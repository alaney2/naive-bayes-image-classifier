#include <core/model.h>

#include <catch2/catch.hpp>


TEST_CASE("Check that 126 is the best class") {
  REQUIRE(naivebayes::Bayes().GetBestClass() == "CS 126");
}

TEST_CASE("Model") {

}

/*

You can (and should) create more test files; this project is too big
for all tests to be in the same file. Remember that, for each file (foo.cc)
containing non-trivial code, you should have a corresponding test file
(foo_test.cc)

Make sure to add any files that you create to CMakeLists.txt.

*/
