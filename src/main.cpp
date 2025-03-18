#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
#include "Input.hh"
#include <iostream>

int main()
{
    Table table;
    std::string table2 = table.make_everything();

    std::cout << table2 << std::endl;
}
