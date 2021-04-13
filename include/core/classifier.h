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

  void CalculateLikelihoodScores(Image &image);

  int GetBestClass(Image image);

 private:
  Model model_;
  std::vector<double> scores_;
};

}

