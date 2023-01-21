#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <json/value.h>
#include <json/json.h>

#include "exprtk.hpp"
#include <chrono>

using std::string;
using std::cout;
using namespace std::chrono;

namespace Parser
{
    struct pointsConfig
    {
        int range = 0;
        int size = 0;
        double array_x[2000];
        double array_y[2000];
        string expression = "";
    };
    
    struct windowConfig
    {
        string colorAxes = "#000000";
        string colorBackground = "#ffffff";
        string colorFunctionGraph = "#00ff00";
        int width = 500;
        int height = 500;
    };
    
    template <typename T>
    void getPoints(pointsConfig &CFG)
    {
        
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T>   expression_t;
        typedef exprtk::parser<T>       parser_t;

        const string expression_string = CFG.expression;
        cout << expression_string << 9498;

        T x;

        symbol_table_t symbol_table;
        symbol_table.add_variable("x", x);
        symbol_table.add_constants();

        expression_t expression;
        expression.register_symbol_table(symbol_table);

        parser_t parser;
        parser.compile(expression_string, expression);
        
        auto start = high_resolution_clock::now();
        {
            int i = 0;
            int range = CFG.range;
            for (x = T(-range); x <= T(+range); i++, x += T(0.01))
            {
                const T y = expression.value();
                CFG.array_x[i] = x;
                CFG.array_y[i] = y;
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
 
        // To get the value of duration use the count()
        // member function on the duration object
        cout << "\n" << "duration: " << duration.count() << "\n";
    }

}

namespace Window
{

}

namespace JSON 
{
    void getData(Parser::pointsConfig &points, Parser::windowConfig &window)
    {
        Json::Value jsonFile;
        Json::Reader reader;
        std::ifstream file("json/settings.json");
        reader.parse(file, jsonFile);
        // points
        points.range = jsonFile["range"].asInt();
        points.expression = jsonFile["expression"].asString();

        // colors
        window.colorAxes = jsonFile["color_axes"].asString();
        window.colorBackground = jsonFile["color_background"].asString();
        window.colorFunctionGraph = jsonFile["color_function_graph"].asString();

        // window properties
        window.height = jsonFile["height"].asInt();
        window.width = jsonFile["width"].asInt();
    }

}
