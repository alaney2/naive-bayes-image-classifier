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
  prior_count.resize(kNumDigits, 0);
  
  Image image;
  while (!input.eof()) {
    input >> image;
    prior_count[image.GetClass()] += 1;
//    prior_count_[image.GetClass()] += 1;
    images_.push_back(image);
  }

  CalculatePriorProbabilities();
  input.close();
}

void Model::CalculatePriorProbabilities() {
  prior_prob.resize(kNumDigits, 0);
  
  for (size_t i = 0; i < prior_prob.size(); ++i) {
    prior_prob[i] = log((constant_ + prior_count[i]) / static_cast<double>(kNumDigits * constant_ + kTotalImages));
//    prior_prob_[i] = log((constant_ + prior_count_[i]) / static_cast<double>(kNumDigits * constant_ + kTotalImages));
  }
}

void Model::TrainModel() {
  Initialize4DVector(feature_count);
  
  for (Image & image : images_) {
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        if (image.GetShades()[row][col] == 0) {
          feature_count[row][col][0][image.GetClass()] += 1;
        } else {
          feature_count[row][col][1][image.GetClass()] += 1;
        }
      }
    }
  }
  CalculateFeatureProbabilities();
}

void Model::CalculateFeatureProbabilities() {
  Initialize4DVector(feature_prob);

  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t c = 0; c < kNumDigits; ++c) {
          feature_prob[row][col][shade][c] = log((constant_ + feature_count[row][col][shade][c]) /
              (static_cast<double>(2 * constant_ + prior_count[c])));
        }
      }
    }
  }
}

void Model::WriteDataToFile() {
  std::fstream new_file;
  new_file.open(kModelFile_, std::fstream::in | std::fstream::out | std::fstream::app);
//  new_file.open(kModelFile_, std::ios::out);
  if (!new_file) {
    new_file.open(kModelFile_, std::fstream::in | std::fstream::out | std::fstream::trunc);
    std::cout << "here" << std::endl;
    for (size_t num = 0; num < kNumDigits; ++num) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t row = 0; row < kImageSize; ++row) {
          for (size_t col = 0; col < kImageSize; ++col) {
            new_file << feature_prob[row][col][shade][num] << " ";
          }
          new_file << std::endl;
        }
      }
    }
    new_file.close();
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
      for (size_t num = 0; num < kNumDigits; ++num) {
        for (size_t shade = 0; shade < kNumShades; ++shade) {
          for (size_t row = 0; row < kNumDigits; ++row) {
            for (size_t col = 0; col < kNumDigits; ++col) {
              while (line_stream >> str) {
                feature_prob[row][col][shade][num] = std::stoi(str);
              }
            }
          }
        }
      }
    }
  }
}

std::vector<Image> Model::GetImages() {
  return images_;
}

void Model::Initialize4DVector(
    std::vector<std::vector<std::vector<std::vector<double>>>> &vec) {
  
//  vector<double> level4(kNumDigits, 0);
//  vector<vector<double>> level3(kNumShades, level4);
//  vector<vector<vector<double>>> level2(kImageSize, level3);
  
  for (size_t row = 0; row < kImageSize; ++row) {
    vec.emplace_back();
    for (size_t col = 0; col < kImageSize; ++col) {
      vec[row].emplace_back();
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        vec[row][col].emplace_back();
        for (size_t num = 0; num < kNumDigits; ++num) {
          vec[row][col][shade].emplace_back(0);
        }
      }
    }
  }
}

}  // namespace naivebayes
