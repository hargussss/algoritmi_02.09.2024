// Copyright 2024 Ivan Karpich

#include <gtest.h>
#include "../lib_DMassive/DMassive.h"

#define EPSILON 0.000001

TEST(TestDMassiv, can_create_empty) {
    // Act
    DMassiv<int> arr;

    // Assert
    EXPECT_TRUE(arr.empty());
    EXPECT_EQ(arr.size(), 0);
}

TEST(TestDMassiv, can_push_back) {
    // Arrange
    DMassiv<int> arr;

    // Act
    arr.push_back(10);

    // Assert
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.data()[0], 10);
}

TEST(TestDMassiv, can_pop_back) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    arr.pop_back();

    // Assert
    EXPECT_TRUE(arr.empty());
}

TEST(TestDMassiv, throw_when_pop_back_on_empty) {
    // Arrange
    DMassiv<int> arr;

    // Act & Assert
    ASSERT_THROW(arr.pop_back(), std::out_of_range);
}

TEST(TestDMassiv, can_push_front) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    arr.push_front(5);

    // Assert
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.data()[0], 5);
}

TEST(TestDMassiv, can_find_first) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(10);

    // Act
    size_t index = arr.find_first(10);

    // Assert
    EXPECT_EQ(index, 0);
}

TEST(TestDMassiv, can_find_last) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(10);

    // Act
    size_t index = arr.find_last(10);

    // Assert
    EXPECT_EQ(index, 2);
}

TEST(TestDMassiv, can_replace) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    arr.replace(0, 20);

    // Assert
    EXPECT_EQ(arr.data()[0], 20);
}

TEST(TestDMassiv, throw_when_replace_invalid_index) {
    // Arrange
    DMassiv<int> arr;

    // Act & Assert
    ASSERT_THROW(arr.replace(0, 20), std::out_of_range);
}

TEST(TestDMassiv, can_clear) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    arr.clear();

    // Assert
    EXPECT_TRUE(arr.empty());
}

TEST(TestDMassiv, can_insert) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(30);

    // Act
    arr.insert(20, 1);

    // Assert
    EXPECT_EQ(arr.data()[1], 20);
}

TEST(TestDMassiv, can_remove_by_index) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    // Act
    arr.remove_by_index(1);

    // Assert
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.data()[1], 30);
}

TEST(TestDMassiv, throw_when_remove_invalid_index) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act & Assert
    ASSERT_THROW(arr.remove_by_index(1), std::out_of_range);
}

TEST(TestDMassiv, can_erase) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    // Act
    arr.erase(1, 1);

    // Assert
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.data()[0], 10);
    EXPECT_EQ(arr.data()[1], 30);
}

TEST(TestDMassiv, can_remove_all) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(10);

    // Act
    arr.remove_all(10);

    // Assert
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr.data()[0], 20);
}

TEST(TestDMassiv, can_remove_first) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(10);

    // Act
    arr.remove_first(10);

    // Assert
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.data()[0], 20);
}

TEST(TestDMassiv, can_remove_last) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(10);

    // Act
    arr.remove_last(10);

    // Assert
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr.data()[1], 20);
}

TEST(TestDMassiv, can_copy_construct) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    // Act
    DMassiv<int> copy(arr);

    // Assert
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.data()[0], 10);
    EXPECT_EQ(copy.data()[1], 20);
}

TEST(TestDMassiv, can_move_construct) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    // Act
    DMassiv<int> moved(std::move(arr));

    // Assert
    EXPECT_EQ(moved.size(), 2);
    EXPECT_EQ(moved.data()[0], 10);
    EXPECT_TRUE(arr.empty());  // Original should be empty after move
}

TEST(TestDMassiv, can_reserve_memory) {
    // Arrange
    DMassiv<int> arr;

    // Act
    arr.reserve(10);

    // Assert
    EXPECT_EQ(arr.capacity(), 15);  // Should increase capacity
                                    // based on STEP_CAPACITY
}

TEST(TestDMassiv, can_repack) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    arr.pop_back();  // Leave one empty

    // Act
    arr.repack();

    // Assert
    EXPECT_EQ(arr.size(), 2);  // Size should be adjusted
    EXPECT_EQ(arr.capacity(), 15);  // Capacity should remain the same
}

TEST(TestDMassiv, can_resize_with_value) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    arr.resize(5, 42);

    // Assert
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.data()[3], 42);
    EXPECT_EQ(arr.data()[4], 42);
}

TEST(TestDMassiv, can_insert_multiple_elements) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(30);

    // Act
    int to_insert[] = {20, 21, 22};
    arr.insert(to_insert, 3, 1);

    // Assert
    EXPECT_EQ(arr.size(), 5);
    EXPECT_EQ(arr.data()[1], 20);
    EXPECT_EQ(arr.data()[2], 21);
    EXPECT_EQ(arr.data()[3], 22);
}

TEST(TestDMassiv, can_find_first_not_found) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);
    arr.push_back(20);

    // Act
    size_t index = arr.find_first(30);

    // Assert
    EXPECT_EQ(index, static_cast<size_t>(-1));  // Not found
}

TEST(TestDMassiv, can_check_if_full) {
    // Arrange
    DMassiv<int> arr;
    arr.push_back(10);

    // Act
    bool is_full = arr.full();

    // Assert
    EXPECT_FALSE(is_full);
}

TEST(TestDMassiv, can_swap) {
    // Arrange
    DMassiv<int> arr1;
    arr1.push_back(10);
    arr1.push_back(20);

    DMassiv<int> arr2;
    arr2.push_back(30);
    arr2.push_back(40);

    // Act
    arr1.swap(arr2);

    // Assert
    EXPECT_EQ(arr1.data()[0], 30);
    EXPECT_EQ(arr2.data()[0], 10);
}
