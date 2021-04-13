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

  int CalculateLikelihoodScores(Image image);

  int GetBestClass();
  
 private:
  Model model_;
  std::vector<double> scores_;
};

}

