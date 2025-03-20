#pragma once
#include <string>
#include <fstream>
#include <regex>
#include <optional>

#include "Path.hh"
class Portfolio
{
private:
    std::optional<int> LU_number = std::nullopt;
    std::optional<std::string> zelf_groep_string = std::nullopt;

    Path path;

public:
    Portfolio(const std::string &path_naar_storage) : path(Path(path_naar_storage)) {};

    void add_item(const std::string &added_line, std::optional<std::string> find_line);

    void update_algemeen();


private:
    void override_item(const std::string &new_line, const std::regex &pattern);
    void override_next_item(const std::string &new_line, std::string find_line);

    void get_leeruitkomst();

    void get_type();

    void store_item(const std::string &item, const std::string &link);
};

/*
Ik ben het meest trots op de code vooruitgangen die ik nu al heb gemaakt, dit jaar ben ik voor het eerst bezig geweest met regex, algorithms/ranges/views/iterator & Variadic templates
s in C++, na wel al een beetje ervaring met Rust, en denk dat ik dit goed begin te begrijpen (copium :) )

De afgelopen periode vond ik het moeilijk om een goede tech lead te zijn van mijn team en ga er daarom voor zorgen dat ik dit de volgende sprint/periode dit beter
 ga doen, om hiervoor te zorgen ga ik, zodra ik beter ben, naar Jan of Nick om ze vragen te stellen hoe ik hier beter in kan worden.

 Ik wil doorgaan met veel beter worden in C++ door Concepts/sfinea/CRTP/etc te begin te begrijpen
*/