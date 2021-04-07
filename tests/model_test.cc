#include <core/model.h>

#include <catch2/catch.hpp>
#include <iostream>

using naivebayes::Image;

TEST_CASE("Check that 126 is the best class") {
  REQUIRE(naivebayes::Model().GetBestClass() == "CS 126");
}

TEST_CASE("Model") {
  naivebayes::Model model;
  std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/sample.txt";
  model.ParseFile(file);
  model.TrainModel();
  SECTION("Correct class") {
    REQUIRE(model.images_[0].GetClass() == 5);
    REQUIRE(model.images_[1].GetClass() == 0);
    REQUIRE(model.images_[3].GetClass() == 4);
  }
  
  SECTION("Shaded vs unshaded") {
    REQUIRE(model.GetImages()[0].GetShades()[0][0] == 0);
    REQUIRE(model.GetImages()[0].GetShades()[27][27] == 0);
    REQUIRE(model.GetImages()[0].GetShades()[11][24] == 0);

    REQUIRE(model.GetImages()[0].GetShades()[5][17] == 1);
    REQUIRE(model.GetImages()[0].GetShades()[5][18] == 1);
    REQUIRE(model.GetImages()[0].GetShades()[6][23] == 1);
  }
  
  SECTION("Feature count") {
    REQUIRE(model.feature_count[0][0][0][0] == 1);
    REQUIRE(model.feature_count[15][15][0][3] == 0);
    REQUIRE(model.feature_count[3][10][0][4] == 2);
    
    REQUIRE(model.feature_count[15][10][1][4] == 2);
    REQUIRE(model.feature_count[17][11][1][4] == 0);
    REQUIRE(model.feature_count[23][19][1][4] == 1);
  }
  
  SECTION("Images") {
    REQUIRE(model.GetImages().size() == 4);
  }
}

TEST_CASE("Probabilities") {
  naivebayes::Model model;
  std::string file = "../data/sample.txt";
  model.ParseFile(file);
  REQUIRE(model.images_[0].GetShades()[0][0] == 0);
  REQUIRE(model.feature_count[0][0][0][0] == 0);
  REQUIRE(model.images_[0].GetClass() == 5);
}

/*

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

*/
