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

#include "Path.hh"

#include "Input.hh"

void Portfolio::add_item(const std::string &added_line, std::optional<std::string> find_line = std::nullopt)
{
    if (LU_number.has_value()) // TODO i dont like 2 if in 1
    {
        std::cout << "klopt dit?\n"
                  << zelf_groep_string.value() << std::endl;

        if (Input::get_yes_no(""))
        {
            get_leeruitkomst();
            get_type();
        }
    }
    else
    {
        get_leeruitkomst();
        get_type();
    }

    std::ifstream inputFile(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n"));
    std::ofstream outputFile("temp.txt");

    if (!inputFile || !outputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.find(find_line.value_or(zelf_groep_string.value())) != std::string::npos)
        {
            line += "\n" + added_line;
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::remove(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
    std::rename("temp.txt", path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
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
    std::ifstream inputFile(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n"));
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

    std::remove(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
    std::rename("temp.txt", path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
}

void Portfolio::override_next_item(const std::string &new_line, std::string find_line)
{
    std::ifstream inputFile(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n"));
    std::ofstream outputFile("temp.txt");

    if (!inputFile || !outputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    bool item_found = false;

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.find(find_line) != std::string::npos)
        {
            item_found = true;
        }
        else if (item_found)
        {
            line = new_line;
            item_found = false;
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::remove(path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
    std::rename("temp.txt", path.get_path(path.PORTFOLIO).value_or(std::cerr << "\nPortfolio path is wrong\n").c_str());
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

        if (std::isalpha(leeruitkomst[0])) // TODO i dont like 2 if in 1
        {
            std::ranges::transform(leeruitkomst, leeruitkomst.begin(), [](unsigned char c)
                                   { return std::toupper(c); });

            if (auto it = lookupTable.find(leeruitkomst); it != lookupTable.end())
            {
                LU_number = it->second;
                return;
            }
        }
        else // TODO else try if i dont like it
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

/*

open 2 files

read every line till your line

append data to your line

write to the temp file

remove old file
rename new file/remp file

*/
