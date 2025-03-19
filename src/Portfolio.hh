#pragma once
#include <string>
#include <fstream>

class Portfolio
{
private:
    std::string path;
    int LU_number;
    std::string zelf_groep_string;

public:
    Portfolio(const std::string &path);

    void update_portfolio(const std::string &table);

private:
    void get_leeruitkomst();

    void get_type();
};