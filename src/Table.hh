#pragma once
#include <string>
#include <vector>
#include <optional>

class Table
{
private:
    template <typename... Args>
        requires(std::convertible_to<Args, std::string> && ...)
    static std::string make_table(Args... args);

    template <typename... Args>
        requires(std::convertible_to<Args, std::string> && ...)
    static std::string make_table_lines(Args... args);

    static std::optional<std::string> make_feedback_or_questions(const std::optional<std::vector<std::vector<std::string>>> &opt_items);

    static bool is_valid_link(const std::string &link);

    static std::string get_link(const std::string &what_to_get, const std::string &link_naam);

public:
    static std::string make_everything();
};