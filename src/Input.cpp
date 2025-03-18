#include "Input.hh"
#include <iostream>
#include <string>

std::string Input::get_input(const std::string &what_to_get)
{
    std::string input;

    std::cout << what_to_get << std::endl;
    std::getline(std::cin, input);

    return input;
}