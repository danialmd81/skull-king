#ifndef CARD_H
#define CARD_H

#include "my_exception.h"
#include <fstream>
#include <iostream>
#include <vector>

enum Cards
{
  PirateFlag,
  Parrot,
  Map,
  Treasure,
  SkullKing,
  Queen,
  Pirate
};

Cards from_int_to_Cards(int n);
std::string from_Cards_to_string(Cards cards);
class Card
{
private:
  Cards Name;
  int Number;
  bool deleted, played;

public:
  Card();
  Card(Cards name, int number);
  std::string filepath();
  bool &played_re();
  bool operator<(const Card card) const;
  bool operator==(const Card &card);
  friend ostream &operator<<(ostream &out, Card &card);
  friend istream &operator>>(istream &in, Card &card);
  
  void delete_it();
  void undelete_it();
  bool is_deleted();
  void save();
  void load();
  int compare(Card &card);
};

#endif // CARD_H
