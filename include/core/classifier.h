#pragma once

#include <cstdio>
#include <vector>

#include "image.h"
#include "model.h"

namespace naivebayes {

class Classifier {
  
 public:
  Classifier(Model& model);

  /**
   * Checks the predicted class against the actual class for given images
   * @param images to verify
   * @return accuracy between 0 and 1
   */
  double CalculateAccuracy(const std::vector<Image> &images);

  /**
   * Calculates likelihood scores for classes 0-9 for an image 
   * @param image to calculate scores for
   */
  void CalculateLikelihoodScores(Image &image);

  /**
   * Returns the class with the highest likelihood score for an image
   * @param image to predict class for
   * @return predicted class
   */
  int GetBestClass(Image image);
  
  double GetScore(size_t num);

 private:
  Model model_;
  std::vector<double> scores_;
};

}

