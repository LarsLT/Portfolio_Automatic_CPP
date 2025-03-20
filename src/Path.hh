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
        STORAGE,
    };

    std::optional<std::string> get_path(const Paths &path);

    void update_path(const Paths &path);

    Path(const std::string &path);

private:
    void set_paths(const std::string &path);
    void update_path(const std::string &path, const Paths &p);
};