#pragma once
#include <string>

class Path
{
private:
    enum Paths
    {
        PORTFOLIO,
        GEMAAKT,
        STORAGE,
    };

public: 
    std::string get_path(Paths path);

    Path();
    ~Path();
};