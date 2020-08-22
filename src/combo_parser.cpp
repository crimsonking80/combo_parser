#include "combo_parser.hpp"

#include <algorithm>
#include <unordered_map>

#include "csv_parser.hpp"

void parse(std::istream &in, std::ostream &out)
{
  std::string line;

  csv_parser parser;

  if(std::getline(in, line))
  {
    const std::vector<std::string> fields = parser.parse_line(line);

    while(std::getline(in, line))
    {
      const std::vector<std::string> values = parser.parse_line(line);

      std::unordered_map<std::string, std::string> combo;

      const size_t n = std::min(fields.size(), values.size());

      for(size_t i = 0; i < n; ++i)
        combo[fields[i]] = values[i];
    }
  }
}
