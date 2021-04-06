#include <array>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

//const size_t kNumShades = 2;
//const size_t kNumDigits = 10;
//const size_t kImageSize = 28;

class Model {
 public:
  std::string GetBestClass() const;
  void ParseFile(std::string& file_path);
  void CalculatePriorProbabilities();
  void CalculateFeatureProbabilities();
  void TrainModel();
  void WriteDataToFile();
  void TakeInModelData();

  std::vector<Image> images_;
  std::array<double, kNumDigits> prior_count_ = { 0 };
  std::array<double, kNumDigits> prior_prob_ = { 0 };

  double feature_count_[kNumDigits][kNumDigits][kNumShades][kNumDigits];
  double feature_prob_[kNumDigits][kNumDigits][kNumShades][kNumDigits];

 private:
  std::string kFilePath_ = "/data/training.txt";
  std::string kModelFile_ = "/data/model_data.txt";
  size_t kTotalImages = 5000;
  size_t constant_ = 1;


};


}  // namespace naivebayes

/*

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

*/
