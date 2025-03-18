#include "Table.hh"
#include <string>

template <typename... Args>
std::string Table::make_table(Args... args)
{
    return std::string();
}

template <typename... Args>
std::string Table::make_onderbouwing(Args... args)
{
    return std::string();
}

template <typename... Args>
std::string Table::make_feedback_or_questions(Args... args)
{
    return std::string();
}

std::string Table::make_everything()
{
    return std::string();
}
