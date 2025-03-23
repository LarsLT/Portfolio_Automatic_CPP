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