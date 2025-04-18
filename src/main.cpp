#include "Input.hh"
#include "Path.hh"
#include "Table.hh"
#include "Portfolio.hh"
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

    Portfolio portfolio(path);

    while (true)
    {
        std::cout << "Kies een functie om uit te voeren:\n";
        std::cout << "1. tabel toevoegen\n";
        std::cout << "2. Algemeen updaten\n";
        std::cout << "3. portfolio path updaten\n";
        std::cout << "4. Exit\n";

        std::string wat = Input::get_input("");

        int num;

        try
        {
            num = std::stoi(wat);
        }
        catch (const std::exception &e)
        {
            std::cout << "Couldnt conver " << wat << " to number\n\n";
            continue;
        }

        switch (num)
        {
        case 1:
        {
            std::string table = Table::make_everything();

            portfolio.add_item(table, std::nullopt);
            Input::clear_console();
            break;
        }
        case 2:
        {

            portfolio.update_algemeen();

            Input::clear_console();
            break;
        }
        case 3:
        {
            path.update_path(path.PORTFOLIO);
            Input::clear_console();
            portfolio = Portfolio(path);
            break;
        }
        case 4:
        {
            Input::clear_console();
            return 0;
            break;
        }

        default:
        {
            std::cout << "Kies een geldige optie\n";
            break;
        }
        }
    }
}
