//
// Created by Almir Redzematovic on 5/16/23.
//

#pragma once

#include <cmath>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "../lib/BinaryTree.cpp"
#include "../lib/BinaryTree.h"

/**
 * TextAnalyzer class
 */

class TextAnalyzer {
 public:
  TextAnalyzer();

  /**
   * Reads a report from a file and performs various calculations.
   *
   * @param file_name The name of the file to read the report from.
   *
   * @throws std::runtime_error If the specified file cannot be found.
   */

  void read_report(const std::string &);

  /**
   * Get the total number of words in the file
   * @return total number of words
   */

  std::size_t get_total_words() const;

  /**
   * Get the number of unique words in the file
   * @return number of unique words
   */

  std::size_t get_unique_words() const;

  /**
   * Get the number of unique words with length greater than 3
   * @return number of unique words with length greater than 3
   */

  std::size_t get_unique_words_gt3() const;

  /**
   * Get the average word length
   * @return average word length
   */

  int get_avg_word_length() const;

  /**
   * Get the average sentence length
   * @return average sentence length
   */

  int get_avg_sentence_length() const;

  /**
   *  Find words in the unordered map that are used more than 5% of the total
   * number of words
   *  @return vector of words that are used more than 5% of the total number of
   * words
   */

  std::vector<std::string> get_words_more_than_5_percent() const;

  /**
   *  Print the words that are used more than 5% of the total number of words
   */

  void print_words_more_than_5_percent() const;

  /**
   *  Print index of the unique words by identifying the first letter of the
   * word
   */

  void print_index() const;

  /**
   * Print the report
   */

  void print_report() const;

 private:
  BinaryTree<std::string> report_;
  std::unordered_map<std::string, std::size_t> word_count_;
  std::size_t total_words_;
  std::size_t unique_words_;
  std::size_t unique_words_gt3_;
  std::size_t total_characters_;
  std::size_t total_sentences_;
  int avg_word_length_;
  int avg_sentence_length_;
};