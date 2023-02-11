#pragma once

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <thread>
#include "qt_window.h"

#include "exprtk.hpp"

using std::string;
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
            double scaleCoef = 1;
        };

        int movedX = 0, movedY = 0;
        bool tap = false;

        PointsConfig pointsCFG;
        WindowConfig windowCFG;
        sf::RenderWindow window;
        sf::VertexArray axes{sf::Lines, 4};
        sf::VertexArray gridX{sf::Lines, 100};
        sf::VertexArray gridY{sf::Lines, 100};
        sf::VertexArray miniGridX{sf::Lines, 100};
        sf::VertexArray miniGridY{sf::Lines, 100};
        sf::Font font;
        sf::Text positionOfCursor;
        
        int prevPosX, prevPosY, currentX, currentY;

        double GetVisualCoordinate(double coordinate);
        double GetPlaneCoordinate(double coordinate);

        void InitSfFields();

        // window updating
        void CheckEvent();
        void DrawGrid();
        void DrawPoints();
        void DrawText();
        void GetDataFromJSON();
        void ResizeGrid();

    public:
        void SetPointsConfig(string exp);
        void RunWindow();
};