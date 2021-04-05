#ifndef NAIVE_BAYES_IMAGE_H
#define NAIVE_BAYES_IMAGE_H

#include <cstddef>
#include "rename_this_file.h"

namespace naivebayes {

class Image {

 public:
  friend std::istream& operator>>(std::istream& is, Image& image);
  friend std::ostream& operator<<(std::ostream& is, Image& image);

 private:
  double features[kImageSize][kImageSize];

};

}

#endif  // NAIVE_BAYES_IMAGE_H
