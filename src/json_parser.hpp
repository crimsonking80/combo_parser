#pragma once

#include <istream>

class card;
class combo;

class json_parser
{
public:
  card parse_card(std::istream &stream);
  combo parse_combo(std::istream &stream);
};
