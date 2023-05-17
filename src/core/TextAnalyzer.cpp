//
// Created by Almir Redzematovic on 5/16/23.
// Description: TextAnalyzer class implementation.
//

#include "TextAnalyzer.h"

TextAnalyzer::TextAnalyzer()
    : total_words_{},
      unique_words_{},
      unique_words_gt3_{},
      total_characters_{},
      total_sentences_{} {}

std::vector<std::string> TextAnalyzer::get_words_more_than_5_percent() const {
  std::vector<std::string> words;

  for (const auto& word : word_count_) {
    // Calculate the percentage of the word
    double percentage = (word.second / static_cast<double>(total_words_)) * 100;
    // If the percentage is greater than 5, add the word to the vector
    if (percentage > 5) words.emplace_back(word.first);
  }

  return words;
}

void TextAnalyzer::print_words_more_than_5_percent() const {
  std::vector<std::string> words = get_words_more_than_5_percent();
  if (words.size() == 0) {
    cout << "No words found with percentage greater than 5\n";
  } else {
    std::size_t counter{1};
    for (const auto& word : get_words_more_than_5_percent()) {
      cout << counter << ". " << word << '\n';
      counter++;
    }
  }
}

void TextAnalyzer::print_index() const {
  // Print the index of unique words in alphabetical order
  // stored int the tree report_
  report_.traverse_in_order();
}

/**
 * Reads a report from a file and performs various calculations.
 *
 * @param file_name The name of the file to read the report from.
 *
 * @throws std::runtime_error If the specified file cannot be found.
 */
void TextAnalyzer::read_report(const std::string& file_name) {
  std::ifstream file(file_name);

  if (!file.is_open()) throw std::runtime_error("File not found");

  std::string word;
  char end_of_sentence_chars[] = {'.', '!', '?'};  // End of sentence chars

  while (file >> word) {
    // Check if the word ends with an end-of-sentence character
    char last_char{word.back()};
    if (std::find(std::begin(end_of_sentence_chars),
                  std::end(end_of_sentence_chars),
                  last_char) != std::end(end_of_sentence_chars)) {
      total_sentences_++;
    }
    word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());

    // If the word is longer than 3 characters, increment the number of that
    // word
    if (word.length() > 3) word_count_[word]++;

    // Increment the total number of characters
    total_characters_ += word.length();

    for (auto& c : word) {
      // Convert the character to lowercase
      c = tolower(c);
    }
    // If the word is not in the tree, increment the number of unique words
    if (!report_.search(word)) {
      // Insert the word into the tree
      report_.insert(word);
      // Increment the number of unique words
      unique_words_++;
      // If the word is longer than 3 characters, increment the number of
      // unique words with length greater than 3
      if (word.length() > 3) unique_words_gt3_++;
    }

    // Increment the total number of words
    total_words_++;
  }
  // Close the file
  file.close();

  // Calculate the average word length and round it to the nearest integer
  avg_word_length_ =
      round(static_cast<double>(total_characters_) / total_words_);
  // Calculate the average sentence length and round it to the nearest integer
  avg_sentence_length_ =
      round(static_cast<double>(total_words_) / total_sentences_);
}

std::size_t TextAnalyzer::get_total_words() const { return total_words_; }
std::size_t TextAnalyzer::get_unique_words() const { return unique_words_; }
std::size_t TextAnalyzer::get_unique_words_gt3() const {
  return unique_words_gt3_;
}
int TextAnalyzer::get_avg_word_length() const { return avg_word_length_; }
int TextAnalyzer::get_avg_sentence_length() const {
  return avg_sentence_length_;
}

void TextAnalyzer::print_report() const {
  cout << "FILE NAME: "
       << "report.txt"
       << "\n\n";
  cout << "\t\t STATISTICAL SUMMARY\n\n";
  cout << "TOTAL NUMBER OF WORDS: " << get_total_words() << "\n";
  cout << "TOTAL NUMBER OF “UNIQUE” WORDS: " << get_unique_words() << "\n";
  cout << "TOTAL NUMBER OF “UNIQUE” WORDS OF MORE THAN THREE LETTERS: "
       << get_unique_words_gt3() << "\n";
  cout << "AVERAGE WORD LENGTH: " << get_avg_word_length() << "\n";
  cout << "AVERAGE SENTENCE LENGTH: " << get_avg_sentence_length() << " words"
       << "\n";

  cout << "\n\t\t STLE WARNINGS\n\n";
  cout << "WORDS USED TOO OFTEN: (WORDS OF MORE THAN 3 LETTERS THAT ARE USED "
          "MORE THAN 5% OF THE TOTAL NUMBER   OF WORDS OF MORE THAN 3 "
          "LETTERS): \n";
  print_words_more_than_5_percent();

  cout << '\n';
  if (avg_sentence_length_ > 10)
    cout << "AVERAGE SENTENCE LENGTH TOO LONG - " << avg_sentence_length_
         << " words\n";

  if (avg_word_length_ > 5)
    cout << "AVERAGE WORD LENGTH TOO LONG - " << avg_word_length_ << " chars\n";

  cout << "\n\t\t INDEX OF UNIQUE WORDS\n\n";
  print_index();

  cout << '\n';
}