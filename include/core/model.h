#include <array>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

//const size_t kNumShades = 2;
//const size_t kNumDigits = 10;
//const size_t kImageSize = 28;

class Bayes {
 public:
  std::string GetBestClass() const;
  void ParseFile(std::string& file_path);
  void CalculatePriorProbabilities();
  void TrainModel();

 private:
  std::string kFilePath_ = "/data/training.txt";
  size_t kTotalImages = 5000;
  size_t constant_ = 1;
  std::vector<Image> images_;
  std::array<double, kNumDigits> prior_count = { 0 };
  std::array<double, kNumDigits> prior_prob = { 0 };

  double features_[kNumDigits][kNumDigits][kNumShades][kNumDigits];
};


}  // namespace naivebayes

/*
TODO: rename this file. You'll also need to modify CMakeLists.txt.

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

*/
