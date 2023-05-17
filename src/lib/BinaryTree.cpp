//
// Created by Almir Redzematovic on 5/12/23.
//

#include "BinaryTree.h"

using std::cout, std::string;

/**
 * Default constructor
 * Sets root_ to nullptr
 */
template <typename T>
BinaryTree<T>::BinaryTree() : root_{nullptr}, depth_{0} {}

/**
 * Helper function for insert
 * @param val value to be inserted
 * @param node pointer to the current node
 */
template <typename T>
void BinaryTree<T>::insert_helper(const T &val, Node<T> *node) {
  // If the value is less than the current node, insert it into the left subtree
  if (val < node->data_) {
    // If the left child is nullptr, create a new node and set it as the left
    if (node->left_ == nullptr)
      node->left_ = std::make_unique<Node<T>>(val);
    else
      // Otherwise, recursively call the function on the left child
      insert_helper(val, node->left_.get());
  } else {
    // If the value is greater than or equal to the current node, insert it into
    if (node->right_ == nullptr)
      // If the right child is nullptr, create a new node and set it as the
      node->right_ = std::make_unique<Node<T>>(val);
    else
      // Otherwise, recursively call the function on the right child
      insert_helper(val, node->right_.get());
  }
}

/**
 * Function to insert a new node into the tree
 * @param val value to be inserted
 */
template <typename T>
void BinaryTree<T>::insert(const T &val) {
  if (root_ == nullptr) {
    root_ = std::make_unique<Node<T>>(val);
    return;
  }

  insert_helper(val, root_.get());
  depth_++;
}

/**
 * Search for a value in the tree
 * @param val value to be searched for
 */
template <typename T>
bool BinaryTree<T>::search(const T &val) const {
  Node<T> *current = root_.get();

  while (current != nullptr) {
    if (val == current->data_) {
      return true;  // value found
    } else if (val < current->data_) {
      current = current->left_.get();  // Traverse left subtree
    } else {
      current = current->right_.get();  // Traverse right subtree
    }
  }

  return false;  // value not found
}

/**
 * Helper function to print the tree in order
 * @param node pointer to the current node
 * @link traverse_in_order
 */
template <typename T>
void BinaryTree<T>::traverse_in_order_helper(const Node<T> *node) const {
  if (node == nullptr) return;

  static char current_letter{};  // Initialize with null character

  traverse_in_order_helper(node->left_.get());

  // Check the first character of the data to determine the index
  if (node->data_.empty()) {
    return;
  }
  // Convert the first character to uppercase
  char first_letter = std::toupper(node->data_[0]);

  // If a new letter is encountered, update the current letter and print it
  if (first_letter != current_letter) {
    current_letter = first_letter;
    cout << '\n' << current_letter << '\n';
  }

  cout << node->data_ << '\n';
  traverse_in_order_helper(node->right_.get());
}

/**
 * Traverses the tree in order
 * Using the helper function traverse_in_order_helper to do the actual traversal
 * @link traverse_in_order_helper
 */
template <typename T>
void BinaryTree<T>::traverse_in_order() const {
  traverse_in_order_helper(root_.get());
  // Print a newline after the traversal
  cout << '\n';
}
