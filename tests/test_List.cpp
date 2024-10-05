// Copyright 2024 Ivan Karpich

#include <gtest.h>
#include "../lib_List/List.h"

TEST(TListTest, can_create_empty_list) {
    // Act & Assert
    TList<int> list;
    ASSERT_TRUE(list.isEmpty());
}

TEST(TListTest, can_insert_front) {
    // Arrange
    TList<int> list;

    // Act
    list.insertFront(10);

    // Assert
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.find(10)->getValue(), 10);
}

TEST(TListTest, can_insert_back) {
    // Arrange
    TList<int> list;

    // Act
    list.insertBack(20);

    // Assert
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.find(20)->getValue(), 20);
}

TEST(TListTest, can_insert_after_node) {
    // Arrange
    TList<int> list;
    list.insertFront(10);
    TNode<int>* node = list.find(10);

    // Act
    list.insertAfter(node, 15);

    // Assert
    EXPECT_EQ(list.find(15)->getValue(), 15);
}

TEST(TListTest, can_insert_at_position) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    list.insertBack(20);

    // Act
    list.insertAt(1, 15);

    // Assert
    EXPECT_EQ(list.find(15)->getValue(), 15);
}

TEST(TListTest, throws_when_insert_at_invalid_position) {
    // Arrange
    TList<int> list;

    // Act & Assert
    ASSERT_THROW(list.insertAt(-1, 10), std::out_of_range);
}

TEST(TListTest, can_remove_front) {
    // Arrange
    TList<int> list;
    list.insertFront(10);

    // Act
    list.removeFront();

    // Assert
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, can_remove_back) {
    // Arrange
    TList<int> list;
    list.insertBack(20);

    // Act
    list.removeBack();

    // Assert
    EXPECT_TRUE(list.isEmpty());
}

TEST(TListTest, can_remove_at_position) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    list.insertBack(20);
    list.insertBack(30);

    // Act
    list.removeAt(1);

    // Assert
    EXPECT_EQ(list.find(20), nullptr);
}

TEST(TListTest, throws_when_remove_at_invalid_position) {
    // Arrange
    TList<int> list;
    list.insertBack(10);

    // Act & Assert
    ASSERT_THROW(list.removeAt(-1), std::out_of_range);
}

TEST(TListTest, can_find_value) {
    // Arrange
    TList<int> list;
    list.insertBack(50);

    // Act
    TNode<int>* found = list.find(50);

    // Assert
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getValue(), 50);
}

TEST(TListTest, returns_null_if_value_not_found) {
    // Arrange
    TList<int> list;

    // Act
    TNode<int>* found = list.find(100);

    // Assert
    EXPECT_EQ(found, nullptr);
}

TEST(TListTest, can_replace_node_value) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    TNode<int>* node = list.find(10);

    // Act
    list.replaceNode(node, 20);

    // Assert
    EXPECT_EQ(list.find(20)->getValue(), 20);
}

TEST(TListTest, can_replace_value_at_position) {
    // Arrange
    TList<int> list;
    list.insertBack(10);

    // Act
    list.replaceAt(0, 20);

    // Assert
    EXPECT_EQ(list.find(20)->getValue(), 20);
}

TEST(TListTest, throws_when_replace_at_invalid_position) {
    // Arrange
    TList<int> list;

    // Act & Assert
    ASSERT_THROW(list.replaceAt(-1, 10), std::out_of_range);
}

TEST(TListTest, can_assign_list) {
    // Arrange
    TList<int> list1;
    list1.insertBack(10);
    list1.insertBack(20);

    TList<int> list2;

    // Act
    list2 = list1;

    // Assert
    EXPECT_EQ(list2.find(10)->getValue(), 10);
    EXPECT_EQ(list2.find(20)->getValue(), 20);
}

TEST(TNodeTest, can_copy_node) {
    // Arrange
    TNode<int> node(10);

    // Act
    TNode<int> copyNode = node;

    // Assert
    EXPECT_EQ(copyNode.getValue(), node.getValue());
}

TEST(TNodeTest, can_compare_nodes) {
    // Arrange
    TNode<int> node1(10);
    TNode<int> node2(10);
    TNode<int> node3(20);

    // Assert
    EXPECT_TRUE(node1 == node2);
    EXPECT_FALSE(node1 == node3);
}

TEST(TListTest, throws_when_insert_after_null) {
    // Arrange
    TList<int> list;

    // Act & Assert
    ASSERT_THROW(list.insertAfter(nullptr, 10), std::invalid_argument);
}

TEST(TListTest, throws_when_remove_non_existent_node) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    TNode<int>* node = new TNode<int>(20);

    // Act & Assert
    ASSERT_THROW(list.removeNode(node), std::invalid_argument);
    delete node;
}

TEST(TListTest, can_remove_node_by_pointer) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    TNode<int>* node = list.find(10);

    // Act
    list.removeNode(node);

    // Assert
    EXPECT_TRUE(list.isEmpty());
}

TEST(TNodeTest, can_print_node) {
    // Arrange
    TNode<int> node(10);
    std::stringstream ss;

    // Act
    ss << node;

    // Assert
    EXPECT_EQ(ss.str(), "10");
}

TEST(TListTest, can_print_list) {
    // Arrange
    TList<int> list;
    list.insertBack(10);
    list.insertBack(20);
    std::stringstream ss;

    // Act
    ss << list;

    // Assert
    EXPECT_EQ(ss.str(), "10 -> 20 -> null");
}
