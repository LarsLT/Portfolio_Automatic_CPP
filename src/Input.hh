#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <optional>
#include <format>

class Input
{
public:
    static std::string get_input(const std::string &what_to_get);
    static std::string get_input();

    template <typename... Args>
        requires(std::convertible_to<Args, std::string> && ...)

    static std::optional<std::vector<std::vector<std::string>>> get_multiple_input(const std::string &what_to_get, int amount_per_item, const Args &...args);

    static bool get_yes_no(const std::string &what_to_get);

    static void clear_console();
};

template <typename... Args> // waarom moet dit inline zijn // en deze moet helemaal in hh anders crash
    requires(std::convertible_to<Args, std::string> && ...)
inline std::optional<std::vector<std::vector<std::string>>> Input::get_multiple_input(const std::string &what_to_get, int amount_per_item, const Args &...args)
{
    std::cout << what_to_get << std::endl;

    if (!get_yes_no(std::format("Wil je verder met {}?\n", what_to_get)))
    {
        return std::nullopt;
    }

    std::vector<std::vector<std::string>> items;

    std::vector<std::string> item;

    std::vector<std::string> vec = {args...};

    while (true)
    {

        std::string input;

        switch (item.size())
        {
        case 0:
            std::cout << vec[0] << "\n";
            break;
        case 1:
            std::cout << vec[1] << "\n";
            break;
        case 2:
            std::cout << vec[2] << "\n";
            break;

        default:
            break;
        }

        std::getline(std::cin, input);

        item.push_back(input);

        if (item.size() == amount_per_item)
        {
            items.push_back(item);
            item.clear();

            if (!get_yes_no(std::format("Wil je verder met {}?\n", what_to_get)))
            {
                return items;
            }
        }
    }

    return items;
}

/*
[100%] Linking CXX executable Portfolio.exe
C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: CMakeFiles\Portfolio.dir/objects.a(Table.cpp.obj): in function `Table::make_everything[abi:cxx11]()':
C:/Projects/zelf/C++/Portfolio_Automatic_C--/src/Table.cpp:102:(.text+0x7d3): undefined reference to `std::optional<std::vector<std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >, std::allocator<std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > > > Input::get_multiple_input<char [17], char [21], char [19]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, char const (&) [17], char const (&) [21], char const (&) [19])'
C:/msys64/ucrt64/bin/../lib/gcc/x86_64-w64-mingw32/13.2.0/../../../../x86_64-w64-mingw32/bin/ld.exe: C:/Projects/zelf/C++/Portfolio_Automatic_C--/src/Table.cpp:105:(.text+0x844): undefined reference to `std::optional<std::vector<std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > >, std::allocator<std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::allocator<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > > > > > > Input::get_multiple_input<char [20], char [19]>(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, char const (&) [20], char const (&) [19])'
collect2.exe: error: ld returned 1 exit status
make[2]: *** [CMakeFiles\Portfolio.dir\build.make:165: Portfolio.exe] Error 1
make[1]: *** [CMakeFiles\Makefile2:86: CMakeFiles/Portfolio.dir/all] Error 2
make: *** [Makefile:90: all] Error 2
*/