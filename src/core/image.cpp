#include "core/image.h"

namespace naivebayes {

std::istream& operator>>(std::istream& is, Image& image) {
  std::string line;
  getline(is, line);

  image.class_ = std::stoi(line);

  for (size_t row = 0; row < kImageSize; ++row) {
    getline(is, line);
    for (size_t col = 0; col < kImageSize; ++col) {
      if (line[col] == '+' || line[col] == '#') {
        image.shades_[row][col] = 1;
      } else {
        image.shades_[row][col] = 0;
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

int* Image::GetShades() {
  return reinterpret_cast<int*>(shades_);
}

}
