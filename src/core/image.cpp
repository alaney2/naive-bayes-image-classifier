#include "core/image.h"

namespace naivebayes {

std::istream& operator>>(std::istream& is, Image& image) {
  std::string line;
  getline(is, line);

  image.class_ = std::stoi(line);
  image.shades_.resize(kImageSize, std::vector<int>(kImageSize, 0));
  
  for (size_t row = 0; row < kImageSize; ++row) {
    getline(is, line);
    for (size_t col = 0; col < kImageSize; ++col) {
      if (line[col] == '+' || line[col] == '#') {
        image.shades_[row][col] = 1;
      }
    }
  }

  return is;
}

std::ostream& operator<<(std::ostream& os, naivebayes::Image& image) {
  return os;
}

int Image::GetClass() {
  return class_;
}
std::vector<std::vector<int>> Image::GetShades() {
  return shades_;
}

}
