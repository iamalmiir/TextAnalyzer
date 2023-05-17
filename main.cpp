/**
 * Text Analyzer Program
 * Author: Almir Redzematovic
 * Date: 5/16/23
 *
 * Description: This program analyzes a text report and generates a report based
 * on the analysis.
 */

#include "src/core/TextAnalyzer.cpp"
#include "src/core/TextAnalyzer.h"

int main() {
  // Create a TextAnalyzer object
  TextAnalyzer report_analyzer;

  // Prompt the user for the file name
  std::string file_name;
  cout << "Enter the file name: ";

  // If the input is empty, use the default file name
  std::getline(std::cin, file_name);
  if (file_name.empty()) file_name = "report.txt";

  // Read the report from the file
  report_analyzer.read_report("report.txt");

  // Print the results of the analysis
  report_analyzer.print_report();

  return 0;
}
