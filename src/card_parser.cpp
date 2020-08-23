#include "card_parser.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "card.hpp"

using namespace boost::property_tree;

card card_parser::parse(std::istream &stream)
{
  try
  {
    ptree properties;

    json_parser::read_json(stream, properties);

    return card(properties.get<std::string>("name"),
                properties.get<std::string>("mana_cost"),
                properties.get<std::string>("type_line"),
                properties.get<std::string>("oracle_text"),
                properties.get<std::string>("colors"),
                properties.get<std::string>("color_identity"));
  }
  catch(const json_parser_error &ex)
  {
    std::cerr << "boost::property_tree::json_parser::read_json() failed: " << ex.what() << std::endl;
    return card();
  }
  catch(const ptree_error &ex)
  {
    std::cerr << "boost::property_tree::ptree::get() failed: " << ex.what() << std::endl;
    return card();
  }
}
