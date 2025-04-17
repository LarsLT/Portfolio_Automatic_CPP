#include "Portfolio.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include <ranges>
#include <algorithm>
#include <iterator>
#include <regex>
#include <format>

#include <mutex>

#include "Path.hh"
#include "Input.hh"
#include "File.hh"

void Portfolio::add_item(const std::string &added_line, std::optional<std::string> find_line = std::nullopt)
{
    get_item(added_line);
    get_leeruitkomst();
    get_type();
    store_item();

    auto func = [&, this](const std::string &line) -> std::optional<std::string>
    {
        if (line.find(find_line.value_or(zelf_groep_string.value())) != std::string::npos)
        {
            return line + added_line;
        };

        return std::nullopt;
    };

    File::write_file(path.get_path(path.PORTFOLIO).value(), func);
}

void Portfolio::update_algemeen()
{
    std::regex pattern_peil(R"(\|\s*\*(Peilmoment)\*\s*\|)");
    std::regex pattern_date(R"(\|\s*\*(Datum)\*\s*\|)");

    std::string num = Input::get_input("welk peilmoment is dit");
    std::string peilmoment = std::format("| *Peilmoment*    | `peilmoment {}`   |", num);
    override_item(peilmoment, pattern_peil);

    std::string date = Input::get_input("welke datum van inlevering");
    std::string date_text = std::format("| *Datum*         | `{}` |", date);
    override_item(date_text, pattern_date);

    std::string trots = Input::get_input("Waar ik het meest trots op ben:");
    override_next_item(std::format("- {}", trots), "*Waar ik het meest trots op ben:*");

    std::string moeite = Input::get_input("Waar ik de afgelopen periode moeite mee heb gehad en welke actie ik heb ondernomen:");
    override_next_item(std::format("- {}", moeite), "*Waar ik de afgelopen periode moeite mee heb gehad en welke actie ik heb ondernomen:*");

    std::string leren = Input::get_input("Wat ik nog graag wil leren en welke actie ik wil gaan ondernemen:");
    override_next_item(std::format("- {}", leren), "*Wat ik nog graag wil leren en welke actie ik wil gaan ondernemen:*");
}

void Portfolio::override_item(const std::string &new_line, const std::regex &pattern)
{
    auto func = [&](const std::string &line) -> std::optional<std::string>
    {
        if (std::regex_search(line, pattern))
        {
            return new_line;
        };
        return std::nullopt;
    };

    File::write_file(path.get_path(path.PORTFOLIO).value(), func);
}

void Portfolio::override_next_item(const std::string &new_line, std::string find_line)
{
    bool item_found = false;

    auto func = [&](const std::string &line) -> std::optional<std::string>
    {
        std::optional<std::string> result;

        if (line.find(find_line) != std::string::npos)
        {
            item_found = true;
        }
        else if (item_found)
        {
            result = new_line;
            item_found = false;
        }
        return result;
    };

    File::write_file(path.get_path(path.PORTFOLIO).value(), func);
}

void Portfolio::get_leeruitkomst()
{
    while (true)
    {
        std::string leeruitkomst = Input::get_input("geef je leeruitkomst als nummer of als text bvb (1/Analyseren)");

        // beter than an unlimited if i guess
        static const std::unordered_map<std::string, int> lookupTable = {
            {"ANALYSEREN", 1},
            {"ONTWERPEN", 2},
            {"ADVISEREN", 3},
            {"REALISEREN", 4},
            {"BEHEREN", 5},
            {"TOEKOMSTGERICHT-ORGANISEREN", 6},
            {"TOEKOMSTGERICHT", 6},
            {"ORGANISEREN", 6},
            {"DOELGERICHT-INTERACTEREN", 7},
            {"DOELGERICHT", 7},
            {"INTERACTEREN", 7},
            {"PERSOONLIJK-LEIDERSCHAP", 8},
            {"PERSOONLIJK", 8},
            {"LEIDERSCHAP", 8},
            {"ONDERZOEK-PROBLEEM-OPLOSSEN", 9},
            {"ONDERZOEK", 9},
            {"PROBLEEM", 9},
            {"OPLOSSEN", 9}};

        if (std::isalpha(leeruitkomst[0]))
        {
            std::ranges::transform(leeruitkomst, leeruitkomst.begin(), [](unsigned char c)
                                   { return std::toupper(c); });

            if (auto it = lookupTable.find(leeruitkomst); it != lookupTable.end())
            {
                LU_number = it->second;
                return;
            }
        }
        else
        {
            try
            {
                int num = std::stoi(leeruitkomst);
                if (num > 0 && num < 10)
                {
                    LU_number = num;
                    return;
                }
            }
            catch (const std::exception &)
            {
                std::cout << "something went wrong\n";
            }
        }
    }
}

void Portfolio::get_type()
{
    while (true)
    {
        std::string leeruitkomst = Input::get_input("groep of opdracht voor je zelf (groep/zelf)");

        std::ranges::transform(leeruitkomst, leeruitkomst.begin(), [](unsigned char c)
                               { return std::toupper(c); });

        if (leeruitkomst == "ZELF")
        {
            zelf_groep_string = std::format("**Leeruitkomst {} Persoonlijke opdrachten:**", LU_number.value());

            return;
        }
        else if (leeruitkomst == "GROEP")
        {
            zelf_groep_string = std::format("**Leeruitkomst {} Groepsopdrachten:**", LU_number.value());

            return;
        }
    }
}

void Portfolio::get_item(const std::string &table)
{
    const std::regex link_regex(R"(\| ([A-Za-z0-9]+) \| [A-Za-z]+ \| \[[^\]]*\]\([^)]*\) \|)");
    std::smatch match;

    auto items = table | std::views::split('\n') |
                 std::views::transform([](auto &&line)
                                       { return std::string(line.begin(), line.end()); }) |
                 std::views::filter([&](const std::string &line_str)
                                    { return std::regex_match(line_str, match, link_regex) && match.size() > 1; }) |
                 std::views::transform([&](const std::string &)
                                       { return match[1].str(); });

    item = *items.begin();
}

void Portfolio::store_item()
{
    std::once_flag flag;

    auto func = [&flag, this](const std::string &line) -> std::optional<std::string>
    {
        std::optional<std::string> result;

        std::call_once(flag, [&]()
                       { result = line + std::format("\n{}: {}", item.value(), zelf_groep_string.value()); });

        return result;
    };

    File::write_file(path.get_path(path.GEMAAKT).value(), func);
}

/*

open 2 files

read every line till your line

append data to your line

write to the temp file

remove old file
rename new file/remp file

*/
