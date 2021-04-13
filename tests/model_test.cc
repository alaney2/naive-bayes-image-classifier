#include <core/model.h>
#include <core/classifier.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>


namespace naivebayes {
TEST_CASE("Model") {
  naivebayes::Model model(5);
  std::string file =
      "../../../../../../tests/testing_data.txt";
  model.ParseFile(file);
  model.TrainModel();
  SECTION("Correct class") {
    REQUIRE(model.GetImages()[0].GetClass() == 0);
    REQUIRE(model.GetImages()[1].GetClass() == 1);
    REQUIRE(model.GetImages()[2].GetClass() == 2);
    REQUIRE(model.GetImages()[5].GetClass() == 5);
    REQUIRE(model.GetImages()[8].GetClass() == 8);
    REQUIRE(model.GetImages()[9].GetClass() == 9);
  }

  SECTION("Shaded") {
    REQUIRE(model.GetImages()[0].GetShade(1, 1) == 1);
    REQUIRE(model.GetImages()[0].GetShade(1, 2) == 1);
    REQUIRE(model.GetImages()[0].GetShade(2, 1) == 1);
    REQUIRE(model.GetImages()[1].GetShade(2, 2) == 1);
    REQUIRE(model.GetImages()[1].GetShade(3, 3) == 1);
    REQUIRE(model.GetImages()[3].GetShade(4, 2) == 1);
    REQUIRE(model.GetImages()[6].GetShade(0, 1) == 1);
    REQUIRE(model.GetImages()[6].GetShade(2, 2) == 1);
    REQUIRE(model.GetImages()[7].GetShade(3, 2) == 1);
    REQUIRE(model.GetImages()[9].GetShade(4, 3) == 1);
  }

  SECTION("Unshaded") {
    REQUIRE(model.GetImages()[0].GetShade(0, 0) == 0);
    REQUIRE(model.GetImages()[0].GetShade(2, 2) == 0);
    REQUIRE(model.GetImages()[1].GetShade(0, 4) == 0);
    REQUIRE(model.GetImages()[2].GetShade(1, 2) == 0);
    REQUIRE(model.GetImages()[4].GetShade(1, 2) == 0);
    REQUIRE(model.GetImages()[5].GetShade(0, 4) == 0);
    REQUIRE(model.GetImages()[5].GetShade(3, 4) == 0);
    REQUIRE(model.GetImages()[8].GetShade(3, 2) == 0);
    REQUIRE(model.GetImages()[8].GetShade(1, 2) == 0);
    REQUIRE(model.GetImages()[9].GetShade(1, 2) == 0);
    REQUIRE(model.GetImages()[9].GetShade(4, 4) == 0);
  }

  SECTION("Feature count") {
    REQUIRE(model.GetFeatureCount(0, 0, 0, 0) == 1);
    REQUIRE(model.GetFeatureCount(4, 4, 0, 3) == 1);
    REQUIRE(model.GetFeatureCount(3, 4, 0, 4) == 1);

    REQUIRE(model.GetFeatureCount(4, 0, 1, 4) == 0);
    REQUIRE(model.GetFeatureCount(1, 1, 1, 4) == 1);
    REQUIRE(model.GetFeatureCount(3, 1, 1, 4) == 0);
  }

  SECTION("Images") {
    REQUIRE(model.GetImages().size() == 10);
  }
}

TEST_CASE("Probabilities") {
  Model model(3);
  Image image(3);
  
  //  REQUIRE(model.GetImages()[0].GetShades()[0][0] == 0);
  //  REQUIRE(model.GetImages()[0].GetShades()[7][12] == 1);
  //  REQUIRE(model.GetFeatureCount()[0][0][0][0] == 1);
  //  REQUIRE(model.GetImages()[0].GetClass() == 5);
}

TEST_CASE("Operator Overloading") {
  SECTION("Loading model") {
    Model model(5);
    std::string file =
        "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/tests/testing_data.txt";
    std::ifstream load(file);
    load >> model;
    REQUIRE(model.GetPriorProbability(0) == 0.0958084);
    REQUIRE(model.GetFeatureProbability(0, 0, 0, 0) == 0.997921);
  }
  
  SECTION("Saving model") {
    Model model(5);
    std::string write = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/tests/testing_model.txt";
    std::ofstream new_file(write);
    new_file << model;
  }
}

}
