#include "deck.h"

Deck::Deck()
{
    for (int i = 1; i <= 11; i++) // start i from one to initialize card number with it.
    {
        card = new Card(Cards::PirateFlag, i); // 0_10
        deck.push_back(*card);
    }
    for (int i = 1; i <= 11; i++)
    {
        card = new Card(Cards::Parrot, i); // 11_21
        deck.push_back(*card);
    }
    for (int i = 1; i <= 11; i++)
    {
        card = new Card(Cards::Map, i); // 22_32
        deck.push_back(*card);
    }
    for (int i = 1; i <= 11; i++)
    {
        card = new Card(Cards::Treasure, i); // 33_43
        deck.push_back(*card);
    }
    // unique card wile initialize with zero.
    for (int i = 0; i < 4; i++)
    {
        card = new Card(Cards::Pirate, 0); // 44_47
        deck.push_back(*card);
    }
    for (int i = 0; i < 4; i++)
    {
        card = new Card(Cards::SkullKing, 0); // 48_51
        deck.push_back(*card);
    }
    for (int i = 0; i < 4; i++)
    {
        card = new Card(Cards::Queen, 0); // 52_55
        deck.push_back(*card);
    }
}

Card &Deck::random()
{
    int int_random = rand() % 56;
    if (deck.at(int_random).is_deleted())
    {
        Deck::random();
    }
    else
    {
        deck.at(int_random).delete_it();
        return deck.at(int_random);
    }
}

void Deck::reset()
{
    for (auto &&i : deck)
    {
        i.undelete_it();
    }
}

Card &Deck::set_starter()
{
    int int_random = (rand() % 11) + 11;
    if (deck.at(int_random).is_deleted())
    {
        Deck::set_starter();
    }
    else
    {
        deck.at(int_random).delete_it();
        return deck.at(int_random);
    }
}