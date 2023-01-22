#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "exprtk.hpp"
#include <chrono>

using std::string;
using std::cout;
using json = nlohmann::json;
using namespace std::chrono;

namespace Parser
{
    struct pointsConfig
    {
        int range = 0;
        string expression = "";
        double array_x[5000];
        double array_y[5000];
    };

    template <typename T>
    void getPoints(pointsConfig &CFG)
    {
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T>   expression_t;
        typedef exprtk::parser<T>       parser_t;

        const string expression_string = CFG.expression.substr(1, CFG.expression.length() - 2);

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
    struct windowConfig
    {
        string colorAxes = "#000000";
        string colorBackground = "#ffffff";
        string colorFunctionGraph = "#00ff00";
        int width = 500;
        int height = 500;
    };
}

namespace JSON 
{
    void getData(Parser::pointsConfig &points, Window::windowConfig &window)
    {
        std::ifstream jsonFile("json/settings.json");
        json j = json::parse(jsonFile);


        points.range = stoi(j["range"].dump());
        points.expression = j["expression"].dump();

        window.width = stoi(j["width"].dump());
        window.height = stoi(j["height"].dump());
        window.colorAxes = j["colorAxes"].dump();
        window.colorBackground = j["colorBackground"].dump();
        window.colorFunctionGraph = j["colorFunctionGraph"].dump();

    }
    void setData(Parser::pointsConfig points, Window::windowConfig window)
    {
        json j =
        {
            { "colorAxes", window.colorAxes },
            { "colorBackground", window.colorBackground },
            { "colorFunctionGraph", window.colorFunctionGraph },
            { "width", window.width },
            { "height", window.height },
            { "expression", points.expression },
            { "range", points.range }
        };
        std::ofstream o("json/settings.json");
        o << std::setw(4) << j << std::endl;
    }
}
