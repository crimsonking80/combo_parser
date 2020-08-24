#pragma once

#include <string>

class Combo
{
public:
  explicit Combo(const std::string &cards = "",
                 const std::string &results = "",
                 const std::string &prerequisites = "",
                 const std::string &steps = "") :
    cards_(cards),
    results_(results),
    prerequisites_(prerequisites),
    steps_(steps)
  {}

  std::string cards() const { return cards_; }
  std::string results() const { return results_; }
  std::string prerequisites() const { return prerequisites_; }
  std::string steps() const { return steps_; }

  std::string color_identity() const;

private:
  std::string cards_, results_, prerequisites_, steps_;
};
