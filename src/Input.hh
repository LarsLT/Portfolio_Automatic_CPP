#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <format>

class Input
{
public:
    static std::string get_input(const std::string &what_to_get);

    template <typename... Args>
        requires(std::convertible_to<Args, std::string> && ...)
    static std::optional<std::vector<std::vector<std::string>>> get_multiple_input(const std::string &what_to_get, int amount_per_item, const Args &...args);
    static bool get_yes_no(const std::string &what_to_get);
    static void clear_console();
};

template <typename... Args> // waarom moet dit inline zijn
    requires(std::convertible_to<Args, std::string> && ...)
inline std::optional<std::vector<std::vector<std::string>>> Input::get_multiple_input(const std::string &what_to_get, int amount_per_item, const Args &...args)
{
    std::cout << what_to_get << std::endl;

    if (!get_yes_no(std::format("Wil je verder met {}?\n", what_to_get)))
    {
        return std::nullopt;
    }

    std::vector<std::vector<std::string>> items;

    std::vector<std::string> item;

    std::vector<std::string> vec = {args...};

    while (true)
    {

        std::string input;

        switch (item.size())
        {
        case 0:
            std::cout << vec[0] << "\n";
            break;
        case 1:
            std::cout << vec[1] << "\n";
            break;
        case 2:
            std::cout << vec[2] << "\n";
            break;

        default:
            break;
        }

        std::getline(std::cin, input);

        item.push_back(input);

        if (item.size() == amount_per_item)
        {
            items.push_back(item);
            item.clear();

            if (!get_yes_no(std::format("Wil je verder met {}?\n", what_to_get)))
            {
                return items;
            }
        }
    }

    return items;
}