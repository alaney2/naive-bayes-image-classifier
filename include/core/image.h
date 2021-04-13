#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
#include "common.h"

namespace naivebayes {

class Image {
  
 public:
  Image();
  Image(size_t image_size);
  /**
   * Stores shaded pixels in a 2d vector, with 0 being unshaded and 1 being shaded
   * @param is input stream
   * @param image class
   * @return input stream
   */
  friend std::istream& operator>>(std::istream& is, Image& image);
  
  /**
   * 
   * @param vector_size 
   */
  void ResizeShadeVector(size_t vector_size);
  
  const size_t GetClass() const;
  const size_t GetShade(size_t row, size_t col) const;
  size_t GetImageSize();
  void SetShade(size_t row, size_t col, size_t shade);
  void SetImageSize(size_t image_size);
  void SetShadeVector(std::vector<std::vector<size_t>> &shades);
  
 private:
  size_t kImageSize_;
  size_t class_;
  std::vector<std::vector<size_t>> shades_;
};

}
