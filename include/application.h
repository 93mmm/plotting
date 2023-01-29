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

namespace Window
{
    struct PointsConfig
    {
        string expression = "";
        int range = 5;
        double step = 0.01;
        double arrayX[5000];
        double arrayY[5000];
    } pointsCFG;

    struct WindowConfig
    {
        int colorAxes[3] {0, 0, 0};
        int colorBackground[3] {255, 255, 255};
        int colorFunctionGraph[3] {0, 255, 0};
        int width = 0;
        int height = 0;
    } windowCFG;



    template <typename T>
    void SetPointsConfig();

    void MovePoints(double moveX, double moveY);
    void SetWindowConfig();

    void CreateWindow();
    void RenderWindow();
}