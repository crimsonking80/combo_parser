#include "combo_serializer.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "combo.hpp"

void ComboSerializer::serialize(std::ostream &stream, const std::vector<Combo> &combos)
{
  // TODO
}

void ComboSerializer::deserialize(std::istream &stream, std::vector<Combo> &combos)
{
  try
  {
    boost::property_tree::ptree properties;

    boost::property_tree::json_parser::read_json(stream, properties);

    for(const boost::property_tree::ptree::value_type &range : properties.get_child("valueRanges"))
    {
      for(const boost::property_tree::ptree::value_type &value : properties.get_child("values"))
      {
        try
        {
          // TODO

          combos.push_back(Combo());
        }
        catch(const boost::property_tree::ptree_error &ex)
        {
          std::cerr << "boost::property_tree::ptree::get() failed: " << ex.what() << std::endl;
        }
      }
    }
  }
  catch(const boost::property_tree::json_parser_error &ex)
  {
    std::cerr << "boost::property_tree::json_parser::read_json() failed: " << ex.what() << std::endl;
  }
  catch(const boost::property_tree::ptree_error &ex)
  {
    std::cerr << "boost::property_tree::ptree::get_child() failed: " << ex.what() << std::endl;
  }
}
