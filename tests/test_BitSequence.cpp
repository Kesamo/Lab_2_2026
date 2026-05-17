#include <gtest/gtest.h>
#include <cstdint>
#include "BitSequence.hpp"
#include "MutableBitSequence.hpp"

#include <gtest/gtest.h>
#include "MutableBitSequence.hpp"
#include "ImmutableBitSequence.hpp"

class MutableBitSequenceTest : public ::testing::Test {
protected:
    MutableBitSequence<int>* seq = nullptr;

    void SetUp() override {
        Bit<int> arr[] = {5, 6, 7, 8};
        seq = new MutableBitSequence<int>(arr, 4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(MutableBitSequenceTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);

    EXPECT_EQ(seq->Get(0)[0], 1);
    EXPECT_EQ(seq->Get(0)[1], 0);
    EXPECT_EQ(seq->Get(0)[2], 1);

    EXPECT_EQ(seq->Get(1)[0], 0);
    EXPECT_EQ(seq->Get(1)[1], 1);
    EXPECT_EQ(seq->Get(1)[2], 1);

    EXPECT_EQ(seq->Get(2)[0], 1);
    EXPECT_EQ(seq->Get(2)[1], 1);
    EXPECT_EQ(seq->Get(2)[2], 1);

    EXPECT_EQ(seq->Get(3)[0], 0);
    EXPECT_EQ(seq->Get(3)[1], 0);
    EXPECT_EQ(seq->Get(3)[2], 0);
    EXPECT_EQ(seq->Get(3)[3], 1);
}

TEST_F(MutableBitSequenceTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99, 5), IndexOutOfRangeException);
}

TEST_F(MutableBitSequenceTest, test_AppendAndPrepend) {
    seq->append(10);
    EXPECT_EQ(seq->GetLength(), 5);
    EXPECT_EQ(seq->Get(4)[0], 0);
    EXPECT_EQ(seq->GetLast()[0], 0);

    seq->prepend(12);
    EXPECT_EQ(seq->GetLength(), 6);
    EXPECT_EQ(seq->Get(0)[0], 0);
    EXPECT_EQ(seq->GetFirst()[0], 0);
}

TEST_F(MutableBitSequenceTest, test_InsertAt) {
    seq->insertAt(99, 0);
    EXPECT_EQ(seq->Get(0)[0], 1);
    EXPECT_EQ(seq->GetLength(), 5);

    seq->insertAt(13, 5);
    EXPECT_EQ(seq->Get(5)[0], 1);
    EXPECT_EQ(seq->GetLength(), 6);

    seq->insertAt(22, 3);
    EXPECT_EQ(seq->Get(3)[0], 0);
    EXPECT_EQ(seq->GetLength(), 7);
}

TEST_F(MutableBitSequenceTest, test_GetSubsequence) {
    Sequence<Bit<int>>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0)[0], 1);
    EXPECT_EQ(sub->Get(1)[0], 0);
    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;
}

TEST_F(MutableBitSequenceTest, test_Concat) {
    Bit<int> data[] = {1, 0};
    MutableBitSequence<int> other(data, 2);
    Sequence<Bit<int>>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);
    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0)[0], 1);
    EXPECT_EQ(concat->Get(4)[0], 1);
    EXPECT_EQ(concat->Get(5)[0], 0);
    delete concat;
}

TEST_F(MutableBitSequenceTest, test_range_based) {
    size_t idx = 0;
    for (Bit<int> val : *seq) {
        EXPECT_EQ(val[0], seq->Get(idx)[0]);
        ++idx;
    }
}

TEST_F(MutableBitSequenceTest, test_throw_empty) {
    MutableBitSequence<int> mut;
    EXPECT_EQ(mut.GetLength(), 0);
    EXPECT_THROW(mut.GetFirst(), IndexOutOfRangeException);
    EXPECT_THROW(mut.GetLast(), IndexOutOfRangeException);
    EXPECT_THROW(mut.Get(0), IndexOutOfRangeException);
    mut.append(42);
    EXPECT_EQ(mut.GetLength(), 1);
    EXPECT_EQ(mut.Get(0)[0], 0);
}

