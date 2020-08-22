#include "combo_parser.hpp"

#include <iostream>
#include <sstream>

int main(int argc, char **argv)
{
  std::istringstream in("1997,Ford,\"\",\"Ford\",\"Super, luxurious truck\",\"Super, \"\"luxurious\"\" truck\",Super\", luxurious\" truck");
  std::ostringstream out;

  parse(in, std::cout);

  return 0;
}
