#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

#include "exprtk.hpp"

using std::string;
using std::cout;
using json = nlohmann::json;

namespace Parser
{
    struct pointsConfig
    {
        int range = 0;
        string expression = "";
        double step = 0;
        double array_x[5000];
        double array_y[5000];
    };

    void setPointsConfig(pointsConfig &points)
    {
        std::ifstream jsonFile("json/settings.json");
        json j = json::parse(jsonFile);

        points.step = stod(j["step"].dump());
        points.range = stoi(j["range"].dump());
        points.expression = j["expression"].dump();
    }

    template <typename T>
    void getPoints(pointsConfig &points)
    {
        typedef exprtk::symbol_table<T> symbol_table_t;
        typedef exprtk::expression<T>   expression_t;
        typedef exprtk::parser<T>       parser_t;

        const string expression_string = points.expression;
        cout << expression_string << "hbfvhjsvjhsdvbjsbvsd\n";

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
            int range = points.range;
            double step = points.step;
            for (x = T(-range); x <= T(+range); i++, x += T(step))
            {
                const T y = expression.value();
                points.array_x[i] = x;
                points.array_y[i] = y;
            }
        }
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
    void createWindow(Parser::pointsConfig points, Window::windowConfig window)
    {
        int range;

        cout << __cplusplus << "\n"
            << "expression: " << points.expression << "\n"
            << "range: " << points.range << "\n"
            << "axes color: " << window.colorAxes << "\n"
            << "bg color: " << window.colorBackground << "\n"
            << "line graph: " << window.colorFunctionGraph << "\n"
            << "height: " << window.height << "\n"
            << "width: " << window.width << "\npoints:\n";

        range = points.range * (1 / points.step) * 2;
        for (int i = 0; i <= range; i++)
        {
            cout << points.array_x[i] << "\t" << points.array_y[i] << "\n";
        }    
    }
    void setWindowConfig(Window::windowConfig &window)
    {
        std::ifstream jsonFile("json/settings.json");
        json j = json::parse(jsonFile);

        window.width = stoi(j["width"].dump());
        window.height = stoi(j["height"].dump());
        window.colorAxes = j["colorAxes"].dump();
        window.colorBackground = j["colorBackground"].dump();
        window.colorFunctionGraph = j["colorFunctionGraph"].dump();
    }
}

