#include "xpath.h"

#include <fstream>
#include <iostream>
#include <string>
int main() {
  std::ifstream infile("xml/expr.txt");
  std::string line;
  std::getline(infile, line);
  print(line);
  main_xpath("xml/example.xml", line.c_str());
}
