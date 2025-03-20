#pragma once
#include <string>
#include <optional>
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
        GEMAAKT,
        STORAGE,
    };

    std::optional<std::string> get_path(Paths path);

    void update_path(Paths path);

    Path(std::string path);

private:
    void set_paths(std::string path);
    void update_path(std::string path, Paths p);
};