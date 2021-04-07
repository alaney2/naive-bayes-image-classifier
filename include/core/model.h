#include <array>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  friend std::ostream& operator<<(std::ostream& os, Model& model);

  std::string GetBestClass() const;
  void ParseFile(std::string& file_path);
  void CalculatePriorProbabilities();
  void CalculateFeatureProbabilities();
  void TrainModel();
  void WriteDataToFile(std::string &file_name);
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
