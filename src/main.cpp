#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
#include "Input.hh"
#include <iostream>

int main()
{
    Portfolio portfolio("C:/Projects/zelf/Portfolio_Automatic_C++/portfolio.md");

    // std::string table = Table::make_everything();

    portfolio.update_algemeen();
}
