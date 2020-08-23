#pragma once

#include <map>

#include "card.hpp"

class card_db
{
public:
  explicit card_db(const std::string &url = "https://api.scryfall.com");

  card &operator [](const std::string &name);

  std::string url() const { return url_; }

protected:
  typedef std::map<std::string, card> map_t;

private:
  std::string url_;

  map_t map_;
};
