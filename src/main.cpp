#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
#include "Input.hh"
#include <iostream>

int main()
{
    while (true)
    {
        Portfolio portfolio("C:/Projects/zelf/C++/Portfolio_Automatic_C--/storage/storage.txt");

        std::string table = Table::make_everything();

        portfolio.add_item(table, std::nullopt);
    }
}
