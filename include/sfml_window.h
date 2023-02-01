#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <thread>

#include "exprtk.hpp"

using std::string;
using std::cout;
using json = nlohmann::json;

class Win
{
    private:
        struct PointsConfig
        {
            string expression = "";
            int range = 5;
            double step = 0.001;
            double arrayX[50000];
            double arrayY[50000];
        };

        struct WindowConfig
        {
            int colorAxes[3] {0, 0, 0};
            int colorBackground[3] {255, 255, 255};
            int colorFunctionGraph[3] {0, 255, 0};
            int side = 0;
            int scaleCoef = 1;
        };

        PointsConfig pointsCFG;
        WindowConfig windowCFG;
        sf::RenderWindow window;
        sf::VertexArray axes{sf::Lines, 4};

        void InitVertexArrays();

        // window updating
        void CheckEvent();
        void DrawGrid();
        void DrawPoints();
        void GetDataFromJSON();

    public:
        void SetPointsConfig(string exp);
        void RunWindow();
};