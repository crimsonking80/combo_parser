#pragma once

#include <map>
#include <memory>

class Card;

class CardDatabase
{
public:
  explicit CardDatabase(const std::string &url = "");

  std::string url() const { return url_; }

  std::shared_ptr<Card> operator [](const std::string &name);

  bool write(const std::string &filename);
  bool write(std::ostream &stream);

  bool read(const std::string &filename);
  bool read(std::istream &stream);

protected:
  typedef std::map< std::string, std::shared_ptr<Card> > map_t;

private:
  std::string url_;

  map_t map_;
};
