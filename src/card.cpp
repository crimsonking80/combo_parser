#include "card.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;

bool Card::parse(std::istream &stream)
{
  try
  {
    ptree properties;

    json_parser::read_json(stream, properties);

    name_ = properties.get<std::string>("name");
    mana_cost_ = properties.get<std::string>("mana_cost");
    type_line_ = properties.get<std::string>("type_line");
    oracle_text_ = properties.get<std::string>("oracle_text");

    colors_.clear();
    for(const ptree::value_type &color : properties.get_child("colors"))
      colors_ += "{" + color.second.data() + "}";

    color_identity_.clear();
    for(const ptree::value_type &color : properties.get_child("color_identity"))
      color_identity_ += "{" + color.second.data() + "}";

    return true;
  }
  catch(const ptree_error &ex)
  {
    std::cerr << "error while parsing card: " << ex.what() << "." << std::endl;

    return false;
  }
}
