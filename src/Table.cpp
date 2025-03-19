#include "Table.hh"
#include <string>
#include <format>
#include <regex>
#include <vector>
#include <ranges>
#include <ranges>
#include <iterator>
#include <algorithm>

#include "Input.hh"

std::string Table::make_feedback_or_questions(const std::vector<std::vector<std::string>> &items)
{
    std::string q_f = "";

    if (items.size() == 0)
    {
        return std::string();
    }
    else if (items[0].size() == 2)
    {
        std::ranges::for_each(items, [&q_f](const std::vector<std::string> &item)
                              { q_f += std::format("- {}\n    - {}", item[0], item[1]); });
    }
    else if (items[0].size() == 3)
    {
        std::ranges::for_each(items, [&q_f](const std::vector<std::string> &item)
                              { q_f += std::format("- {}\n    - {}\n    - {}\n", item[0], item[1], item[2]); });
    }

    return q_f;
}

bool Table::is_valid_link(const std::string &link)
{
    const std::regex link_regex(R"(^(https?:\/\/)([a-zA-Z0-9\-\.]+)\.(nl|com)$)");
    return std::regex_match(link, link_regex);
}

std::string Table::get_link(const std::string &what_to_get, const std::string &link_naam)
{
    while (true)
    {
        std::string link = Input::get_input(what_to_get);

        if (is_valid_link(link))
        {
            return std::format("[{}]({})", link_naam, link);
        }

        std::cout << "Not a Valid Link" << std::endl;
    }
}

std::string Table::make_everything()
{
    std::string item = Input::get_input("geef me item");
    std::string beschrijving = Input::get_input("geef me beschrijving");
    std::string link_naam = Input::get_input("geef me link_naam");
    std::string link = get_link("Geef me de link", link_naam);

    std::string table1 = make_table_lines("Portfolio-item", "Beschrijving", "Bewijslast");
    std::string table2 = make_table_lines("---", "---", "---");
    std::string table3 = make_table_lines(item, beschrijving, link);

    std::string onderbouwing = Input::get_input("geef me onderbouwing");

    std::vector<std::vector<std::string>> questions = Input::get_multiple_input("questions", 3, "geef me de vraag", "geef me het antwoord", "geef me je verwerk");
    std::vector<std::vector<std::string>> feedback = Input::get_multiple_input("feedback", 2, "geef me de feedback", "geef me je verwerk");

    std::string feedback_question = std::format("{}\n{}", make_feedback_or_questions(feedback), make_feedback_or_questions(questions));

    std::string onderbouwing_text = "Onderbouwing hoe deze portfolio-items hebben bijgedragen aan het aantonen van deze leeruitkomst.";
    std::string feedback_question_text = "Beschrijving van de feedback die ik heb ontvangen op de portfolio-items.";

    std::string table = make_table("---\n\n", table1, table2, table3, "\n", onderbouwing_text, onderbouwing, "\n", feedback_question_text, feedback_question, "\n---");

    return table;
}