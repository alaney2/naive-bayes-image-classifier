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

  Image image;
  while (input.is_open()) {
    input >> image;
    priors_[image.GetClass()] += 1;
    images_.push_back(image);
  }

  SetPriors();
  input.close();
}

void Bayes::SetPriors() {
  for (double & prior : priors_) {
    prior = (constant_ + prior) / static_cast<double>(kNumDigits * constant_ + kTotalImages);
  }
}

void Bayes::TrainModel() {
  for (Image & image : images_) {

  }
}

}  // namespace naivebayes
