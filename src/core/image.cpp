#include "core/image.h"

namespace naivebayes {

std::istream& operator>>(std::istream &is, Image &image) {
  const std::vector<char> shaded_chars = { '+', '#'};
  
  std::string digit;
  getline(is, digit);
  image.class_ = std::stoi(digit);
  
  // Sets the image size
  std::string line;
  int pos = is.tellg();
  getline(is, line);
  kImageSize = line.size();
  is.seekg(pos, std::ios_base::beg);
  
  for (size_t row = 0; row < kImageSize; ++row) {
    getline(is, line);
    image.shades_.resize(kImageSize, std::vector<size_t>(kImageSize, 0));
    for (size_t col = 0; col < kImageSize; ++col) {
      if (std::count(shaded_chars.begin(), shaded_chars.end(), line[col])) {
        image.shades_[row][col] = 1;
      } else {
        image.shades_[row][col] = 0;
      }
    }
  }

  return is;
}

size_t Image::GetClass() const {
  return class_;
}

size_t Image::GetShade(size_t row, size_t col) {
  return shades_[row][col];
}

void Image::SetShade(size_t row, size_t col, size_t shade) {
  shades_[row][col] = shade;
}

}
