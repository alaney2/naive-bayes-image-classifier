#include <core/classifier.h>
#include <core/model.h>

#include <catch2/catch.hpp>
#include <fstream>

namespace naivebayes {

TEST_CASE("Likelihood scores") {
  Model model(5);
  std::string file = "../../../../../../tests/testing_model.txt";
  std::ifstream load(file);
  load >> model;

  Classifier classifier(model);
  Image image(5);

  SECTION("Likelihood scores for 0") {
    std::vector<std::vector<size_t>> shades = {{0, 0, 0, 0, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 1, 0, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 0, 0, 0, 0}};
    image.SetShadeVector(shades);
    classifier.CalculateLikelihoodScores(image);
    REQUIRE(classifier.GetScore(0) == Approx(-12.4392002957));
    for (size_t i = 0; i < 10; ++i) {
      REQUIRE(classifier.GetScore(i) < -12.4392002957);
    }
  }

  SECTION("Likelihood scores for 0") {
    std::vector<std::vector<size_t>> shades = {{0, 1, 1, 1, 0},
                                               {0, 1, 0, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 0, 0, 1, 0},
                                               {0, 0, 0, 1, 0}};
    image.SetShadeVector(shades);
    classifier.CalculateLikelihoodScores(image);
    REQUIRE(classifier.GetScore(9) == Approx(-12.4392002957));
    for (size_t i = 0; i < 10; ++i) {
      REQUIRE(classifier.GetScore(i) < -12.4392002957);
    }
  }
}

TEST_CASE("Best class") {
  Model model(5);
  std::string file = "../../../../../../tests/testing_model.txt";
  std::ifstream load(file);
  load >> model;

  Classifier classifier(model);
  Image image(5);
  
  SECTION("Best class for 0") {
    std::vector<std::vector<size_t>> shades = {{0, 0, 0, 0, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 1, 0, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 0, 0, 0, 0}};
    image.SetShadeVector(shades);
    classifier.CalculateLikelihoodScores(image);
    REQUIRE(classifier.GetBestClass(image) == 0);
  }

  SECTION("Best class for 9") {
    std::vector<std::vector<size_t>> shades = {{0, 1, 1, 1, 0},
                                               {0, 1, 0, 1, 0},
                                               {0, 1, 1, 1, 0},
                                               {0, 0, 0, 1, 0},
                                               {0, 0, 0, 1, 0}};
    image.SetShadeVector(shades);
    classifier.CalculateLikelihoodScores(image);
    REQUIRE(classifier.GetBestClass(image) == 9);
  }
}

TEST_CASE("Accuracy") {
  Model model(5);
  std::string file = "../../../../../../tests/testing_data.txt";
  model.ParseFile(file);

  std::string model_file = "../../../../../../tests/testing_model.txt";
  std::ifstream load_file(model_file);
  load_file >> model;
  Classifier classifier(model);
  REQUIRE(classifier.CalculateAccuracy(model.GetImages()) == 1);
}
}
