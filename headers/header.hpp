#pragma once

#include <vector>
#include <string>
#include <cstdio>
#include <json/value.h>
#include <json/json.h>

#include "exprtk.hpp"

using std::string;

namespace JSON 
{
    void getData(string &expression, string &background_color, string &color_axes, string &function_graph_color)
    {
        Json::Value jsonObj;
        Json::Reader reader;

        std::ifstream file("json/settings.json");
        reader.parse(file, jsonObj);
        file.close();

        expression = jsonObj["expression"].asString();
        
        color_axes = jsonObj["color_axes"].asString();
        background_color = jsonObj["background_color"].asString();
        function_graph_color = jsonObj["function_graph_color"].asString();
    }

}

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
    
    template <typename T>
    void getPoints(pointsConfig &CFG)
    {
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T>   expression_t;
        typedef exprtk::parser<T>       parser_t;

        const std::string expression_string = CFG.expression;
        std::cout << expression_string << 9498;

        T x;

        symbol_table_t symbol_table;
        symbol_table.add_variable("x", x);
        symbol_table.add_constants();

        expression_t expression;
        expression.register_symbol_table(symbol_table);

        parser_t parser;
        parser.compile(expression_string, expression);

        {
            int i = 0;
            for (x = T(+4); x <= T(+5); i++, x += T(0.01))
            {
                const T y = expression.value();
                CFG.array_x[i] = x;
                CFG.array_y[i] = y;
            }
        }
        
    }

}

namespace Plotting
{

}