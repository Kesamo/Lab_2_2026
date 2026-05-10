#include <gtest/gtest.h>
#include "MutableSequenceList.hpp"
#include "ImmutableSequenceList.hpp"

class MutableSequenceListTest : public ::testing::Test{
protected:
    MutableSequenceList<int>* seq = nullptr;

    void SetUp() override {
        int arr[] = {3,4,5,6};
        seq = new MutableSequenceList<int>(arr,4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(MutableSequenceListTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->Get(1), 4);
    EXPECT_EQ(seq->Get(2), 5);
    EXPECT_EQ(seq->Get(3), 6);
}

TEST_F(MutableSequenceListTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99,5), IndexOutOfRangeException);

}

TEST_F(MutableSequenceListTest, test_AppendAndPrepend) {
    seq->append(10);

    EXPECT_EQ(seq->GetLength(), 5);
    EXPECT_EQ(seq->Get(4), 10);
    EXPECT_EQ(seq->GetLast(), 10);

    seq->prepend(12);

    EXPECT_EQ(seq->GetLength(), 6);
    EXPECT_EQ(seq->Get(0), 12);
    EXPECT_EQ(seq->GetFirst(), 12);

}

TEST_F(MutableSequenceListTest, test_InsertAt) {
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

TEST_F(MutableSequenceListTest, test_GetSubsequence) {
    Sequence<int>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 3);
    EXPECT_EQ(sub->Get(1), 4);

    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;

}

TEST_F(MutableSequenceListTest, test_Concat) {
    int data[] = {10, 20};
    MutableSequenceList<int> other(data, 2);
    
    Sequence<int>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);
    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0), 3);
    EXPECT_EQ(concat->Get(4), 10);
    EXPECT_EQ(concat->Get(5), 20);

}

TEST_F(MutableSequenceListTest, test_range_based) {
    size_t idx = 0;
    for (int val : *seq) {
        EXPECT_EQ(val, seq->Get(idx));
        ++idx;
    }
}

TEST_F(MutableSequenceListTest, test_throw_empty) {
    MutableSequenceList<int> mut;
    EXPECT_EQ(mut.GetLength(), 0);
    
    EXPECT_THROW(mut.GetFirst(), IndexOutOfRangeException);
    EXPECT_THROW(mut.GetLast(), IndexOutOfRangeException);
    EXPECT_THROW(mut.Get(0), IndexOutOfRangeException);
    
    mut.append(42);
    EXPECT_EQ(mut.GetLength(), 1);
    EXPECT_EQ(mut.Get(0), 42);
}

TEST_F(MutableSequenceListTest, test_Concat_plus_empty) {
    MutableSequenceList<int> mut;
    
    Sequence<int>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    
    Sequence<int>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(MutableSequenceListTest, test_negativ) {
    EXPECT_THROW(seq->Get(-1), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(10, -1), IndexOutOfRangeException);
    EXPECT_THROW(seq->GetSubsequence(-1, 2), IndexOutOfRangeException);
}

class ImmutableSequenceListTest : public ::testing::Test{
protected:
    ImmutableSequenceList<int>* seq = nullptr;

    void SetUp() override {
        int arr[] = {3,4,5,6};
        seq = new ImmutableSequenceList<int>(arr,4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(ImmutableSequenceListTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->Get(1), 4);
    EXPECT_EQ(seq->Get(2), 5);
    EXPECT_EQ(seq->Get(3), 6);
}

TEST_F(ImmutableSequenceListTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99,5), IndexOutOfRangeException);

}

TEST_F(ImmutableSequenceListTest, test_Clone) {
    Sequence<int>* clon = seq->Clone();
    ASSERT_NE(clon, nullptr);
    EXPECT_EQ(clon->GetLength(), 4);
    EXPECT_EQ(clon->Get(2), 5);
    
    EXPECT_NE(clon, seq);
    
    delete clon;
}

TEST_F(ImmutableSequenceListTest, test_Construct) {
    Sequence<int>* immut = seq->Construct();
    ASSERT_NE(immut, nullptr);
    EXPECT_EQ(immut->GetLength(), 0);
    EXPECT_THROW(immut->GetFirst(), IndexOutOfRangeException);
    
    delete immut;

}

TEST_F(ImmutableSequenceListTest, test_GetSubsequence) {
    Sequence<int>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0), 3);
    EXPECT_EQ(sub->Get(1), 4);

    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;

}

TEST_F(ImmutableSequenceListTest, test_Concat) {
    int data[] = {10, 20};
    ImmutableSequenceList<int> other(data, 2);
    
    Sequence<int>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);

    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0), 3);
    EXPECT_EQ(concat->Get(4), 10);
    EXPECT_EQ(concat->Get(5), 20);

}

TEST_F(ImmutableSequenceListTest, test_Concat_plus_empty) {
    ImmutableSequenceList<int> mut;
    
    Sequence<int>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    
    Sequence<int>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(ImmutableSequenceListTest, test_range_based) {
    size_t idx = 0;
    for (int val : *seq) {
        EXPECT_EQ(val, seq->Get(idx));
        ++idx;
    }
}

TEST_F(ImmutableSequenceListTest, test_append) {
    Sequence<int>* append_seq = seq->append(100);

    EXPECT_NE(append_seq, seq);

    EXPECT_EQ(seq->Get(3), 6);
    EXPECT_EQ(seq->GetLength(), 4);

    EXPECT_EQ(append_seq->GetLength(), 5);
    EXPECT_EQ(append_seq->Get(4), 100);

    delete append_seq;
}

TEST_F(ImmutableSequenceListTest, test_prepend) {
    Sequence<int>* prepend_seq = seq->prepend(100);

    EXPECT_NE(prepend_seq, seq);

    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->GetLength(), 4);

    EXPECT_EQ(prepend_seq->GetLength(), 5);
    EXPECT_EQ(prepend_seq->Get(0), 100);

    delete prepend_seq;
}