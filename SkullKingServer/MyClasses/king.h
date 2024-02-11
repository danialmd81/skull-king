#ifndef KING_H
#define KING_H

#include "card.h"
#include <fstream>
#include <vector>

using namespace std;

class King
{
private:
  string k_name, k_username, k_password, k_phone, k_address, error = "error";
  int k_coin, k_score, k_victory, k_failure, int_error = -1;
  vector<Card> k_hand;
  Card k_starter_card;

public:
  King();
  King(ifstream &in);
  King(string n, string u, string pa, string ph, string a);
  string &name();
  string &username();
  string &password();
  string &phone();
  string &address();
  string filePath();
  int &coin();
  int &score();
  int &victory();
  int &failure();
  Card &starter_card();
  vector<Card> &
  hand();
  bool all_cards_is_played();
  friend ostream &operator<<(ostream &out, King &king);
  friend istream &operator>>(istream &in, King &king);

  bool operator==(King &king);
  void reset_hand();

  void save();
  void load(string path);
  void load();
};

#endif // KING_H
