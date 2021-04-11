#include "core/classifier.h"

#include <core/model.h>

namespace naivebayes {

Classifier::Classifier(Model& model) : model_(model){ }

void Classifier::CalculateLikelihoodScores(Image& image) {
  for (size_t num = 0; num < kNumDigits; ++num) {
    double likelihood = log(model_.GetPriorProbability(num));
    
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        likelihood += log(image.GetShade(row, col));
      }
    }
    
    scores_[num] = likelihood;
  }
}

}
