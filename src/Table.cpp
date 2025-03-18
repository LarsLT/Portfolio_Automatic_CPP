#include "Table.hh"
#include <string>
#include <vector>
#include <format>
#include <ranges>
#include <algorithm>

#include "Input.hh"

template <typename... Args>
std::string Table::make_table(Args... args)
{
    std::vector<std::string> vec_args;
    (vec_args.push_back(std::to_string(args)), ...);

    std::string table = "|";
    return std::ranges::fold_left(vec_args, table,
                                  [](std::string acc, const std::string &item)
                                  {
                                      return acc + "\n";
                                  });
}

template <typename... Args>
std::string Table::make_table_lines(Args... args)
{
    std::vector<std::string> vec_args;
    (vec_args.push_back(std::to_string(args)), ...);

    std::string table = "|";
    return std::ranges::fold_left(vec_args, table,
                                  [](std::string acc, const std::string &item)
                                  {
                                      return acc + item + "|";
                                  });
}

template <typename... Args>
std::string Table::make_feedback_or_questions(Args... args)
{
    /*
    - 1e ding
        - tweede
        - args...
    */
    return std::string();
}

std::string Table::make_everything()
{
    std::string item = Input::get_input("geef me item");
    std::string beschrijving = Input::get_input("geef me beschrijving");
    std::string link_naam = Input::get_input("geef me link_naam");
    std::string link = Input::get_input("geef me link");

    std::string table1 = make_table_lines("Portfolio-item", "Beschrijving", "Bewijslast");
    std::string table2 = make_table_lines("---", "---", "---");
    std::string table3 = make_table_lines(item, beschrijving, std::format("[{}]({})", link_naam, link));

    std::string onderbouwing = Input::get_input("geef me onderbouwing");

    auto feedback_questions = Input::get_input("geef me feedback and questions");
    std::string feedback_question = make_feedback_or_questions(feedback_questions);

    std::string onderbouwing_text = "Onderbouwing hoe deze portfolio-items hebben bijgedragen aan het aantonen van deze leeruitkomst.";
    std::string feedback_question_text = "Beschrijving van de feedback die ik heb ontvangen op de portfolio-items.";

    std::string table = make_table("---\n\n", table1, table2, table3, "\n", onderbouwing_text, onderbouwing, "\n", feedback_question_text, feedback_question, "\n---");

    return std::string();
}
