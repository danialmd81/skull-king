#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <iostream>
#include <vector>

using namespace std;
class Deck
{
private:
  Card *card;
  vector<Card> deck;

public:
  Deck();
  Card &random();
  void reset();
  Card &set_starter();
};

#endif // DECK_H
