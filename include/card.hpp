#pragma once

#include <string>

class Card
{
public:
  explicit Card(const std::string &name = "",
                const std::string &mana_cost = "",
                const std::string &type_line = "",
                const std::string &oracle_text = "",
                const std::string &colors = "",
                const std::string &color_identity = "") :
    name_(name),
    mana_cost_(mana_cost),
    type_line_(type_line),
    oracle_text_(oracle_text),
    colors_(colors),
    color_identity_(color_identity)
  {}

  std::string name() const { return name_; }
  std::string mana_cost() const { return mana_cost_; }
  std::string type_line() const { return type_line_; }
  std::string oracle_text() const { return oracle_text_; }
  std::string colors() const { return colors_; }
  std::string color_identity() const { return color_identity_; }

  bool empty() const { return name_.empty(); }

  bool parse(std::istream &stream);

private:
  std::string name_, mana_cost_, type_line_, oracle_text_, colors_, color_identity_;
};
