#pragma once

#include <istream>
#include <ostream>
#include <vector>

class CardDatabase;
class Combo;

class ComboSerializer
{
public:
  explicit ComboSerializer(CardDatabase &database) : database_(database) {}

  bool serialize(std::ostream &stream, const std::vector<Combo> &combos);
  bool deserialize(std::istream &stream, std::vector<Combo> &combos);

private:
  CardDatabase &database_;
};
