#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

namespace naivebayes {

const size_t kNumShades = 2;
const size_t kNumDigits = 10;
const size_t kImageSize = 28;

class Image {

 public:
  /**
   * Stores shaded pixels in a 2d vector, with 0 being unshaded and 1 being shaded
   * @param is input stream
   * @param image class
   * @return input stream
   */
  friend std::istream& operator>>(std::istream& is, Image& image);
  
  size_t GetClass();
  std::vector<std::vector<int>> GetShades();
  
  
 private:
  size_t class_;
  std::vector<std::vector<int>> shades_;
};

}
