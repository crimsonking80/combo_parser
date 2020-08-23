#include "card_db.hpp"

int main(int argc, char **argv)
{
  card_db db;

  //client.get("https://sheets.googleapis.com/v4/spreadsheets/1JJo8MzkpuhfvsaKVFVlOoNymscCt-Aw-1sob2IhpwXY/values:batchGet?ranges=combos!A2:R&key=AIzaSyDzQ0jCf3teHnUK17ubaLaV6rcWf9ZjG5E");

  const card card = db["Ad Nauseam"];

  return 0;
}
