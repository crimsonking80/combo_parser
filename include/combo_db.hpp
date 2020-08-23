#pragma once

#include <map>

#include "combo.hpp"

class combo_db
{
public:
  explicit combo_db(const std::string &url = "");

  combo &operator [](const std::string &name);

  std::string url() const { return url_; }

  bool fetch();

protected:
  typedef std::map<std::string, combo> map_t;

private:
  std::string url_;

  map_t map_;
};
