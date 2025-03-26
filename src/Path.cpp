#include "Path.hh"
#include "Input.hh"
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <format>
#include <map>

#include "File.hh"

void Path::set_paths()
{
    std::map<std::string, std::string> path_map;

    std::regex pattern(R"((\w+):\s*([A-Z]:/[^ \n\r]+))");
    std::smatch match;

    auto func = [&match, &pattern, this](const std::string &line)
    {
        if (std::regex_search(line, match, pattern))
        {
            std::string key = match[1].str();
            std::string value = match[2].str();

            if (key == "Portfolio")
                portfolio_path = value;
            if (key == "Gemaakt")
                gemaakt_path = value;
        }

        return std::nullopt;
    };

    File::read_file(storage_path.value(), func);
}

void Path::update_path(const std::string &path, const Paths &p)
{
    std::regex pattern;
    std::string new_line;

    switch (p)
    {
    case PORTFOLIO:
        pattern = std::regex(R"(Portfolio:\s*[A-Z]:/[^ \n\r]+)");
        new_line = std::format("Portfolio: {}", path);
        portfolio_path = path;
        break;
    case STORAGE:
        pattern = std::regex(R"(Storage:\s*[A-Z]:/[^ \n\r]+)");
        new_line = std::format("Storage: {}", path);
        storage_path = path;
        break;
    case GEMAAKT:
        pattern = std::regex(R"(Gemaakt:\s*[A-Z]:/[^ \n\r]+)");
        new_line = std::format("Gemaakt: {}", path);
        gemaakt_path = path;
        break;
    }

    auto func = [&](const std::string &line) -> std::optional<std::string>
    {
        if (std::regex_search(line, pattern))
        {
            return new_line;
        }

        return std::nullopt;
    };

    File::write_file(storage_path.value(), func);
}

bool Path::validate_path(const std::string &path)
{
    const std::regex path_regex(R"(^(?:[a-zA-Z]:\/(?:[^\/:*?"<>|]+\/)*[^\/:*?"<>|]+\.(md|txt))$)");
    return std::regex_match(path, path_regex);
}

template <backslash_path T>
inline bool Path::validate_path(T &path)
{
    std::string pathStr(path);

    auto result = pathStr | std::views::transform([](char c)
                                                  { return c == '\\' ? '/' : c; }) |
                  std::views::common;

    path = {result.begin(), result.end()};

    const std::regex path_regex(R"(^(?:[a-zA-Z]:\/(?:[^\/:*?"<>|]+\/)*[^\/:*?"<>|]+\.(md|txt))$)");
    return std::regex_match(path, path_regex);
}

std::optional<std::string> Path::get_path(const Paths &path)
{
    switch (path)
    {
    case PORTFOLIO:
        return portfolio_path;
        break;
    case STORAGE:
        return storage_path;
        break;
    case GEMAAKT:
        return gemaakt_path;
        break;
    }

    return std::nullopt;
}

void Path::update_path(const Paths &path)
{
    while (true)
    {
        std::string path_string = "";
        Input::clear_console();

        std::cout << "geef het path naar je " << path << std::endlfile;

        path_string = Input::get_input();
        if (validate_path(path_string))
        {
            update_path(path_string, path);
            return;
        }

        std::cout << "not a good global path :)\n"
                  << "make sure that it goes to a txt or md file and has forward /";
    }
}

Path::Path(const std::string &path)
{
    storage_path = path;

    set_paths();
}

Path::Path()
{
    update_path(Paths::STORAGE);

    set_paths();
}

std::ostream &operator<<(std::ostream &os, const Path::Paths &path)
{
    switch (path)
    {
    case Path::PORTFOLIO:
        os << "Portfolio file";
        break;
    case Path::STORAGE:
        os << "Storage file";
        break;
    case Path::GEMAAKT:
        os << "Gemaakt file";
        break;

    default:
        break;
    }

    return os;
}
