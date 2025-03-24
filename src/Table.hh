#pragma once
#include <string>
#include <vector>
#include <optional>
#include <concepts>

template <typename T> //TODO waarom stopt dit als het 2 zijn bvb 1 voor canvas
concept Github = std::convertible_to<T, std::string> &&
                 requires(T path) { std::string(path).find("https://github.com/") != std::string::npos; };

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

    static std::string get_link(const std::string &what_to_get);

    template <Github github>
    static std::string make_link(github &link);

    static std::string make_link(const std::string &link);

public:
    static std::string make_everything();
};