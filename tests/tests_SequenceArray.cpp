#include <gtest/gtest.h>
#include "MutableSequenceArray.hpp"
#include "ImmutableSequenceArray.hpp"

class MutableSequenceArrayTest : public ::testing::Test {
protected:
    MutableSequenceArray<int>* seq = nullptr;

    void SetUp() override {
        int arr[] = {3,4,5,6};
        seq = new MutableSequenceArray<int>(arr, 4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(MutableSequenceArrayTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->Get(1), 4);
    EXPECT_EQ(seq->Get(2), 5);
    EXPECT_EQ(seq->Get(3), 6);
}

TEST_F(MutableSequenceArrayTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99,5), IndexOutOfRangeException);

}

TEST_F(MutableSequenceArrayTest, test_AppendAndPrepend) {
    seq->append(10);

    EXPECT_EQ(seq->GetLength(), 5);
    EXPECT_EQ(seq->Get(4), 10);
    EXPECT_EQ(seq->GetLast(), 10);

    seq->prepend(12);

    EXPECT_EQ(seq->GetLength(), 6);
    EXPECT_EQ(seq->Get(0), 12);
    EXPECT_EQ(seq->GetFirst(), 12);

}

TEST_F(MutableSequenceArrayTest, test_InsertAt) {
    seq->insertAt(99,0);

    EXPECT_EQ(seq->Get(0), 99);
    EXPECT_EQ(seq->GetLength(), 5);

    seq->insertAt(13,5);

    EXPECT_EQ(seq->Get(5), 13);
    EXPECT_EQ(seq->GetLength(), 6);

    seq->insertAt(22,3);

    EXPECT_EQ(seq->Get(3), 22);
    EXPECT_EQ(seq->GetLength(), 7);

}

TEST_F(MutableSequenceArrayTest, test_GetSubsequence) {
    Sequence<int>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 3);
    EXPECT_EQ(sub->Get(1), 4);

    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;

}

TEST_F(MutableSequenceArrayTest, test_Concat) {
    int data[] = {10, 20};
    MutableSequenceArray<int> other(data, 2);
    
    Sequence<int>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);
    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0), 3);
    EXPECT_EQ(concat->Get(4), 10);
    EXPECT_EQ(concat->Get(5), 20);

}

TEST_F(MutableSequenceArrayTest, test_range_based) {
    size_t idx = 0;
    for (int val : *seq) {
        EXPECT_EQ(val, seq->Get(idx));
        ++idx;
    }
}

TEST_F(MutableSequenceArrayTest, test_throw_empty) {
    MutableSequenceArray<int> mut;
    EXPECT_EQ(mut.GetLength(), 0);
    
    EXPECT_THROW(mut.GetFirst(), IndexOutOfRangeException);
    EXPECT_THROW(mut.GetLast(), IndexOutOfRangeException);
    EXPECT_THROW(mut.Get(0), IndexOutOfRangeException);
    
    mut.append(42);
    EXPECT_EQ(mut.GetLength(), 1);
    EXPECT_EQ(mut.Get(0), 42);
}

TEST_F(MutableSequenceArrayTest, test_Concat_plus_empty) {
    MutableSequenceArray<int> mut;
    
    Sequence<int>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    
    Sequence<int>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(MutableSequenceArrayTest, test_negativ) {
    EXPECT_THROW(seq->Get(-1), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(10, -1), IndexOutOfRangeException);
    EXPECT_THROW(seq->GetSubsequence(-1, 2), InvalidRangeException);
}

class ImmutablSequenceArrayTest : public ::testing::Test {
    protected:
    ImmutableSequenceArray<int>* seq = nullptr;

    void SetUp() override {
        int arr[] = {3,4,5,6};
        seq = new ImmutableSequenceArray<int>(arr, 4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(ImmutablSequenceArrayTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->Get(1), 4);
    EXPECT_EQ(seq->Get(2), 5);
    EXPECT_EQ(seq->Get(3), 6);
}

TEST_F(ImmutablSequenceArrayTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99,5), IndexOutOfRangeException);

}

TEST_F(ImmutablSequenceArrayTest, test_Clone) {
    Sequence<int>* clon = seq->Clone();
    ASSERT_NE(clon, nullptr);
    EXPECT_EQ(clon->GetLength(), 4);
    EXPECT_EQ(clon->Get(2), 5);
    
    EXPECT_NE(clon, seq);
    
    delete clon;
}

TEST_F(ImmutablSequenceArrayTest, test_Construct) {
    Sequence<int>* immut = seq->Construct();
    ASSERT_NE(immut, nullptr);
    EXPECT_EQ(immut->GetLength(), 0);
    EXPECT_THROW(immut->GetFirst(), IndexOutOfRangeException);
    
    delete immut;

}

TEST_F(ImmutablSequenceArrayTest, test_GetSubsequence) {
    Sequence<int>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 3);
    EXPECT_EQ(sub->Get(1), 4);

    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;

}

TEST_F(ImmutablSequenceArrayTest, test_Concat) {
    int data[] = {10, 20};
    MutableSequenceArray<int> other(data, 2);
    
    Sequence<int>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);

    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0), 3);
    EXPECT_EQ(concat->Get(4), 10);
    EXPECT_EQ(concat->Get(5), 20);

}

TEST_F(ImmutablSequenceArrayTest, test_Concat_plus_empty) {
    MutableSequenceArray<int> mut;
    
    Sequence<int>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    
    Sequence<int>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(ImmutablSequenceArrayTest, test_range_based) {
    size_t idx = 0;
    for (int val : *seq) {
        EXPECT_EQ(val, seq->Get(idx));
        ++idx;
    }
}

TEST_F(ImmutablSequenceArrayTest, test_append) {
    Sequence<int>* append_seq = seq->append(100);

    EXPECT_NE(append_seq, seq);

    EXPECT_EQ(seq->Get(3), 6);
    EXPECT_EQ(seq->GetLength(), 4);

    EXPECT_EQ(append_seq->GetLength(), 5);
    EXPECT_EQ(append_seq->Get(4), 100);

    delete append_seq;
}

TEST_F(ImmutablSequenceArrayTest, test_prepend) {
    Sequence<int>* prepend_seq = seq->prepend(100);

    EXPECT_NE(prepend_seq, seq);

    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->GetLength(), 4);

    EXPECT_EQ(prepend_seq->GetLength(), 5);
    EXPECT_EQ(prepend_seq->Get(0), 100);

    delete prepend_seq;
}