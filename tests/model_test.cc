#include <core/model.h>

#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("Check that 126 is the best class") {
  REQUIRE(naivebayes::Model().GetBestClass() == "CS 126");
}

TEST_CASE("Model") {
  naivebayes::Model model;
  std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/sample.txt";
  model.ParseFile(file);
  model.TrainModel();
  SECTION("Correct class") {
    REQUIRE(model.GetImages()[0].GetClass() == 5);
    REQUIRE(model.GetImages()[1].GetClass() == 0);
    REQUIRE(model.GetImages()[3].GetClass() == 4);
  }
  
  SECTION("Shaded vs unshaded") {
    REQUIRE(model.GetImages()[0].GetShade(0,0) == 0);
    REQUIRE(model.GetImages()[0].GetShade(27,27) == 0);
    REQUIRE(model.GetImages()[0].GetShade(11,24) == 0);

    REQUIRE(model.GetImages()[0].GetShade(5,17) == 1);
    REQUIRE(model.GetImages()[0].GetShade(5,18) == 1);
    REQUIRE(model.GetImages()[0].GetShade(6,23) == 1);
  }
  
  SECTION("Feature count") {
    REQUIRE(model.GetFeatureCount(0,0,0,0) == 1);
    REQUIRE(model.GetFeatureCount(15,15,0,3) == 0);
    REQUIRE(model.GetFeatureCount(3,10,0,4) == 2);
    
    REQUIRE(model.GetFeatureCount(15,10,1,4) == 2);
    REQUIRE(model.GetFeatureCount(17,11,1,4) == 0);
    REQUIRE(model.GetFeatureCount(23,19,1,4) == 1);
  }
  
  SECTION("Images") {
    REQUIRE(model.GetImages().size() == 4);
  }
  std::string path = "model.txt";
  model.WriteDataToFile(path);
}

TEST_CASE("Probabilities") {
  naivebayes::Model model;
  std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/sample.txt";
  model.ParseFile(file);
  model.TrainModel();
//  REQUIRE(model.GetImages()[0].GetShades()[0][0] == 0);
//  REQUIRE(model.GetImages()[0].GetShades()[7][12] == 1);
//  REQUIRE(model.GetFeatureCount()[0][0][0][0] == 1);
//  REQUIRE(model.GetImages()[0].GetClass() == 5);
}

TEST_CASE("Loading model") {
  naivebayes::Model model;
  std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/model.txt";
  model.LoadModelData(file);
  REQUIRE(model.GetPriorProbability(0) == -2.34541);
  REQUIRE(model.GetFeatureProbability(0,0,0,0) == -0.00208117);
}
