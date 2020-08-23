#pragma once

#include <istream>

class card;

class card_parser
{
public:
  card parse(std::istream &stream);
};
