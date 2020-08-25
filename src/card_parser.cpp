#include "card_parser.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "card.hpp"

using namespace boost::property_tree;

Card CardParser::parse(std::istream &stream)
{
  try
  {
    ptree properties;

    json_parser::read_json(stream, properties);

    std::string colors, color_identity;

    for(const ptree::value_type &color : properties.get_child("colors"))
      colors += "{" + color.second.data() + "}";

    for(const ptree::value_type &color : properties.get_child("color_identity"))
      color_identity += "{" + color.second.data() + "}";

    return Card(properties.get<std::string>("name"),
                properties.get<std::string>("mana_cost"),
                properties.get<std::string>("type_line"),
                properties.get<std::string>("oracle_text"),
                colors,
                color_identity);
  }
  catch(const ptree_error &ex)
  {
    std::cerr << "error while parsing card: " << ex.what() << "." << std::endl;
    return Card();
  }
}
