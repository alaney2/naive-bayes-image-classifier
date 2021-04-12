#include "core/image.h"
#include "core/model.h"

namespace naivebayes {

Image::Image(size_t image_size) {
  kImageSize_ = image_size;
}

std::istream& operator>>(std::istream &is, Image &image) {
  const std::vector<char> shaded_chars = { '+', '#'};
  
  std::string digit;
  getline(is, digit);
  image.class_ = std::stoi(digit);
  
  std::string line;
  for (size_t row = 0; row < image.kImageSize_; ++row) {
    getline(is, line);
    image.shades_.resize(image.kImageSize_, std::vector<size_t>(image.kImageSize_, 0));
    for (size_t col = 0; col < image.kImageSize_; ++col) {
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

size_t Image::GetImageSize() {
  return kImageSize_;
}

void Image::SetShade(size_t row, size_t col, size_t shade) {
  shades_[row][col] = shade;
}

}
