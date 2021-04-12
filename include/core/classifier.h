#pragma once

#include <cstdio>
#include <vector>

#include "image.h"
#include "model.h"

namespace naivebayes {

class Classifier {
  
 public:
  Classifier(Model& model);

  double CalculateAccuracy(const std::vector<Image> &images);
  
  size_t CalculateLikelihoodScores(Image& image);

  size_t GetBestClass();
 private:
  Model model_;
  std::vector<double> scores_;
  std::vector<size_t> predictions_;
  
};

}

