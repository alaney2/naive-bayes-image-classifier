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
  }

  CalculatePriorProbabilities();
  input.close();
}

void Model::CalculatePriorProbabilities() {
  prior_prob.resize(kNumDigits, 0);

  for (size_t i = 0; i < prior_prob.size(); ++i) {
    prior_prob[i] =
        log((constant_ + prior_count[i]) /
            static_cast<double>(kNumDigits * constant_ + kTotalImages));
  }
}

void Model::TrainModel() {
  feature_count_ = vector<vector<vector<vector<int>>>>(
      kImageSize, vector<vector<vector<int>>>(
                      kImageSize, vector<vector<int>>(
                                      kNumShades, vector<int>(kNumDigits))));

  for (Image &image : images_) {
    for (size_t row = 0; row < kImageSize; ++row) {
      for (size_t col = 0; col < kImageSize; ++col) {
        if (image.GetShades()[row][col] == 0) {
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
  feature_prob_ = vector<vector<vector<vector<double>>>>(
      kImageSize, vector<vector<vector<double>>>(
                      kImageSize, vector<vector<double>>(
                                      kNumShades, vector<double>(kNumDigits))));

  for (size_t row = 0; row < kImageSize; ++row) {
    for (size_t col = 0; col < kImageSize; ++col) {
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t c = 0; c < kNumDigits; ++c) {
          feature_prob_[row][col][shade][c] =
              log((constant_ + feature_count_[row][col][shade][c]) /
                  (static_cast<double>(2 * constant_ + prior_count[c])));
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

void Model::TakeInModelData(std::string &file_name) {
  prior_prob.resize(kNumDigits, 0);
  feature_prob_ = vector<vector<vector<vector<double>>>>(
      kImageSize, vector<vector<vector<double>>>(
                      kImageSize, vector<vector<double>>(
                                      kNumShades, vector<double>(kNumDigits))));
  
  std::ifstream new_file(file_name);

  std::string line;
  while (getline(new_file, line)) {
    std::istringstream ss(line);
    std::string feature;
    for (size_t num = 0; num < kNumDigits; ++num) {
      ss >> feature;
      prior_prob[num] = std::stod(feature);
      for (size_t shade = 0; shade < kNumShades; ++shade) {
        for (size_t row = 0; row < kNumDigits; ++row) {
          for (size_t col = 0; col < kNumDigits; ++col) {
            //            while (ss >> feature) {
            std::cout << "here" << std::endl;
            ss >> feature;
            std::cout << "there" << std::endl;
            feature_prob_[row][col][shade][num] = std::stod(feature);
            //            }
          }
        }
      }
    }
  }
}

std::ostream &operator<<(std::ostream &os, Model &model) {
  std::string line;

  return os;
}

std::vector<Image> Model::GetImages() {
  return images_;
}

std::vector<std::vector<std::vector<std::vector<int>>>>
Model::GetFeatureCount() {
  return feature_count_;
}

std::vector<std::vector<std::vector<std::vector<double>>>>
Model::GetFeatureProbability() {
  return feature_prob_;
}

std::vector<double> Model::GetPriorProbability() {
  return prior_prob;
}

}  // namespace naivebayes
