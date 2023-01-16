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

    double array_y[2000];
    {
        int i = 0;
        double x = -5;
        for (; x <= 5; x += 0.01, i++)
        {
            cfg.array_x[i] = x;
        }
    }


    Parser::getPoints<double>(cfg);

    // array_y = cfg.array_y
}
/*
configuring arrays with relevant x and y points


*/