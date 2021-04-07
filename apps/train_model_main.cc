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
  model.TrainModel();
//  std::string new_file = "../data/test_model.txt";
  
  std::string model_file = "../data/model.txt";
  model.WriteDataToFile(model_file);

//  model.WriteDataToFile(new_file);
//  std::cout << model.GetFeatureProbability()[0][0][0][0] << std::endl;
//  std::cout << model.GetFeatureProbability()[0][0][0][5] << std::endl;
  
//  model.TakeInModelData(new_file);
//  std::cout << model.GetFeatureProbability()[0][0][0][0] << std::endl;
//  std::cout << model.GetFeatureProbability()[0][0][0][5] << std::endl;
  
  return 0;
}
