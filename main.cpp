#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "headers/header.hpp"

using std::string;

int main()
{
    string expression, background_color, color_axes, function_graph_color;

    JSON::getData(expression, background_color, color_axes, function_graph_color);
    std::cout << __cplusplus << "\n";
    
    std::cout << color_axes << "\n";
    std::cout << background_color << "\n";
    std::cout << function_graph_color << "\n";
    
    std::cout << expression << "\n";

    Parser::pointsConfig cfg;
    cfg.expression = expression;

    Parser::getPoints<double>(cfg);

    for (int i = 0; i < 1000; i++)
    {
        std::cout << cfg.array_x[i] << "\t" << cfg.array_y[i] << "\n";
    }
}
