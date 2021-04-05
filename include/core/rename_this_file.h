#include <string>
#include <vector>

namespace naivebayes {

class Bayes {
 public:
  std::string GetBestClass() const;

  friend std::istream& operator>>(std::istream& is, std::vector<std::vector<std::vector<std::vector<double>>>> vector);
  friend std::ostream& operator<<(std::ostream& is, std::vector<std::vector<std::vector<std::vector<double>>>> vector);

 private:
  std::vector<std::vector<std::vector<std::vector<double>>>> vector_;
  const size_t kNumShades = 2;
  const size_t kNumDigits = 10;
  const size_t kImageSize_ = 28;
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
