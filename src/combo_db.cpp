#include "combo_db.hpp"

#include <fstream>

#include "data_provider.hpp"

combo_db::combo_db(const std::string &url) : url_(url.empty()? "https://sheets.googleapis.com/v4/spreadsheets/1JJo8MzkpuhfvsaKVFVlOoNymscCt-Aw-1sob2IhpwXY/values:batchGet?ranges=combos!A2:R&key=AIzaSyDzQ0jCf3teHnUK17ubaLaV6rcWf9ZjG5E" : url)
{
}

combo &combo_db::operator [](const std::string &name)
{
  map_t::iterator it = map_.lower_bound(name);
  if(it == map_.end() || it->first != name)
  {
    std::fstream stream("combos.json");

    data_provider provider;

    provider.get(url_, stream);

    //it = map_.insert(it, std::make_pair(name, json_parser().parse(stream)));
  }

  return it->second;
}

bool combo_db::fetch()
{
  std::fstream stream("combos.json");

  data_provider provider;

  if(!provider.get(url_, stream))
    return false;

  // TODO

  return true;
}
