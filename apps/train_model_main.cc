#include <core/model.h>
#include <core/classifier.h>

#include <iostream>

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.
  
  naivebayes::Model model;
  std::string path = "../data/testing.txt";
  model.ParseFile(path);
//  model.TrainModel();
//  std::string write = "../data/model.txt";
//  model.WriteDataToFile(write);
  std::string file = "../data/model.txt";
  model.LoadModelData(file);
  
  naivebayes::Classifier classifier(model);

  std::cout << classifier.CalculateAccuracy(model.GetImages());
  
  return 0;
}
