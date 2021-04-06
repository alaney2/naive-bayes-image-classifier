#include <core/model.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::vector;

namespace naivebayes {

std::string Model::GetBestClass() const {
  return "CS 126";
}

void Model::ParseFile(std::string& file_path) {
  std::ifstream input(file_path);

  Image image;
  while (input.is_open() && !input.eof()) {
    input >> image;
    prior_count_[image.GetClass()] += 1;
    images_.push_back(image);
  }

  CalculatePriorProbabilities();
  input.close();
}

void Model::CalculatePriorProbabilities() {
  for (size_t i = 0; i < prior_prob_.size(); ++i) {
    prior_prob_[i] = (constant_ + prior_count_[i]) / static_cast<double>(kNumDigits * constant_ + kTotalImages);
  }
}

void Model::TrainModel() {
  for (Image & image : images_) {
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        if (image.GetShades() == 0) {
          feature_count_[row][col][0][image.GetClass()] += 1;
        } else {
          feature_count_[row][col][1][image.GetClass()] += 1;
        }
      }
    }
  }
  CalculateFeatureProbabilities();
}

void Model::CalculateFeatureProbabilities() {
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t c = 0; c < kNumDigits; ++c) {
          feature_prob_[row][col][shade][c] = (constant_ + feature_count_[row][col][shade][c]) /
              (static_cast<double>(2 * constant_ + prior_count_[c]));
        }
      }
    }
  }
}

void Model::WriteDataToFile() {
  std::ofstream new_file;
  new_file.open(kModelFile_);
  if (!new_file) {
    for (size_t num = 0; num < kNumDigits; ++num) {
//      new_file << num << " ";
      for (size_t shade = 0; shade < kNumShades; ++shade) {
//        new_file << shade << std::endl;
        for (size_t row = 0; row < kImageSize; ++row) {
          for (size_t col = 0; col < kImageSize; ++col) {
            new_file << feature_prob_[row][col][shade][num] << " ";
          }
          new_file << std::endl;
        }
      }
    }
  }
}

void Model::TakeInModelData() {
  std::ifstream new_file;
  new_file.open(kModelFile_);

  std::string line;
  if (new_file) {
    while (getline(new_file, line)) {
      std::stringstream line_stream(line);

      std::string str;
//      size_t digit;
//      size_t shade;
//      line_stream >> digit >> shade;
      for (size_t num = 0; num < kNumDigits; ++num) {
        for (size_t shade = 0; shade < kNumShades; ++shade) {
          for (size_t row = 0; row < kNumDigits; ++row) {
            for (size_t col = 0; col < kNumDigits; ++col) {
              while (line_stream >> str) {
                feature_prob_[row][col][shade][num] = std::stoi(str);
              }
            }
          }
        }
      }
    }
  }
}

}  // namespace naivebayes
