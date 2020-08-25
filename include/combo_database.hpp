#pragma once

#include <istream>
#include <map>

#include "combo.hpp"

class CardDatabase;

class ComboDatabase
{
public:
  explicit ComboDatabase(CardDatabase &database) : database_(database) {}
  ComboDatabase(CardDatabase &database, std::istream &stream) : database_(database) { fetch(stream); }

  bool fetch(std::istream &stream);

protected:
  typedef std::map<std::string, Combo> map_t;

private:
  CardDatabase &database_;

  map_t map_;
};
