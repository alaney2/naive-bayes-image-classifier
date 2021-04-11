#pragma once

#include <cstdio>
#include <vector>

#include "image.h"
#include "model.h"

namespace naivebayes {

class Classifier {
  
 public:
  Classifier(Model& model);
  
  void CalculateLikelihoodScores(Image& image);
  
 private:
  Model model_;
  std::vector<double> scores_;
  
};

}

