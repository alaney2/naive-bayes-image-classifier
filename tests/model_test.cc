#include <core/model.h>

#include <catch2/catch.hpp>

using naivebayes::Image;
using naivebayes::Image;

TEST_CASE("Check that 126 is the best class") {
  REQUIRE(naivebayes::Model().GetBestClass() == "CS 126");
}

TEST_CASE("Model") {
  naivebayes::Model model;
  std::string file = "/Users/alaney/CLionProjects/Cinder/my-projects/naive-bayes-alaney2/data/sample.txt";
  model.ParseFile(file);
//  REQUIRE(model.feature_count_[0][0][0][0] == 0);
  REQUIRE(model.images_[0].GetClass() == 0);
//  model.WriteDataToFile();
}

/*

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

*/
