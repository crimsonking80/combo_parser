#pragma once

#include <istream>

class Card;

class CardParser
{
public:
  Card parse(std::istream &stream);
};
