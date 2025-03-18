#pragma once
#include <string>

class Table
{
private:
    template <typename... Args>
    std::string make_table(Args... args);

    template <typename... Args>
    std::string make_table_lines(Args... args);

    template <typename... Args>
    std::string make_feedback_or_questions(Args... args);

public:
    std::string make_everything();
};