TEST_F(MutableBitSequenceTest, test_Concat_plus_empty) {
    MutableBitSequence<int> mut;
    Sequence<Bit<int>>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    Sequence<Bit<int>>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(MutableBitSequenceTest, test_negativ) {
    EXPECT_THROW(seq->Get(-1), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(10, -1), IndexOutOfRangeException);
    EXPECT_THROW(seq->GetSubsequence(-1, 2), InvalidRangeException);
}

class ImmutableBitSequenceTest : public ::testing::Test {
protected:
    ImmutableBitSequence<int>* seq = nullptr;

    void SetUp() override {
        Bit<int> arr[] = {3, 4, 5, 6};
        seq = new ImmutableBitSequence<int>(arr, 4);
    }

    void TearDown() override {
        delete seq;
    }
};

TEST_F(ImmutableBitSequenceTest, test_GET) {
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0)[0], 1);
    EXPECT_EQ(seq->Get(1)[0], 0);
    EXPECT_EQ(seq->Get(2)[0], 1);
    EXPECT_EQ(seq->Get(3)[0], 0);
}

TEST_F(ImmutableBitSequenceTest, test_trow) {
    EXPECT_THROW(seq->Get(5), IndexOutOfRangeException);
    EXPECT_THROW(seq->insertAt(99, 5), IndexOutOfRangeException);
}

TEST_F(ImmutableBitSequenceTest, test_Clone) {
    Sequence<Bit<int>>* clon = seq->Clone();
    ASSERT_NE(clon, nullptr);
    EXPECT_EQ(clon->GetLength(), 4);
    EXPECT_EQ(clon->Get(2)[0], 1);
    EXPECT_NE(clon, seq);
    delete clon;
}

TEST_F(ImmutableBitSequenceTest, test_Construct) {
    Sequence<Bit<int>>* immut = seq->Construct();
    ASSERT_NE(immut, nullptr);
    EXPECT_EQ(immut->GetLength(), 0);
    EXPECT_THROW(immut->GetFirst(), IndexOutOfRangeException);
    delete immut;
}

TEST_F(ImmutableBitSequenceTest, test_GetSubsequence) {
    Sequence<Bit<int>>* sub = seq->GetSubsequence(0, 1);
    ASSERT_NE(sub, nullptr);
    EXPECT_EQ(sub->GetLength(), 2);
    EXPECT_EQ(sub->Get(0)[0], 1);
    EXPECT_EQ(sub->Get(1)[0], 0);
    EXPECT_EQ(seq->GetLength(), 4);
    delete sub;
}

TEST_F(ImmutableBitSequenceTest, test_Concat) {
    Bit<int> data[] = {10, 20};
    ImmutableBitSequence<int> other(data, 2);
    Sequence<Bit<int>>* concat = seq->Concat(&other);
    ASSERT_NE(concat, nullptr);
    EXPECT_EQ(concat->GetLength(), 6);
    EXPECT_EQ(concat->Get(0)[0], 1);
    EXPECT_EQ(concat->Get(4)[0], 0);
    EXPECT_EQ(concat->Get(5)[0], 0);
}

TEST_F(ImmutableBitSequenceTest, test_Concat_plus_empty) {
    ImmutableBitSequence<int> mut;
    Sequence<Bit<int>>* r1 = seq->Concat(&mut);
    EXPECT_EQ(r1->GetLength(), 4);
    delete r1;
    Sequence<Bit<int>>* r2 = mut.Concat(seq);
    EXPECT_EQ(r2->GetLength(), 4);
    delete r2;
}

TEST_F(ImmutableBitSequenceTest, test_range_based) {
    size_t idx = 0;
    for (Bit<int> val : *seq) {
        EXPECT_EQ(val[0], seq->Get(idx)[0]);
        ++idx;
    }
}

TEST_F(ImmutableBitSequenceTest, test_append) {
    Sequence<Bit<int>>* append_seq = seq->append(100);
    EXPECT_NE(append_seq, seq);
    EXPECT_EQ(seq->Get(3)[0], 0);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(append_seq->GetLength(), 5);
    EXPECT_EQ(append_seq->Get(4)[0], 0);
    delete append_seq;
}

TEST_F(ImmutableBitSequenceTest, test_prepend) {
    Sequence<Bit<int>>* prepend_seq = seq->prepend(100);
    EXPECT_NE(prepend_seq, seq);
    EXPECT_EQ(seq->Get(0)[0], 1);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(prepend_seq->GetLength(), 5);
    EXPECT_EQ(prepend_seq->Get(0)[0], 0);
    delete prepend_seq;
}