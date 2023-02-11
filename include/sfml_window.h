#pragma once

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "qt_window.h"
#include "exprtk.hpp"

class Win
{
    private:
    // structs
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
        PointsConfig pointsCFG;
        WindowConfig windowCFG;
    // structs end

    // sf objects
        sf::RenderWindow window;
        sf::VertexArray axes{sf::Lines, 4}, gridX{sf::Lines, 100},
                        gridY{sf::Lines, 100}, miniGridX{sf::Lines, 100},
                        miniGridY{sf::Lines, 100};
        sf::Font font;
        sf::Text positionOfCursor;
    // sf objects end

    // vars
        int movedX = 0, movedY = 0;
        bool tap = false;
        int prevPosX, prevPosY, currentX, currentY;

        double GetVisualCoordinate(double coordinate);
        double GetPlaneCoordinate(double coordinate);

        void InitSfFields();
    // vars end

    // render frame
        void CheckEvent();
        void DrawGrid();
        void DrawPoints();
        void DrawText();
        void GetDataFromJSON();
        void ResizeGrid();
    // render frame end

    public:
        void SetPointsConfig(string exp);
        void RunWindow();
};