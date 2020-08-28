#pragma once

#include <iostream>
#include <string>

class DataProvider
{
public:
	DataProvider();
	~DataProvider();

	std::string escape(const std::string &url) const;

	bool get(const std::string &url, std::ostream &out = std::cout);

protected:
	void *handle;
};
