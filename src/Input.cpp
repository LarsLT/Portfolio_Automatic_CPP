#include "Input.hh"
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <format>
#include <stdlib.h>

namespace Input
{
    std::string get_input(const std::string &what_to_get)
    {
        std::string input;

        std::cout << what_to_get << std::endl;
        std::getline(std::cin, input);

        return input;
    }

    std::string get_input()
    {
        std::string input;

        std::getline(std::cin, input);

        return input;
    }

    bool get_yes_no(const std::string &what_to_get)
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

    void clear_console()
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
} // namespace Input
