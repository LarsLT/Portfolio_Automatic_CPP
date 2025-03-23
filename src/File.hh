#pragma once
#include <string>
#include "Path.hh"
#include <fstream>
#include <iostream>

class File
{
public:
    template <typename Functor>
    static void write_file(const std::string &path, Functor func);

    template <typename Functor>
    static void read_file(const std::string &path, Functor func);
};

template <typename Functor>
void File::write_file(const std::string &path, Functor func)
{
    std::ifstream inputFile(path);
    std::ofstream outputFile("temp.txt");

    if (!inputFile || !outputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    bool wrote_item = false;

    std::string line;
    while (std::getline(inputFile, line))
    {
        line = func(line).value_or(line);
        outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();

    std::remove(path.c_str());
    std::rename("temp.txt", path.c_str());
}

template <typename Functor>
inline void File::read_file(const std::string &path, Functor func)
{
    std::ifstream inputFile(path);

    if (!inputFile)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(inputFile, line))
    {
        func(line);
    }

    inputFile.close();
}
