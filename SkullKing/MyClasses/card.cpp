#include "card.h"

using namespace std;

Card::Card()
{
    played = false;
    deleted = false;
}

Card::Card(Cards name, int number)
{
    played = false;
    deleted = false;
    Name = name;
    if (Name != Cards::Queen && Name != Cards::SkullKing && Name != Cards::Pirate)
    {
        Number = number;
    }
    else
    {
        Number = 0;
    }
}

string Card::filepath()
{
    if (Number != 0)
        return from_Cards_to_string(this->Name) + to_string(Number) + ".png";
    else
        return from_Cards_to_string(this->Name) + ".png";
}

void Card::save()
{
    ofstream file;
    file.open("card.txt", ios::out | ios::trunc);
    file << *this;
    file.close();
}

void Card::load()
{
    ifstream file;
    file.open("card.txt", ios::in);
    file >> *this;
    file.close();
}

void Card::delete_it()
{
    deleted = true;
}

void Card::undelete_it()
{
    deleted = false;
}

bool Card::is_deleted()
{
    return deleted;
}

bool &Card::played_re()
{
    return played;
}

int Card::compare(Card &card) // -1 ->first loose  | 0 -> check  | 1 -> first win  |  2 -> early is winner
{
    if (Name == card.Name)
    {
        if (Name == Cards::SkullKing || Name == Cards::Queen || Name == Cards::Pirate)
        {
            return 2; // erly
        }
        else
        {
            if (Number > card.Number)
                return 1; // compare number
            else
                return -1;
        }
    }
    else
    {
        if (Name == Cards::PirateFlag)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate)
            {
                return -1; // first loos
            }
            else
            {
                return 1; // firsr win
            }
        }
        else if (Name == Cards::Parrot)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return -1; // first loose
            }
            else
            {
                return 0; // check
            }
        }
        else if (Name == Cards::Map)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return -1; // first loose
            }
            else
            {
                return 0; // check
            }
        }
        else if (Name == Cards::Treasure)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return -1; // first loose
            }
            else
            {
                return 0; // check
            }
        }
        else if (Name == Cards::SkullKing)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return 1; // skull king is bigger than them.  ///first win
            }
            else if (card.Name == Cards::Queen)
            {
                return -1; // skull king is smaller than queen.///first loos
            }
            else
            {
                return 1; // skull king is bigger than pirate.///first win
            }
        }
        else if (Name == Cards::Queen)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return 1; // queen is bigger than them.//first win
            }
            else if (card.Name == Cards::Pirate)
            {
                return -1; // queen is smaller than pirate.//first loos
            }
            else
            {
                return 1; // queen is bigger than king skull.//first win
            }
        }
        else if (Name == Cards::Pirate)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return 1; // pirate is bigger than them.//first win
            }
            else if (card.Name == Cards::SkullKing)
            {
                return -1; // pirate is smaller than skull king. first loose
            }
            else
            {
                return 1; // pirate is bigger than queen.//first win
            }
        }
    }
}

bool Card::operator<(const Card card) const
{
    if (Name == card.Name)
    {
        if (Name == Cards::SkullKing || Name == Cards::Queen || Name == Cards::Pirate)
        {
            return false; // this and that are equal.
        }
        else
        {
            return Number < card.Number;
        }
    }
    else
    {
        if (Name == Cards::PirateFlag)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (Name == Cards::Parrot)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (Name == Cards::Map)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (Name == Cards::Treasure)
        {
            if (card.Name == Cards::SkullKing || card.Name == Cards::Queen || card.Name == Cards::Pirate ||
                card.Name == Cards::PirateFlag)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (Name == Cards::SkullKing)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return false; // skull king is bigger than them.
            }
            else if (card.Name == Cards::Queen)
            {
                return true; // skull king is smaller than queen.
            }
            else
            {
                return false; // skull king is bigger than pirate.
            }
        }
        else if (Name == Cards::Queen)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return false; // queen is bigger than them.
            }
            else if (card.Name == Cards::Pirate)
            {
                return true; // queen is smaller than pirate.
            }
            else
            {
                return false; // queen is bigger than king skull.
            }
        }
        else if (Name == Cards::Pirate)
        {
            if (card.Name == Cards::PirateFlag || card.Name == Cards::Parrot || card.Name == Cards::Map ||
                card.Name == Cards::Treasure)
            {
                return false; // pirate is bigger than them.
            }
            else if (card.Name == Cards::SkullKing)
            {
                return true; // pirate is smaller than skull king.
            }
            else
            {
                return false; // pirate is bigger than queen.
            }
        }
        else
        {
            throw my_exception(my_exception_enum::card_comparison);
        }
    }
}

bool Card::operator==(const Card &card)
{
    if (Name == card.Name)
    {
        if (Name == Cards::SkullKing || Name == Cards::Queen || Name == Cards::Pirate)
        {
            return true;
        }
        else
        {
            return Number == card.Number;
        }
    }
    else
    {
        return false;
    }
}

Cards from_int_to_Cards(int cards)
{
    if (cards == 0)
    {
        return Cards::PirateFlag;
    }
    else if (cards == 1)
    {
        return Cards::Parrot;
    }
    else if (cards == 2)
    {
        return Cards::Map;
    }
    else if (cards == 3)
    {
        return Cards::Treasure;
    }
    else if (cards == 4)
    {
        return Cards::SkullKing;
    }
    else if (cards == 5)
    {
        return Cards::Queen;
    }
    else if (cards == 6)
    {
        return Cards::Pirate;
    }
    else
    {
        throw my_exception(my_exception_enum::cards_enum_error);
    }
}

string from_Cards_to_string(Cards cards)
{
    if (cards == Cards::PirateFlag)
    {
        return "PirateFlag";
    }
    else if (cards == Cards::Parrot)
    {
        return "Parrot";
    }
    else if (cards == Cards::Map)
    {
        return "Map";
    }
    else if (cards == Cards::Treasure)
    {
        return "Treasure";
    }
    else if (cards == Cards::SkullKing)
    {
        return "SkullKing";
    }
    else if (cards == Cards::Queen)
    {
        return "Queen";
    }
    else if (cards == Cards::Pirate)
    {
        return "Pirate";
    }
    else
    {
        // throw my_exception(my_exception_enum::cards_enum_error);
    }
}

ostream &operator<<(ostream &out, Card &card)
{
    out << card.Name << ' ' << card.Number << ' ';
    return out;
}

istream &operator>>(istream &in, Card &card)
{
    int cards;
    in >> cards >> card.Number;
    card.Name = from_int_to_Cards(cards);
    return in;
}
