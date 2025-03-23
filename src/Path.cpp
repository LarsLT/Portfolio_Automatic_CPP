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

void Path::set_paths(const std::string &path)
{
    std::ifstream inputFile(path);

    if (!inputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    std::regex pattern(R"((\w+):\s*([A-Z]:/[^ \n\r]+))");
    std::smatch match;

    while (std::getline(inputFile, line))
    {
        if (std::regex_search(line, match, pattern))
        {
            std::string key = match[1].str();
            std::string value = match[2].str();

            if (key == "Portfolio")
                portfolio_path = value;
            else if (key == "Storage")
                storage_path = value;
            else if (key == "Gemaakt")
                gemaakt_path = value;
        }
    }

    inputFile.close();
}

void Path::set_paths()
{
    std::ifstream inputFile(storage_path.value());

    if (!inputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    std::regex pattern(R"((\w+):\s*([A-Z]:/[^ \n\r]+))");
    std::smatch match;

    while (std::getline(inputFile, line))
    {
        if (std::regex_search(line, match, pattern))
        {
            std::string key = match[1].str();
            std::string value = match[2].str();

            if (key == "Portfolio")
                portfolio_path = value;
        }
    }

    inputFile.close();
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

    std::ifstream inputFile(storage_path.value());
    std::ofstream outputFile("temp.txt");

    if (!inputFile || !outputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;

    while (std::getline(inputFile, line))
    {
        if (std::regex_search(line, pattern))
        {
            line = new_line;
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::remove(storage_path.value().c_str());
    std::rename("temp.txt", storage_path.value().c_str());
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

        switch (path)
        {
        case PORTFOLIO:
            path_string = Input::get_input("geef het path naar je portfolio.");
            if (validate_path(path_string))
            {
                update_path(path_string, path);
                return;
            }

            break;
        case STORAGE:
            path_string = Input::get_input("geef het path naar je storage file.");
            if (validate_path(path_string))
            {
                update_path(path_string, path);
                return;
            }

            break;
        }

        std::cout << "not a good global path :)\n"
                  << "make sure that it goes to a txt or md file and has forward /";
    }
}

Path::Path(const std::string &path)
{
    set_paths(path);
}

Path::Path()
{
    update_path(Paths::STORAGE);

    set_paths();
}
