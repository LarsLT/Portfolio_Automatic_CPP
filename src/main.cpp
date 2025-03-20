#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
#include "Input.hh"
#include <iostream>
#include <string>
#include <format>

Path storage_path()
{
    Input::clear_console();
    std::string path = "C:/Projects/zelf/C++/Portfolio_Automatic_C--/storage/storage.txt";

    if (Input::get_yes_no(std::format("Klopt dit path\n{}\n", path)))
    {
        Input::clear_console();
        return Path(path);
    }
    else
    {
        Input::clear_console();
        return Path();
    }
}

int main()
{
    Input::clear_console();

    Path path = storage_path();

    while (true)
    {
        std::cout << "Kies een functie om uit te voeren:\n";
        std::cout << "1. tabel toevoegen\n";
        std::cout << "2. portfolio path updaten\n";
        std::cout << "3. Algemeen updaten\n";
        std::cout << "4. Exit\n";

        std::string wat = Input::get_input("");

        switch (std::stoi(wat))
        {
        case 1:
        {
            Portfolio portfolio(path); // TODO dont like creating an object for bs
            std::string table = Table::make_everything();

            portfolio.add_item(table, std::nullopt);
            Input::clear_console();
            break;
        }
        case 2:
        {
            path.update_path(path.PORTFOLIO);
            Input::clear_console();
            break;
        }
        case 3:
        {
            Portfolio portfolio(path); // TODO dont like creating an object for bs

            portfolio.update_algemeen();

            Input::clear_console();
            break;
        }
        case 4:
        {
            return 0;
            Input::clear_console();
            break;
        }

        default:
        {
            break;
        }
        }
    }
}
