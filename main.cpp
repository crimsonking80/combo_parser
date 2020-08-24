//#include <iostream>
#include <fstream>

#include "data_provider.hpp"

#include <boost/program_options.hpp>

#include "card_database.hpp"

int main(int argc, char **argv)
{
  boost::program_options::options_description desc("options:");

  desc.add_options()
    ("help", "display help")
    ("url", boost::program_options::value<std::string>(), "combo spreadsheets url");

  boost::program_options::variables_map args;

  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), args);
  boost::program_options::notify(args);    

  if(args.count("help"))
  {
    std::cout << desc << std::endl;
    return 0;
  }

  std::string url = "https://sheets.googleapis.com/v4/spreadsheets/1JJo8MzkpuhfvsaKVFVlOoNymscCt-Aw-1sob2IhpwXY/values:batchGet?ranges=combos!A2:R&key=AIzaSyDzQ0jCf3teHnUK17ubaLaV6rcWf9ZjG5E";

  if(args.count("url"))
    url = args["url"].as<std::string>();
    std::fstream stream("combos.json");

  DataProvider provider;

  if(!provider.get(url_, stream))
    return false;

  return 0;
}
