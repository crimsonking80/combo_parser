#include "color.hpp"

#include <cctype>

struct data_t
{
  char value;

  bool (*parse)(data_t *data, char ch);
};

bool parse(data_t *data, char ch)
{
  bool parse_color(data_t *, char);
  bool parse_open_braces(data_t *, char);

  switch(ch)
  {
  case '{':
    data->parse = parse_open_braces;
    return true;

  case ',':
    return true;

  default:
    return parse_color(data, ch);
  }
}

bool parse_color(data_t *data, char ch)
{
  switch(ch)
  {
  case 'W':
  case 'w':
    data->value |= 0x01;
    return true;

  case 'U':
  case 'u':
    data->value |= 0x02;
    return true;

  case 'B':
  case 'b':
    data->value |= 0x04;
    return true;

  case 'R':
  case 'r':
    data->value |= 0x08;
    return true;

  case 'G':
  case 'g':
    data->value |= 0x10;
    return true;

  case 'C':
  case 'c':
    return true;

  default:
    return std::isspace(ch) != 0;
  }
}

bool parse_open_braces(data_t *data, char ch)
{
  bool parse_close_braces(data_t *, char);

  if(std::isspace(ch != 0))
    return true;

  if(parse_color(data, ch))
  {
    data->parse = parse_close_braces;
    return true;
  }

  return false;
}

bool parse_close_braces(data_t *data, char ch)
{
  switch(ch)
  {
  case '}':
    data->parse = parse;
    return true;

  default:
    return std::isspace(ch) != 0;
  }
}

Color::Color(const std::string &desc) : value_(0)
{
  bool result = true;

  data_t data;

  data.value = 0;
  data.parse = parse;

  for(std::string::const_iterator it = desc.begin(); result && it != desc.end(); ++it)
    result = data.parse(&data, *it);

  if(result)
    value_ = data.value;
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
