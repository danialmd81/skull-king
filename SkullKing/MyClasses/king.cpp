#include "king.h"

King::King()
{
}

King::King(string n, string u, string pa, string ph, string a)
{
    k_name = n;
    k_username = u;
    k_password = pa;
    k_phone = ph;
    k_address = a;
    k_coin = 1000;
    k_score = 0;
    k_victory = 0;
    k_failure = 0;
}

King::King(ifstream &in)
{
    in >> *this;
}

string &King::name()
{
    return k_name;
}

string &King::username()
{
    return k_username;
}

string &King::password()
{
    return k_password;
}

string &King::phone()
{
    return k_phone;
}

string &King::address()
{
    return k_address;
}

string King::filePath()
{
    return (k_username + ".txt");
}

int &King::coin()
{
    return k_coin;
}

int &King::score()
{
    return k_score;
}

int &King::victory()
{
    return k_victory;
}

int &King::failure()
{
    return k_failure;
}

Card &King::starter_card()
{
    return k_starter_card;
}

vector<Card> &King::hand()
{
    return k_hand;
}

ostream &operator<<(ostream &out, King &king)
{
    out << "King: " << king.k_name << ' ' << king.k_username << ' ' << king.k_password << ' '
        << king.k_phone << ' ' << king.k_address << ' ' << king.k_coin << ' ' << king.k_score << ' '
        << king.k_victory << ' ' << king.k_failure << ' ' << king.k_hand.size() << ' ';
    for (auto &&i : king.k_hand)
    {
        out << i;
    }
    // if you want to add something to write in the file add here.
    out << "end";
    return out;
}

istream &operator>>(istream &in, King &king)
{
    string s_reader;
    int i_reader;
    in >> s_reader;
    while (s_reader != "end")
    {
        if (s_reader == "King:")
        {
            in >> king.k_name >> king.k_username >> king.k_password >> king.k_phone >> king.k_address >>
                king.k_coin >> king.k_score >> king.k_victory >> king.k_failure >> i_reader;
            for (int i = 0; i < i_reader; i++)
            {
                Card card;
                in >> card;
                king.k_hand.push_back(card);
            }
        }
        // if you want to add something to read file add here.
        in >> s_reader;
    }
    return in;
}

bool King::operator==(King &king)
{
    return k_username == king.k_username && k_password == king.k_password;
}

void King::reset_hand()
{
    k_hand.clear();
}

bool King::all_cards_is_played()
{
    bool flag = true;
    for (auto &&i : k_hand)
    {
        if (!i.played_re())
            flag = false;
    }
    return flag;
}

void King::save()
{
    ofstream file;
    file.open(k_username + ".txt", ios::out | ios::trunc);
    file << *this;
    file.close();
}

void King::load(string path)
{
    try
    {
        ifstream file;
        file.open(path, ios::in);
        if (file.is_open())
        {
            file >> (*this);
            file.close();
        }
        else
        {
            __throw_ios_failure("there is no file with this path");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void King::load()
{
    try
    {
        ifstream file;
        file.open(k_username + ".txt", ios::in);
        if (file.is_open())
        {
            file >> (*this);
            file.close();
        }
        else
        {
            __throw_ios_failure("there is no file with this path");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}
