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
    prior_count[image.GetClass()] += 1;
    images_.push_back(image);
  }

  CalculatePriorProbabilities();
  input.close();
}

void Bayes::CalculatePriorProbabilities() {
  for (size_t i = 0; i < prior_prob.size(); ++i) {
    prior_prob[i] = (constant_ + prior_count[i]) / static_cast<double>(kNumDigits * constant_ + kTotalImages);
  }
}

void Bayes::TrainModel() {
  for (Image & image : images_) {

  }
}

}  // namespace naivebayes
