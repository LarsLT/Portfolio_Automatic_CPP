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
            else if (key == "storage")
                storage_path = value;
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
    }

    return std::nullopt;
}

void Path::update_path(const Paths &path)
{
    switch (path)
    {
    case PORTFOLIO:
        portfolio_path = Input::get_input("geef het path naar je portfolio.");
        update_path(portfolio_path.value(), path);
        break;
    case STORAGE:
        storage_path = Input::get_input("geef het path naar je stroage file.");
        update_path(storage_path.value(), path);
        break;
    }
}

Path::Path(const std::string &path)
{
    set_paths(path);
}