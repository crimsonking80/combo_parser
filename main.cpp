#include "card_db.hpp"

int main(int argc, char **argv)
{
  card_db db;

  const card card = db["Ad Nauseam"];

  return 0;
}
