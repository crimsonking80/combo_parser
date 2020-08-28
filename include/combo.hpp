#pragma once

#include <memory>
#include <string>
#include <vector>

class Card;
class Color;

class Combo
{
protected:
	typedef std::vector< std::shared_ptr<Card> > cards_t;

public:
	explicit Combo(const cards_t &cards,
								 const std::string &results = "",
								 const std::string &prerequisites = "",
								 const std::string &steps = "") :
		cards_(cards),
		results_(results),
		prerequisites_(prerequisites),
		steps_(steps)
	{}

	cards_t cards() const { return cards_; }
	std::string results() const { return results_; }
	std::string prerequisites() const { return prerequisites_; }
	std::string steps() const { return steps_; }

	Color color_identity() const;

private:
	cards_t cards_;

	std::string results_, prerequisites_, steps_;
};
