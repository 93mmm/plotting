#pragma once

#include <iostream>
#include <string>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

#include "../include/exprtk.hpp"
#include "points.h"

using std::string;

class SFMLWindow
{
    public:
        SFMLWindow(string expr);
        ~SFMLWindow();
    private:
    // structs
        struct WindowConfig
        {
            int colorAxes[3] {0, 0, 0};
            int colorBackground[3] {255, 255, 255};
            int colorFunctionGraph[3] {0, 255, 0};
            int side = 0;
            double scaleCoef = 1;
        } windowCFG;
    // structs end

    // sf objects
        sf::Image icon;
        sf::Event event;
        sf::RenderWindow window;
        sf::VertexArray axes{sf::Lines, 4}, gridX{sf::Lines, 100},
                        gridY{sf::Lines, 100}, miniGridX{sf::Lines, 100},
                        miniGridY{sf::Lines, 100};
        sf::Font font;
        sf::Text positionOfCursor;
    // sf objects end

    // init vars
        Points points;

        int movedX = 0, movedY = 0;
        int prevPosX, prevPosY, currentX, currentY;

        double GetVisualCoordinate(double coordinate);
        double GetPlaneCoordinate(double coordinate);

        bool tap = false;
        
        void InitSfFields();
        void GetDataFromJSON();
    // init vars end

        void RunWindow();

    // render frame
        void CheckEvent();
        void DrawGrid();
        void DrawPoints();
        void DrawText();
        void ResizeGrid();
    // render frame end
};