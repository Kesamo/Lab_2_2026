#include <gtest/gtest.h>
#include "../src/sequences/SequenceArray/MutableSequenceArray.hpp"

TEST(array_sequence, constructor_test) {
    int array[] = {1, 2, 3, 4};
    MutableSequenceArray<int> seq(array, 4);

    ASSERT_EQ(seq.GetLength(), 4);

    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(1), 2);
    EXPECT_EQ(seq.Get(2), 3);
    EXPECT_EQ(seq.Get(3), 4);
}