#include "color.hpp"

#include <cctype>

class ColorParser
{
public:
	ColorParser() :
		parse_(&ColorParser::parse_init),
		value_(0)
	{}

	bool parse(char ch) { return (this->*parse_)(ch); }

	char value() const { return value_; }

protected:
	typedef bool (ColorParser::*parse_f)(char);

	bool parse_init(char ch)
	{
		switch(ch)
		{
		case '{':
			parse_ = &ColorParser::parse_open_braces;
			return true;

		case ',':
			return true;

		default:
			return parse_color(ch);
		}
	}

	bool parse_color(char ch)
	{
		switch(ch)
		{
		case 'W':
		case 'w':
			value_ |= 0x01;
			return true;

		case 'U':
		case 'u':
			value_ |= 0x02;
			return true;

		case 'B':
		case 'b':
			value_ |= 0x04;
			return true;

		case 'R':
		case 'r':
			value_ |= 0x08;
			return true;

		case 'G':
		case 'g':
			value_ |= 0x10;
			return true;

		case 'C':
		case 'c':
			return true;

		default:
			return std::isspace(ch) != 0;
		}
	}

	bool parse_open_braces(char ch)
	{
		if(std::isspace(ch != 0))
			return true;

		if(parse_color(ch))
		{
			parse_ = &ColorParser::parse_close_braces;
			return true;
		}

		return false;
	}

	bool parse_close_braces(char ch)
	{
		switch(ch)
		{
		case '}':
			parse_ = &ColorParser::parse_init;
			return true;

		default:
			return std::isspace(ch) != 0;
		}
	}

private:
	parse_f parse_;

	char value_;
};

Color::Color(const std::string &text) : value_(0)
{
  bool result = true;

  ColorParser parser;

  for(std::string::const_iterator it = text.begin(); result && it != text.end(); ++it)
    result = parser.parse(*it);

  if(result)
    value_ = parser.value();
}

Color::operator std::string() const
{
  if(desc_.empty())
  {
    if(value_ == 0)
      desc_ = "{C}";
    else
    {
      if(value_ & 1)
        desc_ += "{W}";

      if(value_ & 2)
        desc_ += "{U}";

      if(value_ & 4)
        desc_ += "{B}";

      if(value_ & 8)
        desc_ += "{R}";

      if(value_ & 16)
        desc_ += "{G}";
    }
  }

  return desc_;
}

Color operator +(const Color &a, const Color &b)
{
  Color c = a;
  c += a;
  return c;
}

Color operator -(const Color &a, const Color &b)
{
  Color c = a;
  c -= a;
  return c;
}
