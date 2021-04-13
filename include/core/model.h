#pragma once

#include <array>
#include <string>
#include <vector>

#include "image.h"
#include "common.h"

namespace naivebayes {

class Model {
 public:
  Model(size_t image_size);
  
  /**
   * 
   * @param os 
   * @param model 
   * @return 
   */
  friend std::ostream& operator<<(std::ostream& os, Model& model);
  
  /**
   * Reads a file and stores feature probabilities and prior probabilities
   * @param is 
   * @param model 
   * @return 
   */
  friend std::istream& operator>>(std::istream& is, Model& model);
  
  /**
   * Reads given file and stores images and priors
   * @param file_path given file
   */
  void ParseFile(std::string& file_path);
  
  /**
   * Calculates prior probabilities
   */
  void CalculatePriorProbabilities();

  /**
   * Calculates everything needed for Bayes' Theorem
   */
  void TrainModel();

  /**
   * 
   */
  void CountFeatures();

  /**
   * Calculates feature probabilities
   */
  void CalculateFeatureProbabilities();

  const size_t GetFeatureCount(size_t row, size_t col, size_t shade, size_t num);
  const double GetPriorProbability(size_t num);
  const double GetFeatureProbability(size_t row, size_t col, size_t shade, size_t num);

  const std::vector<Image> GetImages();

 private:
  size_t kImageSize_;
  size_t image_count_ = 0;
  const double kSmoothingFactor_ = 1.0;
//  static size_t kImageSize_;
  
  std::vector<Image> images_;
  std::vector<std::vector<std::vector<std::vector<size_t>>>> feature_count_;
        // (row, column, shade, number)
  std::vector<std::vector<std::vector<std::vector<double>>>> feature_prob_;
        // (row, column, shade, number)
  std::vector<size_t> prior_count_;  // (number)
  std::vector<double> prior_prob_;   // (number)
};

}  // namespace naivebayes
