#include "json_parser.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "card.hpp"
#include "combo.hpp"

card json_parser::parse_card(std::istream &stream)
{
  try
  {
    boost::property_tree::ptree properties;

    boost::property_tree::json_parser::read_json(stream, properties);

    std::string colors, color_identity;

    for(const boost::property_tree::ptree::value_type &color : properties.get_child("colors"))
      colors += "{" + color.second.data() + "}";

    for(const boost::property_tree::ptree::value_type &color : properties.get_child("color_identity"))
      color_identity += "{" + color.second.data() + "}";

    return card(properties.get<std::string>("name"),
                properties.get<std::string>("mana_cost"),
                properties.get<std::string>("type_line"),
                properties.get<std::string>("oracle_text"),
                colors,
                color_identity);
  }
  catch(const boost::property_tree::json_parser_error &ex)
  {
    std::cerr << "boost::property_tree::json_parser::read_json() failed: " << ex.what() << std::endl;
    return card();
  }
  catch(const boost::property_tree::ptree_error &ex)
  {
    std::cerr << "boost::property_tree::ptree::get() failed: " << ex.what() << std::endl;
    return card();
  }
}

combo json_parser::parse_combo(std::istream &stream)
{
  try
  {
    boost::property_tree::ptree properties;

    boost::property_tree::json_parser::read_json(stream, properties);

    // TODO

    return combo();
  }
  catch(const boost::property_tree::json_parser_error &ex)
  {
    std::cerr << "boost::property_tree::json_parser::read_json() failed: " << ex.what() << std::endl;
    return combo();
  }
  catch(const boost::property_tree::ptree_error &ex)
  {
    std::cerr << "boost::property_tree::ptree::get() failed: " << ex.what() << std::endl;
    return combo();
  }
}
