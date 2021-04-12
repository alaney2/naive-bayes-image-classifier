#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
#include "common.h"

namespace naivebayes {

class Image {

 public:
  /**
   * Stores shaded pixels in a 2d vector, with 0 being unshaded and 1 being shaded
   * @param is input stream
   * @param image class
   * @return input stream
   */
  friend std::istream& operator>>(std::istream& is, Image& image);
  
  size_t GetClass() const;
  size_t GetShade(size_t row, size_t col);
  void SetShade(size_t row, size_t col, size_t shade);
  
 private:
  size_t class_;
  std::vector<std::vector<size_t>> shades_;
};

}
