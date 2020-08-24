#pragma once

#include <istream>
#include <ostream>
#include <vector>

class Combo;

class ComboSerializer
{
public:
  void serialize(std::ostream &stream, const std::vector<Combo> &combos);
  void deserialize(std::istream &stream, std::vector<Combo> &combos);
};
