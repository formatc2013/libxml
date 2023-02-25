
#include "../xpath.h"
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
TEST(testMath, myCubeTest) {

  std::ifstream infile("xml/expr.txt");
  std::string line;
  std::getline(infile, line);
  print(line);
  main_xpath("xml/example.xml", line.c_str());
  auto f = 1;
  auto ff = 11;
  EXPECT_EQ(1000, 1000);
}