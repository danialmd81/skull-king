#include "king.h"

King::King()
{
    load_pixmap();
}

King::King(string n, string u, string pa, string ph, string a)
{
    k_name = n;
    k_username = u;
    k_password = pa;
    k_phone = ph;
    k_address = a;
    k_coin = 1000;
    k_turn = 0;
    k_score = 0;
    k_victory = 0;
    k_failure = 0;
    load_pixmap();
}

King::King(ifstream &in)
{
    in >> *this;
    load_pixmap();
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

bool &King::turn()
{
    return k_turn;
}

vector<Card> &King::hand()
{
    return k_hand;
}

QGraphicsPixmapItem *King::pixmap_item()
{
    return pix_item;
}

QSize &King::pix_size()
{
    return pixmap_size;
}

// string &King::operator()(string output)
// {
//     if (output == "name" || output == "1")
//         return k_name;
//     else if (output == "username" || output == "2")
//         return k_username;
//     else if (output == "password" || output == "3")
//         return k_password;
//     else if (output == "phone" || output == "4")
//         return k_phone;
//     else if (output == "address" || output == "5")
//         return k_address;
//     else
//     {
//         // throw my_exception(my_exception_enum::king_string_error);
//     }
// }

// int &King::operator()(char output)
// {
//     if (output == '6' || output == 'c')
//         return k_coin;
//     else if (output == '7' || output == 's')
//         return k_score;
//     else if (output == '8' || output == 'v')
//         return k_victory;
//     else if (output == '9' || output == 'f')
//         return k_failure;
//     else
//     {
//         // throw my_exception(my_exception_enum::king_int_error);
//     }
// }

ostream &operator<<(ostream &out, King &king)
{
    out << "King: " << king.k_name << ' ' << king.k_username << ' ' << king.k_password << ' ' << king.k_phone << ' '
        << king.k_address << ' ' << king.k_coin << ' ' << king.k_turn << ' ' << king.k_score << ' ' << king.k_victory
        << ' ' << king.k_failure << ' ' << king.k_hand.size() << ' ';
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
            in >> king.k_name >> king.k_username >> king.k_password >> king.k_phone >> king.k_address >> king.k_coin >>
                king.k_turn >> king.k_score >> king.k_victory >> king.k_failure >> i_reader;
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

bool King::all_cards_is_deleted()
{
    bool flag = true;
    for (auto &&i : k_hand)
    {
        if (!i.is_deleted())
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
            file.close();
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
            file.close();
            __throw_ios_failure("there is no file with this path");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void King::load_pixmap()
{
    QPixmap pix_map;
    pix_map.load(":/Pictures/Game/SkullMark.png");
    pixmap_size = pix_map.size();
    pix_item = new QGraphicsPixmapItem(pix_map);
}
