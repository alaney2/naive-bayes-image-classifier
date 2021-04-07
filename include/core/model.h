#include <array>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  std::string GetBestClass() const;
  void ParseFile(std::string& file_path);
  void CalculatePriorProbabilities();
  void CalculateFeatureProbabilities();
  void TrainModel();
  void WriteDataToFile();
  void TakeInModelData();
  
  std::vector<Image> GetImages();
  std::vector<std::vector<std::vector<std::vector<int>>>> GetFeatureCount();
  std::vector<std::vector<std::vector<std::vector<double>>>> GetFeatureProbability();
  
 private:
  std::string kFilePath_ = "../data/training.txt";
  std::string kModelFile_ = "../data/model_data.txt";
  size_t kTotalImages = 5000;
  double constant_ = 1;

  std::vector<Image> images_;
  std::vector<std::vector<std::vector<std::vector<int>>>> feature_count_;
  std::vector<std::vector<std::vector<std::vector<double>>>> feature_prob_;

  std::vector<size_t> prior_count;
  std::vector<double> prior_prob;
};

}  // namespace naivebayes

/*

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

*/
