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
    oracle_text_ = properties.get<std::string>("oracle_text", "");

    if(properties.count("card_faces"))
    {
      for(const ptree::value_type &face : properties.get_child("card_faces"))
      {
        if(!oracle_text_.empty())
          oracle_text_ += "\n";

        oracle_text_ += face.second.get<std::string>("oracle_text", "");
      }
    }

    std::string colors;
    for(const ptree::value_type &color : properties.get_child("colors"))
      colors += color.second.data();
    colors_ = colors;

    std::string color_identity;
    for(const ptree::value_type &color : properties.get_child("color_identity"))
      color_identity += color.second.data();
    color_identity_ = color_identity;

    return true;
  }
  catch(const ptree_error &ex)
  {
    std::cerr << "error while parsing card: " << ex.what() << "." << std::endl;

    return false;
  }
}
