// Copyright 2024 Ivan Karpich

#include <gtest.h>
#include "../lib_pair/pair.h"

#define EPSILON 0.000001

// тест конструкторов
TEST(TPairTest, DefaultConstructor) {
    // Arrange & Act
    TPair<int, double> pair;

    // Assert
    EXPECT_EQ(pair.first(), 0);
    EXPECT_EQ(pair.second(), 0.0);
}

TEST(TPairTest, ParameterizedConstructor) {
    // Arrange
    int first = 1;
    double second = 2.5;

    // Act
    TPair<int, double> pair(first, second);

    // Assert
    EXPECT_EQ(pair.first(), first);
    EXPECT_EQ(pair.second(), second);
}

TEST(TPairTest, MoveConstructor) {
    // Arrange
    TPair<int, double> original(1, 2.5);

    // Act
    TPair<int, double> moved(std::move(original));

    // Assert
    EXPECT_EQ(moved.first(), 1);
    EXPECT_EQ(moved.second(), 2.5);
}

// тесты операторов
TEST(TPairTest, AssignmentOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2;

    // Act
    pair2 = pair1;

    // Assert
    EXPECT_EQ(pair2.first(), 1);
    EXPECT_EQ(pair2.second(), 2.5);
}

TEST(TPairTest, MoveAssignmentOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2;

    // Act
    pair2 = std::move(pair1);

    // Assert
    EXPECT_EQ(pair2.first(), 1);
    EXPECT_EQ(pair2.second(), 2.5);
}

TEST(TPairTest, EqualityOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2(1, 2.5);

    // Act & Assert
    EXPECT_TRUE(pair1 == pair2);
}

TEST(TPairTest, InequalityOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2(2, 3.5);

    // Act & Assert
    EXPECT_TRUE(pair1 != pair2);
}

TEST(TPairTest, LessThanOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2(2, 3.5);

    // Act & Assert
    EXPECT_TRUE(pair1 < pair2);
}

// тесты арифметических операций
TEST(TPairTest, AdditionOperator) {
    // Arrange
    TPair<int, double> pair1(1, 2.5);
    TPair<int, double> pair2(3, 4.5);

    // Act
    TPair<int, double> result = pair1 + pair2;

    // Assert
    EXPECT_EQ(result.first(), 4);
    EXPECT_EQ(result.second(), 7.0);
}

TEST(TPairTest, SubtractionOperator) {
    // Arrange
    TPair<int, double> pair1(5, 6.5);
    TPair<int, double> pair2(3, 4.5);

    // Act
    TPair<int, double> result = pair1 - pair2;

    // Assert
    EXPECT_EQ(result.first(), 2);
    EXPECT_EQ(result.second(), 2.0);
}

// тест метода to_string
TEST(TPairTest, ToStringMethod) {
    // Arrange
    TPair<int, double> pair(1, 2.5);

    // Act
    std::string result = pair.to_string();

    // Assert
    EXPECT_EQ(result, "(1, 2.5)");
}

// тест оператора вывода в поток
TEST(TPairTest, OutputStreamOperator) {
    // Arrange
    TPair<int, double> pair(1, 2.5);
    std::stringstream ss;

    // Act
    ss << pair;

    // Assert
    EXPECT_EQ(ss.str(), "(1, 2.5)");
}
