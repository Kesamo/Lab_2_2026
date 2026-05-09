#include <gtest/gtest.h>
#include "MutableSequenceArray.hpp"

class MutableArrayTest : public ::testing::Test {
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

TEST_F(MutableArrayTest, test_GET){
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(seq->GetLength(), 4);
    EXPECT_EQ(seq->Get(0), 3);
    EXPECT_EQ(seq->Get(1), 4);
    EXPECT_EQ(seq->Get(2), 5);
    EXPECT_EQ(seq->Get(3), 6);
}

TEST_F(MutableArrayTest, test_append){
    seq->append(20);
    EXPECT_EQ(seq->GetLength(), 5);
    EXPECT_EQ(seq->Get(4), 20);
}

