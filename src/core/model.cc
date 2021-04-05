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
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        if (image.GetShades() == 0) {
          feature_count_[row][col][0][image.GetClass()] += 1;
        } else {
          feature_count_[row][col][1][image.GetClass()] += 1;
        }
      }
    }
  }
  CalculateFeatureProbabilities();
}

void Bayes::CalculateFeatureProbabilities() {
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t c = 0; c < kNumDigits; ++c) {
          feature_prob_[row][col][shade][c] = (constant_ + feature_count_[row][col][shade][c]) /
              static_cast<double>(2 * constant_ + prior_count[c]);
        }
      }
    }
  }
}

}  // namespace naivebayes
