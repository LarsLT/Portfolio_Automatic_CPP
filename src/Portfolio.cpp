#include "Portfolio.hh"
#include <iostream>
#include <fstream>
#include <string>

#include <ranges>
#include <algorithm>
#include <iterator>

#include "Input.hh"

Portfolio::Portfolio(const std::string &path)
{
    this->path = path;

    get_leeruitkomst();

    get_type();

    std::cout << zelf_groep_string << std::endl;
}

void Portfolio::update_portfolio(const std::string &table)
{
    std::ifstream inputFile(path);
    std::ofstream outputFile("temp.txt");

    if (!inputFile || !outputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line.find(zelf_groep_string) != std::string::npos)
        {
            line += "\n" + table;
        }
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::remove(path.c_str());
    std::rename("temp.txt", path.c_str());
}

void Portfolio::get_leeruitkomst()
{
    while (true)
    {
        std::string leeruitkomst = Input::get_input("geef je leeruitkomst als nummer of als text bvb (1/Analyseren)");

        if (std::isalpha(leeruitkomst[0]))
        {
            std::ranges::transform(leeruitkomst, leeruitkomst.begin(), [](unsigned char c)
                                   { return std::toupper(c); });

            if (leeruitkomst == "ANALYSEREN")
            {
                LU_number = 1;

                return;
            }
            else if (leeruitkomst == "ONTWERPEN")
            {
                LU_number = 2;

                return;
            }
            else if (leeruitkomst == "ADVISEREN")
            {
                LU_number = 3;

                return;
            }
            else if (leeruitkomst == "REALISEREN")
            {
                LU_number = 4;

                return;
            }
            else if (leeruitkomst == "BEHEREN")
            {
                LU_number = 5;

                return;
            }
            else if (leeruitkomst == "TOEKOMSTGERICHT-ORGANISEREN" || leeruitkomst == "TOEKOMSTGERICHT" || leeruitkomst == "ORGANISEREN")
            {
                LU_number = 6;

                return;
            }
            else if (leeruitkomst == "DOELGERICHT-INTERACTEREN" || leeruitkomst == "DOELGERICHT" || leeruitkomst == "INTERACTEREN")
            {
                LU_number = 7;

                return;
            }
            else if (leeruitkomst == "PERSOONLIJK-LEIDERSCHAP" || leeruitkomst == "PERSOONLIJK" || leeruitkomst == "LEIDERSCHAP")
            {
                LU_number = 8;

                return;
            }
            else if (leeruitkomst == "ONDERZOEK-PROBLEEM-OPLOSSEN" || leeruitkomst == "ONDERZOEK" || leeruitkomst == "PROBLEEM" || leeruitkomst == "OPLOSSEN")
            {
                LU_number = 9;

                return;
            }
        }
        else
        {
            int num = std::stoi(leeruitkomst);

            if (num > 0 && num < 10)
            {
                LU_number = num;
                return;
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
            zelf_groep_string = std::format("**Leeruitkomst {} Persoonlijke opdrachten:**", LU_number);

            return;
        }
        else if (leeruitkomst == "GROEP")
        {
            zelf_groep_string = std::format("**Leeruitkomst {} Groepsopdrachten:**", LU_number);

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
