#include "card_db.hpp"

#include <sstream>

#include "data_provider.hpp"
#include "json_parser.hpp"

card_db::card_db(const std::string &url) : url_(url.empty()? "https://api.scryfall.com" : url)
{
}

card &card_db::operator [](const std::string &name)
{
  map_t::iterator it = map_.lower_bound(name);
  if(it == map_.end() || it->first != name)
  {
    std::stringstream stream;

    data_provider provider;

    provider.get(url_ + "/cards/named?exact=" + provider.escape(name), stream);

    it = map_.insert(it, std::make_pair(name, json_parser().parse_card(stream)));
  }

  return it->second;
}
