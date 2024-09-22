// Copyright 2024 Ivan Karpich

#include <gtest.h>
#include "../lib_Stack/Stack.h"

#define EPSILON 0.000001

TEST(TestTStack, can_push_and_top) {
    // Arrange
    TStack<int> stack(5);
    
    // Act
    stack.push(1);
    int actual_result = stack.top();
    
    // Assert
    EXPECT_EQ(actual_result, 1);
}

TEST(TestTStack, can_pop) {
    // Arrange
    TStack<int> stack(5);
    stack.push(1);
    stack.push(2);
    
    // Act
    int actual_result = stack.pop();
    
    // Assert
    EXPECT_EQ(actual_result, 2);
}

TEST(TestTStack, throw_when_pop_on_empty_stack) {
    // Arrange
    TStack<int> stack(5);
    
    // Act & Assert
    ASSERT_THROW(stack.pop(), std::underflow_error);
}

TEST(TestTStack, throw_when_top_on_empty_stack) {
    // Arrange
    TStack<int> stack(5);
    
    // Act & Assert
    ASSERT_THROW(stack.top(), std::underflow_error);
}

TEST(TestTStack, can_check_if_stack_is_empty) {
    // Arrange
    TStack<int> stack(5);
    
    // Act & Assert
    EXPECT_TRUE(stack.isEmpty());
    stack.push(1);
    EXPECT_FALSE(stack.isEmpty());
}

TEST(TestTStack, can_get_size_of_stack) {
    // Arrange
    TStack<int> stack(5);
    
    // Act
    size_t actual_size = stack.size();
    
    // Assert
    EXPECT_EQ(actual_size, 0);
    stack.push(1);
    EXPECT_EQ(stack.size(), 1);
    stack.pop();
    EXPECT_EQ(stack.size(), 0);
}

TEST(TestTStack, throw_when_push_overflow) {
    // Arrange
    TStack<int> stack(5);
    for (int i = 0; i < 5; ++i) {
        stack.push(i);
    }
    
    // Act & Assert
    ASSERT_THROW(stack.push(6), std::overflow_error);
}