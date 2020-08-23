#pragma once

#include <iostream>
#include <string>

class data_provider
{
public:
  data_provider();
  ~data_provider();

  std::string escape(const std::string &url) const;

  bool get(const std::string &url, std::ostream &out = std::cout);

protected:
  void *handle;
};
