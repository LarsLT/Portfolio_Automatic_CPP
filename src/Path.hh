#pragma once
#include <string>
#include <optional>
#include <concepts>
#include <ranges>
#include <regex>
#include <iostream>

template <typename T>
concept backslash_path = requires(T path) {
    { path.find('\\') != std::string::npos };
    std::string(path);
};

class Path
{
private:
    std::optional<std::string> portfolio_path = std::nullopt;
    std::optional<std::string> gemaakt_path = std::nullopt;
    std::optional<std::string> storage_path = std::nullopt;

public:
    enum Paths
    {
        PORTFOLIO,
        STORAGE,
        GEMAAKT
    };

    std::optional<std::string> get_path(const Paths &path);

    void update_path(const Paths &path);

    Path(const std::string &path);
    Path();

private:
    void set_paths();
    void update_path(const std::string &path, const Paths &p);

    template <backslash_path T>
    bool validate_path(T &path);

    bool validate_path(const std::string &path);

    friend std::ostream &operator<<(std::ostream &os, const Paths &path);
};