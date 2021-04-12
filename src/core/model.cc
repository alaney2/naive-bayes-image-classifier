#include <core/model.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::vector;

namespace naivebayes {

Model::Model() {
  prior_count.resize(kNumDigits, 0);
  prior_prob.resize(kNumDigits, 0);
  feature_count_ = vector<vector<vector<vector<size_t>>>>(
      kImageSize, vector<vector<vector<size_t>>>(
          kImageSize, vector<vector<size_t>>(
              kNumShades, vector<size_t>(kNumDigits))));
  feature_prob_ = vector<vector<vector<vector<double>>>>(
      kImageSize, vector<vector<vector<double>>>(
          kImageSize, vector<vector<double>>(
              kNumShades, vector<double>(kNumDigits))));
}

void Model::ParseFile(std::string &file_path) {
  std::ifstream input(file_path);

  if (!input) {
    return;
  }

  while (!input.eof()) {
    Image image;
    input >> image;
    prior_count[image.GetClass()] += 1;
    images_.push_back(image);
    image_count_ += 1;
  }
  
  input.close();
}

void Model::CalculatePriorProbabilities() {
  for (size_t num = 0; num < prior_prob.size(); ++num) {
    prior_prob[num] = (kSmoothingFactor_ + static_cast<double>(prior_count[num])) /
            (kNumDigits * kSmoothingFactor_ + static_cast<double>(image_count_));
  }
}

void Model::TrainModel() {
  CalculatePriorProbabilities();
  CountFeatures();
  CalculateFeatureProbabilities();
}

void Model::CountFeatures() {
  for (Image &image : images_) {
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        size_t shade = image.GetShade(row, col);
        feature_count_[row][col][shade][image.GetClass()] += 1;
      }
    }
  }
}

void Model::CalculateFeatureProbabilities() {
  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t num = 0; num < kNumDigits; ++num) {
          feature_prob_[row][col][shade][num] =
              (kSmoothingFactor_ + static_cast<double>(feature_count_[row][col][shade][num])) /
                  (kNumShades * kSmoothingFactor_ + static_cast<double>(prior_count[num]));
        }
      }
    }
  }
}

std::ostream &operator<<(std::ostream &os, Model &model) {
  for (size_t num = 0; num < kNumDigits; ++num) {
    os << model.prior_prob[num] << std::endl;
    for (size_t shade = 0; shade < kNumShades; ++shade) {
      for (size_t row = 0; row < kImageSize; ++row) {
        for (size_t col = 0; col < kImageSize; ++col) {
          os << model.feature_prob_[row][col][shade][num] << " ";
        }
        os << std::endl;
      }
    }
  }
  
  return os;
}

std::istream &operator>>(std::istream &is, Model &model) {
  std::string line;
  
  for (size_t num = 0; num < kNumDigits; ++num) {
    getline(is, line);
    model.prior_prob[num] = std::stod(line);

    for (size_t shade = 0; shade < kNumShades; ++shade) {
      for (size_t row = 0; row < kImageSize; ++row) {
        std::string feature;
        getline(is, line);
        std::istringstream ss(line);
        for (size_t col = 0; col < kImageSize; ++col) {
          ss >> feature;
          model.feature_prob_[row][col][shade][num] = std::stod(feature);
        }
      }
    }
  }
  
  return is;
}

const std::vector<Image> Model::GetImages() {
  return images_;
}

const double Model::GetFeatureCount(size_t row, size_t col, size_t shade, size_t num) {
  return feature_count_[row][col][shade][num];
}

const double Model::GetFeatureProbability(size_t row, size_t col, size_t shade, size_t num) {
  return feature_prob_[row][col][shade][num];
}

const double Model::GetPriorProbability(size_t num) {
  return prior_prob[num];
}

}  // namespace naivebayes
