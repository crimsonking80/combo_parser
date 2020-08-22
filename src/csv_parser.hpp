#pragma once

#include <string>
#include <vector>

class csv_parser
{
public:
  std::vector<std::string> parse_line(const std::string &line);

private:
  friend void parse_unquoted(csv_parser &parser, char ch);
  friend void parse_quoted(csv_parser &parser, char ch);
  friend void parse_quoted_quote(csv_parser &parser, char ch);

  void (*parse)(csv_parser &parser, char ch);

  std::vector<std::string> fields;
};
