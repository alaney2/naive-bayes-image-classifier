#include <core/model.h>

#include <iostream>

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.

  std::cout << "Welcome to " << naivebayes::Model().GetBestClass() << std::endl;
  
  naivebayes::Model model;
  std::string file = "../data/model.txt";
  model.LoadModelData(file);
  std::cout << model.GetPriorProbability(0) << std::endl;
  std::cout << model.GetFeatureProbability(0,0,0,1) << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << model.GetPriorProbability(i) << std::endl;
  }
  return 0;
}
