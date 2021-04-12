#include "core/classifier.h"

#include <core/model.h>

namespace naivebayes {

Classifier::Classifier(Model& model) : model_(model){ }

double Classifier::CalculateAccuracy(const std::vector<Image>& images) {
  size_t count = 0;
  for (size_t i = 0; i < images.size(); ++i) {
    size_t predicted = CalculateLikelihoodScores(const_cast<Image&>(images[i]));
    size_t actual = images[i].GetClass();
    if (actual == predicted) {
      ++count;
    }
  }
  
  return static_cast<double>(count) / images.size();
}

size_t Classifier::CalculateLikelihoodScores(Image& image) {
  scores_.resize(kNumDigits, 0);
  
  for (size_t num = 0; num < kNumDigits; ++num) {
    double likelihood = log(model_.GetPriorProbability(num));
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        size_t shade = image.GetShade(row, col);
        likelihood += log(model_.GetFeatureProbability(row, col, shade, num));
      }
    }
    scores_[num] = likelihood;
  }

  size_t best_class = GetBestClass();
  return best_class;
}

size_t Classifier::GetBestClass() {
  int best_class = 0;
  for (int num = 1; num < 10; ++num) {
    if (scores_[num] > scores_[best_class]) {
      best_class = num;
    }
  }
  
  return best_class;
}
}
