#pragma once

#include <map>

#include "card.hpp"

class CardDatabase
{
public:
  explicit CardDatabase(const std::string &url = "");

  Card &operator [](const std::string &name);

  std::string url() const { return url_; }

protected:
  typedef std::map<std::string, Card> map_t;

private:
  std::string url_;

  map_t map_;
};