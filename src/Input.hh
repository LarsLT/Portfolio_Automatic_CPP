#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <optional>

class Input
{
public:
    static std::string get_input(const std::string &what_to_get);
    static std::optional<std::vector<std::vector<std::string>>> get_multiple_input(const std::string &what_to_get, int amount_per_item, const std::string &one = "This is a Problem", const std::string &two = "This is a Problem", const std::string &three = "This is a Problem");
    static bool get_yes_no(const std::string &what_to_get);
    static void clear_console();
};
