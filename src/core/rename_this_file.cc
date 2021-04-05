#include <core/rename_this_file.h>

#include <iostream>
#include <fstream>
#include <vector>

using std::vector;

namespace naivebayes {

std::string Bayes::GetBestClass() const {
  return "CS 126";
}

std::ostream& operator<<(std::ostream& os, vector<vector<vector<vector<double>>>> vector) {
  return os;
}

std::istream& operator>>(std::istream& is, vector<vector<vector<vector<double>>>> vector) {
  std::string file_path = "/data/trainingimagesandlabels.txt";
  std::ifstream input_file(file_path);
  if (input_file.is_open()) {
    std::string line;
    while (getline(input_file, line)) {
      int actual = std::stoi(line);
      for (size_t i = 0; i < 28; ++i) {
        for (size_t j = 0; j < 28; ++j) {
          vector[i][j][0][actual] = 1;
        }
      }
    }
    input_file.close();
  }
  return is;
}

}  // namespace naivebayes
