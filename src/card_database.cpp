#include "card_database.hpp"

#include <fstream>
#include <sstream>

#include <boost/property_tree/json_parser.hpp>

#include "card.hpp"
#include "data_provider.hpp"

using namespace boost::property_tree;

CardDatabase::CardDatabase(const std::string &url) : url_(url.empty()? "https://api.scryfall.com" : url)
{
}

std::shared_ptr<Card> CardDatabase::operator [](const std::string &name)
{
	const map_t::iterator it = map_.lower_bound(name);
	if(it != map_.end() && it->first == name)
		return it->second;

	std::cout << "downloading card \"" << name << "\" from " << url_ << "..." << std::endl;

	DataProvider provider;
	std::stringstream stream;

	if(!provider.get(url_ + "/cards/named?fuzzy=" + provider.escape(name), stream))
	{
		std::cerr << "download of card \"" << name << "\" failed." << std::endl;
	}

	std::shared_ptr<Card> card(new Card());

	if(!card->parse(stream))
	{
		std::cerr << "parsing of card \"" << name << "\" failed." << std::endl;
		return std::shared_ptr<Card>();
	}

	map_.insert(it, std::make_pair(name, card));
	map_.insert(it, std::make_pair(card->name(), card));

	std::cout << "card \"" << name << "\" added to database." << std::endl;

	return card;
}

bool CardDatabase::write(const std::string &filename)
{
	std::fstream stream(filename, std::fstream::out);
	if(!stream.is_open())
		return false;

	return write(stream);
}

bool CardDatabase::write(std::ostream &stream)
{
	try
	{
		std::cout << "saving card database..." << std::endl;

		ptree properties;

		for(map_t::iterator it = map_.begin(); it != map_.end(); ++it)
		{
			ptree card;

			card.put("name", it->second->name());
			card.put("mana_cost", it->second->mana_cost());
			card.put("type_line", it->second->type_line());
			card.put("oracle_text", it->second->oracle_text());
			card.put<std::string>("colors", it->second->colors());
			card.put<std::string>("color_identity", it->second->color_identity());

			properties.push_back(std::make_pair("", card));
		}

		json_parser::write_json(stream, properties);

		std::cout << "card database successfully saved." << std::endl;

		return true;
	}
	catch(const ptree_error &ex)
	{
		std::cerr << "error while writing cards: " << ex.what() << "." << std::endl;

		return false;
	}
}

bool CardDatabase::read(const std::string &filename)
{
	std::fstream stream(filename, std::fstream::in);
	if(!stream.is_open())
		return false;

	return read(stream);
}

bool CardDatabase::read(std::istream &stream)
{
	try
	{
		std::cout << "loading card database..." << std::endl;

		ptree properties;

		json_parser::read_json(stream, properties);

		for(ptree::const_iterator it = properties.begin(); it != properties.end(); ++it)
		{
			try
			{
				const std::shared_ptr<Card> card(new Card(it->second.get<std::string>("name"),
																									it->second.get<std::string>("mana_cost"),
																									it->second.get<std::string>("type_line"),
																									it->second.get<std::string>("oracle_text"),
																									it->second.get<std::string>("colors"),
																									it->second.get<std::string>("color_identity")));

				map_.insert(std::make_pair(card->name(), card));

				std::cout << "card \"" << card->name() << "\" added to database." << std::endl;
			}
			catch(const std::exception &ex)
			{
				std::cerr << "error while reading a card: " << ex.what() << "." << std::endl;
			}
		}

		std::cout << "card database successfully loaded." << std::endl;

		return true;
	}
	catch(const ptree_error &ex)
	{
		std::cerr << "error while reading cards: " << ex.what() << "." << std::endl;

		return false;
	}
}
