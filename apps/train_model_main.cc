#include <core/model.h>

#include <iostream>

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  std::cout << "Welcome to " << naivebayes::Model().GetBestClass() << std::endl;

  naivebayes::Model model;
  std::string file = "../data/training.txt";
  model.ParseFile(file);
//  model.TrainModel();
//  model.WriteDataToFile();
  std::cout << model.feature_prob_[0][0][0][4] << std::endl;

  for (size_t i = 0; i < 28; ++i) {
    for (size_t j = 0; j < 28; ++j) {
      std::cout << model.GetImages()[0].shades_[i][j];
    }
    std::cout << std::endl;
  }
  return 0;
}
