#include "Input.hh"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <format>
#include <stdlib.h>

std::string Input::get_input(const std::string &what_to_get)
{
    std::string input;

    std::cout << what_to_get << std::endl;
    std::getline(std::cin, input);

    return input;
}

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

bool Input::get_yes_no(const std::string &what_to_get)
{
    std::cout << what_to_get;

    while (true)
    {
        std::string input;

        std::getline(std::cin, input);

        if (std::toupper(input[0]) == 'J')
        {
            return true;
        }
        else if (std::toupper(input[0]) == 'N')
        {
            return false;
        }
        else
        {
            std::cout << "alleen Ja Of Nee\n";
        }
    }
}

void Input::clear_console()
{
#if defined(_DEBUG)
    if (!isDebuggerAttached())
    {
        system("cls");
    }
#else
    system("cls");
#endif
}