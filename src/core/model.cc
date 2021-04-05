#include <core/model.h>

#include <fstream>
#include <iostream>
#include <vector>

using std::vector;

namespace naivebayes {

std::string Bayes::GetBestClass() const {
  return "CS 126";
}

void Bayes::ParseFile(std::string& file_path) {
  std::ifstream input(file_path);

  char digit;
  Image image;
  while (input.is_open()) {
    input >> digit;
    priors_[digit - '0'] += 1;

    input >> image;
    images_.push_back(image);
  }

  SetPriors();
  input.close();
}

void Bayes::SetPriors() {
  for (double & prior : priors_) {
    prior /= static_cast<double>(kTotalImages);
  }
}

}  // namespace naivebayes
