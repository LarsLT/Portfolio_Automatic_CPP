#pragma once
#include <string>
#include <vector>
#include <optional>

class Table
{
private:
    template <typename... Args> // waarom moet dit in .hh file
        requires(std::convertible_to<Args, std::string> && ...)
    std::string make_table(Args... args)
    {
        std::string table = "";
        ((table += std::string(args) + "\n"), ...);
        return table;
    }

    template <typename... Args> // waarom moet dit in .hh file
        requires(std::convertible_to<Args, std::string> && ...)
    std::string make_table_lines(Args... args)
    {
        std::string table = "|";
        ((table += " " + std::string(args) + " |"), ...);
        return table;
    }

    std::optional<std::string> make_feedback_or_questions(const std::optional<std::vector<std::vector<std::string>>> &opt_items);

    bool is_valid_link(const std::string &link);

    std::string get_link(const std::string &what_to_get, const std::string &link_naam);

public:
    std::string make_everything();
};