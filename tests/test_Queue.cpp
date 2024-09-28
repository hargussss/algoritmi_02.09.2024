// Copyright 2024 Ivan Karpich

#include <gtest.h>
#include "../lib_Queue/Queue.h"

TEST(TestQueue, can_enqueue_and_front) {
    // Arrange
    Queue<int> queue(5);

    // Act
    queue.enqueue(1);
    int actual_result = queue.front();

    // Assert
    EXPECT_EQ(actual_result, 1);
}

TEST(TestQueue, can_dequeue) {
    // Arrange
    Queue<int> queue(5);
    queue.enqueue(1);
    queue.enqueue(2);

    // Act
    int actual_result = queue.dequeue();

    // Assert
    EXPECT_EQ(actual_result, 1);
}

TEST(TestQueue, throw_when_enqueue_overflow) {
    // Arrange
    Queue<int> queue(5);
    for (int i = 0; i < 5; ++i) {
        queue.enqueue(i);
    }

    // Act & Assert
    ASSERT_THROW(queue.enqueue(6), std::overflow_error);
}

TEST(TestQueue, throw_when_dequeue_on_empty_queue) {
    // Arrange
    Queue<int> queue(5);

    // Act & Assert
    ASSERT_THROW(queue.dequeue(), std::underflow_error);
}

TEST(TestQueue, throw_when_front_on_empty_queue) {
    // Arrange
    Queue<int> queue(5);

    // Act & Assert
    ASSERT_THROW(queue.front(), std::underflow_error);
}

TEST(TestQueue, can_check_if_queue_is_empty) {
    // Arrange
    Queue<int> queue(5);

    // Act & Assert
    EXPECT_TRUE(queue.isEmpty());
    queue.enqueue(1);
    EXPECT_FALSE(queue.isEmpty());
}

TEST(TestQueue, can_get_size_of_queue) {
    // Arrange
    Queue<int> queue(5);

    // Act
    size_t actual_size = queue.size();

    // Assert
    EXPECT_EQ(actual_size, 0);
    queue.enqueue(1);
    EXPECT_EQ(queue.size(), 1);
    queue.dequeue();
    EXPECT_EQ(queue.size(), 0);
}

TEST(TestQueue, can_wrap_around_when_enqueue_dequeue) {
    // Arrange
    Queue<int> queue(3);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.dequeue();

    // Act
    queue.enqueue(4);
    int actual_result = queue.dequeue();

    // Assert
    EXPECT_EQ(actual_result, 2);
}
