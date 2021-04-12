#include <core/classifier.h>
#include <core/model.h>

#include <fstream>
#include <iostream>

// TODO: You may want to change main's signature to take in argc and argv
int main() {
  // TODO: Replace this with code that reads the training data, trains a model,
  // and saves the trained model to a file.
  
  naivebayes::Model model;
  std::string path = "../data/training.txt";
  model.ParseFile(path);
//  model.TrainModel();
//  std::string write = "../data/model.txt";
//  std::ofstream new_file(write);
//  new_file << model;
  std::string file = "../data/model.txt";
  std::ifstream load_file(file);
  load_file >> model;
  
//  naivebayes::Classifier classifier(model);

//  std::cout << classifier.CalculateAccuracy(model.GetImages());
  
  return 0;
}
