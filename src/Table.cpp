#include "Table.hh"
#include <string>
#include <format>
#include <regex>
#include <vector>
#include <ranges>
#include <ranges>
#include <iterator>
#include <algorithm>
#include <optional>

#include "Input.hh"

template <typename... Args> // waarom moet dit inline zijn
    requires(std::convertible_to<Args, std::string> && ...)
inline std::string Table::make_table(Args... args)
{
    std::string table = "";
    ((table += std::string(args) + "\n"), ...);
    return table;
}

template <typename... Args> // waarom moet dit inline zijn
    requires(std::convertible_to<Args, std::string> && ...)
inline std::string Table::make_table_lines(Args... args)
{
    std::string table = "|";
    ((table += " " + std::string(args) + " |"), ...);
    return table;
}

std::optional<std::string> Table::make_feedback_or_questions(const std::optional<std::vector<std::vector<std::string>>> &opt_items)
{

    if (!opt_items.has_value())
    {
        return std::nullopt;
    }

    std::string q_f = "";

    std::vector<std::vector<std::string>> items = opt_items.value();

    if (items[0].size() == 2)
    {
        std::ranges::for_each(items, [&q_f](const std::vector<std::string> &item)
                              { q_f += std::format("- {}\n  - {}\n", item[0], item[1]); });
    }
    else if (items[0].size() == 3)
    {
        std::ranges::for_each(items, [&q_f](const std::vector<std::string> &item)
                              { q_f += std::format("- {}\n  - {}\n  - {}\n", item[0], item[1], item[2]); });
    }

    return q_f;
}

bool Table::is_valid_link(const std::string &link)
{
    const std::regex link_regex(R"(^(https?:\/\/(?:[a-zA-Z0-9\-\.]+)\.([a-zA-Z]{2,})(?:\/[^\s]*)?)$)");
    return std::regex_match(link, link_regex);
}

std::string Table::get_link(const std::string &what_to_get)
{
    while (true)
    {
        std::string link = Input::get_input(what_to_get);

        if (is_valid_link(link))
        {
            return link;
        }

        std::cout << "Not a Valid Link" << std::endl;
    }
}

template <Github github>
std::string Table::make_link(github &link)
{
    return std::format("[Github]({})", link);
}

std::string Table::make_link(const std::string &link)
{
    Input::clear_console();

    std::string link_naam = Input::get_input("Geef me de linknaam");

    return std::format("[{}]({})", link_naam, link);
}

std::string Table::make_everything()
{
    Input::clear_console();
    std::string item = Input::get_input("geef me item");

    Input::clear_console();
    std::string beschrijving = Input::get_input("geef me beschrijving");

    Input::clear_console();
    std::string link = get_link("Geef me de link");

    std::string md_link = make_link(link);

    std::string table1 = make_table_lines("Portfolio-item", "Beschrijving", "Bewijslast");
    std::string table2 = make_table_lines("---", "---", "---");
    std::string table3 = make_table_lines(item, beschrijving, md_link);

    Input::clear_console();
    std::string onderbouwing = "- ";
    onderbouwing += Input::get_input("geef me onderbouwing");

    Input::clear_console();
    std::optional<std::vector<std::vector<std::string>>> questions = Input::get_multiple_input("questions", 3, "geef me de vraag", "geef me het antwoord", "geef me je verwerk");

    Input::clear_console();
    std::optional<std::vector<std::vector<std::string>>> feedback = Input::get_multiple_input("feedback", 2, "geef me de feedback", "geef me je verwerk");

    std::string feedback_question = std::format("{}\n{}", make_feedback_or_questions(feedback).value_or("- Geen feedback"), make_feedback_or_questions(questions).value_or("- Geen vragen"));

    std::string onderbouwing_text = "Onderbouwing hoe deze portfolio-items hebben bijgedragen aan het aantonen van deze leeruitkomst.";
    std::string feedback_question_text = "Beschrijving van de feedback die ik heb ontvangen op de portfolio-items.";

    std::string table = make_table("\n", table1, table2, table3, "\n", onderbouwing_text, onderbouwing, "\n", feedback_question_text, feedback_question, "\n---");

    Input::clear_console();

    return table;
}