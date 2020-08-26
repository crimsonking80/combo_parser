#include <fstream>

#include <boost/program_options.hpp>

#include "card_database.hpp"
#include "combo_database.hpp"
#include "data_provider.hpp"

int main(int argc, char **argv)
{
  std::string url = "https://sheets.googleapis.com/v4/spreadsheets/1JJo8MzkpuhfvsaKVFVlOoNymscCt-Aw-1sob2IhpwXY/values:batchGet?ranges=combos!A2:R&key=AIzaSyDzQ0jCf3teHnUK17ubaLaV6rcWf9ZjG5E";

  std::string file, card_file;

  bool download, parse;

  boost::program_options::options_description desc("options:");

  desc.add_options()
    ("help", "display help")
    ("url", boost::program_options::value<std::string>(), "combo spreadsheets url")
    ("file", boost::program_options::value<std::string>(&file)->default_value("combos.json"), "downloaded combos filename")
    ("card_file", boost::program_options::value<std::string>(&card_file)->default_value("cards.json"), "card database filename")
    ("download", boost::program_options::value<bool>(&download)->default_value(true), "perform download")
    ("parse", boost::program_options::value<bool>(&parse)->default_value(true), "perform parse");

  boost::program_options::variables_map args;

  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), args);
  boost::program_options::notify(args);

  if(args.count("help"))
  {
    std::cout << desc << std::endl;
    return 0;
  }

  if(args.count("url"))
    url = args["url"].as<std::string>();

  CardDatabase card_db;

  card_db.read(card_file);

  if(download)
  {
    std::fstream stream(file, std::fstream::out);

    DataProvider provider;

    if(!provider.get(url, stream))
      return -1;
  }

  if(parse)
  {
    std::fstream stream(file, std::fstream::in);

    ComboDatabase combo_db(card_db, stream);
  }

  card_db.write(card_file);

  return 0;
}
