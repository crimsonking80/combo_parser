#pragma once

#include <map>
#include <ostream>

#include "combo.hpp"

class ComboDatabase
{
public:
  ComboDatabase() {}
  explicit ComboDatabase(std::ostream &stream) { fetch(stream); }

  bool fetch(std::ostream &stream);

protected:
  typedef std::map<std::string, Combo> map_t;

private:
  map_t map_;
};
