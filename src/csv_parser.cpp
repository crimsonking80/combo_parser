#include "csv_parser.hpp"

static void parse_unquoted(csv_parser &parser, char ch)
{
  switch(ch)
  {
  case ',':
  case ';':
    parser.fields.push_back(std::string());
    break;

  case '\"':
    parser.parse = parse_quoted;
    break;

  default:
    parser.fields.back().push_back(ch);
    break;
  }
}

static void parse_quoted(csv_parser &parser, char ch)
{
  switch(ch) 
  {
  case '\"':
    parser.parse = parse_quoted_quote;
    break;

  default:
    parser.fields.back().push_back(ch);
    break;
  }
}

static void parse_quoted_quote(csv_parser &parser, char ch)
{
  switch(ch)
  {
  case ',':
  case ';':
    parser.fields.push_back(std::string());
    parser.parse = parse_unquoted;
    break;

  case '\"':
    parser.fields.back().push_back('\"');
    parser.parse = parse_quoted;
    break;

  default:
    parser.fields.back().push_back(ch);
    parser.parse = parse_unquoted;
    break;
  }
}

std::vector<std::string> csv_parser::parse_line(const std::string &line)
{
  fields.clear();
  fields.push_back(std::string());

  parse = parse_unquoted;

  for(std::string::const_iterator it = line.begin(); it != line.end(); ++it)
    parse(*this, *it);

  return fields;
}
