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
  void SetPriors();

 private:
  std::string kFilePath_ = "/data/trainingimagesandlabels.txt";
  size_t kTotalImages = 5000;
  std::vector<Image> images_;
  std::array<double, kNumDigits> priors_ = { 0 };
};


}  // namespace naivebayes

/*
TODO: rename this file. You'll also need to modify CMakeLists.txt.

You can (and should) create more classes and files in include/core (header
 files) and src/core (source files); this project is too big to only have a
 single class.

Make sure to add any files that you create to CMakeLists.txt.

TODO Delete this comment before submitting your code.
*/
