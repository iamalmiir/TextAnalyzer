//
// Created by Almir Redzematovic on 5/12/23.
//

#pragma once

#include <cctype>
#include <iostream>
#include <memory>
#include <string>

/**
 * Node class
 * @param T type of data
 */
template <typename T>
class Node {
 public:
  T data_;
  std::unique_ptr<Node<T>> left_;
  std::unique_ptr<Node<T>> right_;

  /**
   * Constructor
   * @param data data to be stored in the node
   * @param left pointer to the left child
   * @param right pointer to the right child
   */
  explicit Node(const T &data) : data_{data}, left_{nullptr}, right_{nullptr} {}
};

/**
 * Binary tree class
 * @tparam T type of data
 */
template <typename T>
class BinaryTree {
 public:
  /**
   * Default constructor
   * Sets root_ to nullptr
   */
  BinaryTree();

  /**
   * Inserts a new node into the tree
   * @param val value to be inserted
   */
  void insert(const T &);

  /**
   * Traverses the tree in order
   */
  void traverse_in_order() const;

  /**
   * Search for a value in the tree
   */
  bool search(const T &) const;

 private:
  std::unique_ptr<Node<T>> root_;
  std::size_t depth_;

  /**
   * Helper function for traverse_in_order
   * @param node current node
   */
  void insert_helper(const T &, Node<T> *);

  /**
   * Helper function for traverse_in_order
   * @param node current node
   */
  void traverse_in_order_helper(const Node<T> *) const;
};
