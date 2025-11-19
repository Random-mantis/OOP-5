#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, PushAndTop) {
    Stack<int, MapAllocator<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.top(), 3);
}

TEST(StackTest, DelfirstRemovesTop) {
    Stack<int, MapAllocator<int>> s;
    s.push(10);
    s.push(20);
    s.delfirst();
    EXPECT_EQ(s.top(), 10);
}

TEST(StackTest, ClearEmptiesStack) {
    Stack<int, MapAllocator<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.clear();
    EXPECT_TRUE(s.is_void());
}

TEST(StackTest, IsVoidOnEmptyStack) {
    Stack<int, MapAllocator<int>> s;
    EXPECT_TRUE(s.is_void());
    s.push(5);
    EXPECT_FALSE(s.is_void());
}

TEST(StackTest, IteratorTraversesAllElements) {
    Stack<int, MapAllocator<int>> s;
    s.push(1);
    s.push(2);
    s.push(3);
    std::vector<int> values;
    for (auto it = s.begin(); it != s.end(); ++it)
        values.push_back(*it);
    EXPECT_EQ(values.size(), 3);
    EXPECT_EQ(values[0], 3);
    EXPECT_EQ(values[1], 2);
    EXPECT_EQ(values[2], 1);
}

TEST(StackTest, PopAllElements) {
    Stack<int, MapAllocator<int>> s;
    for (int i = 0; i < 5; ++i)
        s.push(i);
    for (int i = 0; i < 5; ++i)
        s.delfirst();
    EXPECT_TRUE(s.is_void());
}

TEST(StackTest, TopReturnsReference) {
    Stack<int, MapAllocator<int>> s;
    s.push(42);
    int& ref = s.top();
    ref = 99;
    EXPECT_EQ(s.top(), 99);
}






