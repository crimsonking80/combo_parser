#include "combo_serializer.hpp"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>

#include "card_database.hpp"
#include "combo.hpp"

using namespace boost::property_tree;

bool ComboSerializer::serialize(std::ostream &stream, const std::vector<Combo> &combos)
{
  // TODO

  return false;
}

bool ComboSerializer::deserialize(std::istream &stream, std::vector<Combo> &combos)
{
  try
  {
    std::cout << "parsing combos..." << std::endl;

    ptree properties;

    json_parser::read_json(stream, properties);

    const ptree &ranges = properties.get_child("valueRanges");

    for(ptree::const_iterator range_it = ranges.begin(); range_it != ranges.end(); ++range_it)
    {
      const ptree &values = range_it->second.get_child("values");

      for(ptree::const_iterator value_it = values.begin(); value_it != values.end(); ++value_it)
      {
        try
        {
          ptree::const_iterator it = value_it->second.begin();

          const std::string id = (it++)->second.data();

          for(size_t i = 0; i < 10; ++i)
          {
            const std::string name = (it++)->second.data();
            if(name.empty())
              continue;

            const Card card = database_[name];
            if(card.empty())
              throw std::exception(("card " + name + " not found").c_str());

            // TODO
          }

          const std::string color_identity = (it++)->second.data();
          const std::string prerequisites = (it++)->second.data();
          const std::string steps = (it++)->second.data();
          const std::string results = (it++)->second.data();
          const std::string reserved1 = (it++)->second.data();
          const std::string reserved2 = (it++)->second.data();
          const std::string cards = (it++)->second.data();

          combos.push_back(Combo(cards, results, prerequisites, steps));
        }
        catch(const std::exception &ex)
        {
          std::cerr << "error while parsing a combo: " << ex.what() << "." << std::endl;
        }
      }
    }

    std::cout << "combos successfully parsed." << std::endl;

    return true;
  }
  catch(const ptree_error &ex)
  {
    std::cerr << "error while parsing combos: " << ex.what() << "." << std::endl;

    return false;
  }
}
