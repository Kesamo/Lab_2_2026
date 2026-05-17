#include <gtest/gtest.h>
#include "controller.hpp"
#include "MutableSequenceArray.hpp"
#include "ImmutableSequenceArray.hpp"
#include "MutableSequenceList.hpp"
#include "ImmutableSequenceList.hpp"
#include "MutableBitSequence.hpp"
#include "ImmutableBitSequence.hpp"

TEST(MenegerTest, test_creat_mut) {
    Manager m;
    m.create(0, 0);
    EXPECT_EQ(m.size(), 1);
    Sequence<uint8_t>* seq = m.get(0);
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(m.getName(0), "1)Array_Mutabel");
}

TEST(MenegerTest, test_creat_immut) {
    Manager m;
    m.create(0, 1);
    EXPECT_EQ(m.size(), 1);
    auto* seq = m.get(0);
    ASSERT_NE(seq, nullptr);
    EXPECT_EQ(m.getName(0), "1)Array_Immutabele");
}

TEST(MenegerTest, test_creat) {
    Manager m;
    m.create(0, 0);
    m.create(1, 1);
    EXPECT_EQ(m.size(), 2);
    EXPECT_EQ(m.getName(0), "1)Array_Mutabel");
    EXPECT_EQ(m.getName(1), "2)List_Immutabele");
}

TEST(MenegerTest, test_remove) {
    Manager m;
    m.create(0, 0);
    m.create(1, 1);
    EXPECT_EQ(m.size(), 2);
    m.remove(0);
    EXPECT_EQ(m.size(), 1);
    EXPECT_EQ(m.getName(0), "1)List_Immutabele");
}

TEST(MenegerTest, test_get_nullptr) {
    Manager m;
    EXPECT_EQ(m.get(0), nullptr);
    m.create(0, 0);
    EXPECT_EQ(m.get(1), nullptr);
}

TEST(MenegerTest, test_getName) {
    Manager m;
    EXPECT_EQ(m.getName(0), "");
    m.create(0, 0);
    EXPECT_EQ(m.getName(1), "");
}

TEST(MenegerTest, test_storage_node) {
    Storage s;
    auto* seq = new MutableSequenceArray<uint8_t>();
    s.push(seq, 0, 0);
    EXPECT_EQ(s.size(), 1);
    auto* node = s.get(0);
    ASSERT_NE(node, nullptr);
    EXPECT_EQ(node->seq, seq);
    EXPECT_EQ(node->seq_idx, 0);
    EXPECT_EQ(node->mut_idx, 0);
}