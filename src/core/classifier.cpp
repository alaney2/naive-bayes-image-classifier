#include "core/classifier.h"

namespace naivebayes {

Classifier::Classifier(Model& model) : model_(model) {}

double Classifier::CalculateAccuracy(const std::vector<Image>& images) {
  size_t count = 0;
  for (const auto & image : images) {
    size_t predicted = GetBestClass(const_cast<Image&>(image));
    size_t actual = image.GetClass();
    if (actual == predicted) {
      ++count;
    }
  }
  
  return static_cast<double>(count) / static_cast<double>(images.size());
}

void Classifier::CalculateLikelihoodScores(Image &image) {
  scores_.resize(kNumClasses, 0);
  
  for (size_t num = 0; num < kNumClasses; ++num) {
    double likelihood = log(model_.GetPriorProbability(num));
    for (size_t row = 0; row < image.GetImageSize(); ++row) {
      for (size_t col = 0; col < image.GetImageSize(); ++col) {
        size_t shade = image.GetShade(row, col);
        likelihood += log(model_.GetFeatureProbability(row, col, shade, num));
      }
    }
    scores_[num] = likelihood;
  }
}

int Classifier::GetBestClass(Image image) {
  CalculateLikelihoodScores(image);
  int best_class = 0;
  for (int num = 1; num < kNumClasses; ++num) {
    if (scores_[num] > scores_[best_class]) {
      best_class = num;
    }
  }
  
  return best_class;
}
double Classifier::GetScore(size_t num) {
  return scores_[num];
}
}
