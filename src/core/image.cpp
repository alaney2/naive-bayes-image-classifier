//
// Created by Alan Yao on 4/5/21.
//

#include "core/image.h"

std::istream& naivebayes::operator>>(std::istream& is,
                                     naivebayes::Image& image) {
  std::string line;
  getline(is, line);
  image.class_ = std::stoi(line);

  for (size_t row = 0; row < kImageSize; ++row) {
    getline(is, line);
    for (size_t col = 0; col < kImageSize; ++col) {
      if (line[col] == ' ') {
        image.shades_[row][col] = 0;
      } else {
        image.shades_[row][col] = 1;
      }
    }
  }

  return is;
}

std::ostream& naivebayes::operator<<(std::ostream& os,
                                     naivebayes::Image& image) {

  return os;
}

int naivebayes::Image::GetClass() {
  return class_;
}

int* naivebayes::Image::GetShades() {
  return shades_[0];
}
