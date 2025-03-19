#include "Input.hh"
#include <iostream>
#include <string>
#include <vector>

bool Input::wil_je_verder(const std::string &what)
{
    std::cout << "Wil je verder met " << what << "?\n";

    std::string input;

    std::getline(std::cin, input);

    if (input == "J")
    {
        return true;
    }

    return false;
}

std::string Input::get_input(const std::string &what_to_get)
{
    std::string input;

    std::cout << what_to_get << std::endl;
    std::getline(std::cin, input);

    return input;
}

std::vector<std::vector<std::string>> Input::get_multiple_input(const std::string &what_to_get, int amount_per_item, const std::string &one, const std::string &two, const std::string &three)
{
    std::vector<std::vector<std::string>> items;

    std::vector<std::string> item;

    std::cout << what_to_get << std::endl;

    if (!wil_je_verder(what_to_get))
    {
        return items; // maak dit std::options;
    }

    while (true)
    {

        std::string input;

        switch (item.size())
        {
        case 0:
            std::cout << one << "\n";
            break;
        case 1:
            std::cout << two << "\n";
            break;
        case 2:
            std::cout << three << "\n";
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

            if (!wil_je_verder(what_to_get))
            {
                return items; // maak dit std::options;
            }
        }
    }

    return items;
}
