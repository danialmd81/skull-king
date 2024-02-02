#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <string>

using namespace std;

enum my_exception_enum
{
    cards_enum_error,
    card_comparison,
    change_name,
    king_string_error,
    king_int_error
};

class my_exception : public exception
{
  private:
    string message;

  public:
    my_exception();
    my_exception(my_exception_enum exc);
    const char *what() const throw()
    {
        return message.c_str();
    }
};

#endif // MY_EXCEPTION_H
