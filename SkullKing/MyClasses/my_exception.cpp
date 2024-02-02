#include "my_exception.h"

my_exception::my_exception()
{
}

my_exception::my_exception(my_exception_enum exc)
{
    if (exc == my_exception_enum::card_comparison)
    {
        message = "card comparison failed.";
    }
    else if (exc == my_exception_enum::change_name)
    {
        message = "can't change username because file is open.";
    }
    else if (exc == my_exception_enum::cards_enum_error)
    {
        message = "you choose a card that don't exist.";
    }
    else if (exc == my_exception_enum::king_string_error)
    {
        message = "king doesn't have a attribute with this name.";
    }
    else if (exc == my_exception_enum::king_int_error)
    {
        message = "king doesn't have a attribute with this int.";
    }
}
