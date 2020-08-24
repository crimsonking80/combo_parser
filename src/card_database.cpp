#include "card_database.hpp"

#include <sstream>

#include "data_provider.hpp"
#include "card_parser.hpp"

CardDatabase::CardDatabase(const std::string &url) : url_(url.empty()? "https://api.scryfall.com" : url)
{
}

Card &CardDatabase::operator [](const std::string &name)
{
  map_t::iterator it = map_.lower_bound(name);
  if(it == map_.end() || it->first != name)
  {
    std::stringstream stream;

    DataProvider provider;

    provider.get(url_ + "/cards/named?exact=" + provider.escape(name), stream);

    it = map_.insert(it, std::make_pair(name, CardParser().parse(stream)));
  }

  return it->second;
}
