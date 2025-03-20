#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
#include "Input.hh"
#include <iostream>

int main()
{
    Path path("C:/Projects/zelf/Portfolio_Automatic_C++/storage/storage.txt");

    path.update_path(path.PORTFOLIO);
}
