#include <core/model.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::vector;

namespace naivebayes {

void Model::ParseFile(std::string &file_path) {
  std::ifstream input(file_path);
  prior_count.resize(kNumDigits, 0);

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
  prior_prob.resize(kNumDigits, 0);

  for (size_t num = 0; num < prior_prob.size(); ++num) {
    prior_prob[num] = (constant_ + static_cast<double>(prior_count[num])) /
            (kNumDigits * constant_ + static_cast<double>(image_count_));
  }
}

void Model::TrainModel() {
  CalculatePriorProbabilities();
  CountFeatures();
  CalculateFeatureProbabilities();
}

void Model::CalculateFeatureProbabilities() {
  feature_prob_ = vector<vector<vector<vector<double>>>>(
      kImageSize, vector<vector<vector<double>>>(
                      kImageSize, vector<vector<double>>(
                                      kNumShades, vector<double>(kNumDigits))));

  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t num = 0; num < kNumDigits; ++num) {
          feature_prob_[row][col][shade][num] =
              (constant_ + feature_count_[row][col][shade][num]) /
                  (2 * constant_ + static_cast<double>(prior_count[num]));
        }
      }
    }
  }
}

void Model::WriteDataToFile(std::string &file_name) {
  std::ofstream new_file(file_name);
  
  for (size_t num = 0; num < kNumDigits; ++num) {
    new_file << prior_prob[num] << std::endl;
    for (size_t shade = 0; shade < kNumShades; ++shade) {
      for (size_t row = 0; row < kImageSize; ++row) {
        for (size_t col = 0; col < kImageSize; ++col) {
          new_file << feature_prob_[row][col][shade][num] << " ";
        }
        new_file << std::endl;
      }
    }
  }
  new_file.close();
}

void Model::LoadModelData(std::string &file_name) {
  prior_prob.resize(kNumDigits, 0);
  feature_prob_ = vector<vector<vector<vector<double>>>>(
      kImageSize, vector<vector<vector<double>>>(
                      kImageSize, vector<vector<double>>(
                                      kNumShades, vector<double>(kNumDigits))));
  
  std::ifstream new_file(file_name);

  std::string line;
  while (!new_file.eof()) {

    for (size_t num = 0; num < kNumDigits; ++num) {
      getline(new_file, line);
      prior_prob[num] = std::stod(line);
      
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t col = 0; col < kImageSize; ++col) {
          std::string feature;
          getline(new_file, line);
          std::istringstream ss(line);
          for (size_t row = 0; row < kImageSize; ++row) {
            ss >> feature;
            feature_prob_[row][col][shade][num] = std::stod(feature);
          }
        }
      }
    }
  }
}

//std::ostream &operator<<(std::ostream &os, Model &model) {
//  std::string line;
//
//  return os;
//}

void Model::CountFeatures() {
  feature_count_ = vector<vector<vector<vector<int>>>>(
      kImageSize, vector<vector<vector<int>>>(
          kImageSize, vector<vector<int>>(
              kNumShades, vector<int>(kNumDigits))));
  
  for (Image &image : images_) {
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        size_t shade = image.GetShade(row, col);
        feature_count_[row][col][shade][image.GetClass()] += 1;
      }
    }
  }
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
