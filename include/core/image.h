#ifndef NAIVE_BAYES_IMAGE_H
#define NAIVE_BAYES_IMAGE_H

#include <cstddef>
#include <iostream>

//#include "model.h"

namespace naivebayes {

const size_t kNumShades = 2;
const size_t kNumDigits = 10;
const size_t kImageSize = 28;

class Image {

 public:
  friend std::istream& operator>>(std::istream& is, Image& image);
  friend std::ostream& operator<<(std::ostream& is, Image& image);
  int GetClass();
  int* GetShades();
  
  int shades_[kImageSize][kImageSize];

 private:
  int class_;
};

}

#endif  // NAIVE_BAYES_IMAGE_H
