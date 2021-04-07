#include <array>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  friend std::ostream& operator<<(std::ostream& os, Model& model);

  /**
   * Predicts the class
   * @return string of class
   */
  std::string GetBestClass() const;
  
  /**
   * Reads given file and stores images and priors in vectors
   * Calls CalculatePriorProbabilities()
   * @param file_path given file
   */
  void ParseFile(std::string& file_path);
  
  /**
   * Calculates and stores logarithmic probabilities of priors in a vector
   */
  void CalculatePriorProbabilities();

  /**
   * Gets a count of all the features and stores them in a 4d vector
   * Calls CalculateFeatureProbabilities()
   */
  void TrainModel();

  /**
   * 
   */
  void CalculateFeatureProbabilities();
  
  /**
   * 
   * @param file_name 
   */
  void WriteDataToFile(std::string &file_name);
  
  /**
   * 
   * @param file_name 
   */
  void TakeInModelData(std::string &file_name);
  
  std::vector<Image> GetImages();
  std::vector<std::vector<std::vector<std::vector<int>>>> GetFeatureCount();
  std::vector<std::vector<std::vector<std::vector<double>>>> GetFeatureProbability();
  
 private:
  std::string kFilePath_ = "../data/training.txt";
  size_t kTotalImages = 5000;
  double constant_ = 1;

  std::vector<Image> images_;
  std::vector<std::vector<std::vector<std::vector<int>>>> feature_count_;
  std::vector<std::vector<std::vector<std::vector<double>>>> feature_prob_;

  std::vector<size_t> prior_count;
  std::vector<double> prior_prob;
};

}  // namespace naivebayess
