#include "sfml_window.h"
#include "qt_window.h"
#include "./ui_mainwindow.h"
#include <math.h>
#include <thread>
#include <fstream>

using std::string;
using std::cout;;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setText("how_to_use_notepad.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionOpen_triggered()
{

}


void MainWindow::on_actionSave_As_triggered()
{

}

void MainWindow::on_actionSave_triggered()
{

}

void MainWindow::on_actionPlot_Graph_triggered()
{
    Win sfml_win;
    sfml_win.SetPointsConfig(ui->plainTextEdit->textCursor().selectedText().toStdString());
    sfml_win.RunWindow();
}

void MainWindow::setText(std::string filename)
{
    std::ifstream ifs;
    ifs.open(filename);
    if (!ifs.is_open())
        cout << "file \"how_to_use_notepad.txt\" deleted\n";
    else
    {
        string fileString;
        QString line;
        QStringList text;
        while (getline(ifs, fileString))
        {
            line = QString::fromStdString(fileString);
            text.append(line);
        }
        ui->plainTextEdit->setPlainText(text.join("\n"));
        ifs.close();
    }
}


double Win::GetVisualCoordinate(double coordinate)
{
    return coordinate * windowCFG.scaleCoef + windowCFG.side / 2;
}

double Win::GetPlaneCoordinate(double coordinate)
{
    return (coordinate - windowCFG.side / 2) / windowCFG.scaleCoef;
}

void Win::InitSfFields()
{
    int side = windowCFG.side;
    axes[0].position = sf::Vector2f(side / 2, 0);
    axes[1].position = sf::Vector2f(side / 2, side);
    axes[2].position = sf::Vector2f(0, side / 2);
    axes[3].position = sf::Vector2f(side, side / 2);
    
    for (int i = -50; i < 50; i += 2)
    {
        gridX[i + 50].color = sf::Color(100, 100, 100);
        gridY[i + 50].color = sf::Color(100, 100, 100);

        gridX[i + 51].color = sf::Color(100, 100, 100);
        gridY[i + 51].color = sf::Color(100, 100, 100);
    }

    font.loadFromFile("reg_consolas.ttf");
    positionOfCursor.setFont(font);
    positionOfCursor.setCharacterSize(10);
    positionOfCursor.setFillColor(sf::Color::White);
    positionOfCursor.setPosition(sf::Vector2f(windowCFG.side - 200, 1));

    prevPosX = sf::Mouse::getPosition(window).x;
    prevPosY = sf::Mouse::getPosition(window).y;
}

void Win::ResizeGrid()
{
    int side = windowCFG.side;
    axes[0].position = sf::Vector2f(side / 2 + movedX, 0);
    axes[1].position = sf::Vector2f(side / 2 + movedX, side);
    axes[2].position = sf::Vector2f(0, side / 2 + movedY);
    axes[3].position = sf::Vector2f(side, side / 2 + movedY);
    int i = -50;
    int increment = -25;
    for (; i < 50; i += 2)
    {
        double pos = GetVisualCoordinate(increment);
        gridX[i + 50].position = sf::Vector2f(pos + movedX, 0);
        gridY[i + 50].position = sf::Vector2f(0, pos + movedY);
        gridX[i + 51].position = sf::Vector2f(pos + movedX, windowCFG.side);
        gridY[i + 51].position = sf::Vector2f(windowCFG.side, pos + movedY);
        increment++;
    }
}

void Win::CheckEvent()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        if (event.type == sf::Event::MouseWheelMoved)
        {
            double *scaleCoef = &windowCFG.scaleCoef;
            bool flag = false;

            if (*scaleCoef < 1000 and *scaleCoef > 5.5)
                flag = true;
            else if (*scaleCoef <= 5.5 and event.mouseWheel.delta == 1)
                flag = true;
            else if (*scaleCoef >= 1000 and event.mouseWheel.delta == -1)
                flag = true;
            if (flag)
                *scaleCoef *= 1 + 0.05 * event.mouseWheel.delta;
        }
    }
    currentX = sf::Mouse::getPosition(window).x;
    currentY = sf::Mouse::getPosition(window).y;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        movedX += currentX - prevPosX;
        movedY += currentY - prevPosY;
        prevPosX = currentX;
        prevPosY = currentY;
    }
    prevPosX = currentX;
    prevPosY = currentY;
}

void Win::DrawGrid()
{
    ResizeGrid();
    if (windowCFG.scaleCoef < 10)
    {
        //window.draw(gridX); 
    }
    window.draw(gridX);
    window.draw(gridY);
    window.draw(axes);
    window.draw(positionOfCursor);
}

void Win::DrawPoints()
{
    int range = pointsCFG.range * (1 / pointsCFG.step) * 2;
    for (int i = 0; i < range; i++)
    {
        double x = GetVisualCoordinate(pointsCFG.arrayX[i]) + movedX;
        double y = GetVisualCoordinate(-pointsCFG.arrayY[i]) + movedY;

        sf::Vertex point(sf::Vector2f(x, y));
        point.color = sf::Color(windowCFG.colorFunctionGraph[0], windowCFG.colorFunctionGraph[1], windowCFG.colorFunctionGraph[2]);
        window.draw(&point, 1, sf::Points);
    }
}

void Win::GetDataFromJSON()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();

    windowCFG.side = stoi(parsedFile["window"]["side"].dump());
    windowCFG.scaleCoef = windowCFG.side / 20;

    windowCFG.colorAxes[0] = stoi(parsedFile["window"]["colorAxes"][0].dump());
    windowCFG.colorAxes[1] = stoi(parsedFile["window"]["colorAxes"][1].dump());
    windowCFG.colorAxes[2] = stoi(parsedFile["window"]["colorAxes"][2].dump());

    windowCFG.colorBackground[0] = stoi(parsedFile["window"]["colorBackground"][0].dump());
    windowCFG.colorBackground[1] = stoi(parsedFile["window"]["colorBackground"][1].dump());
    windowCFG.colorBackground[2] = stoi(parsedFile["window"]["colorBackground"][2].dump());

    windowCFG.colorFunctionGraph[0] = stoi(parsedFile["window"]["colorFunctionGraph"][0].dump());
    windowCFG.colorFunctionGraph[1] = stoi(parsedFile["window"]["colorFunctionGraph"][1].dump());
    windowCFG.colorFunctionGraph[2] = stoi(parsedFile["window"]["colorFunctionGraph"][2].dump());
}

void Win::SetPointsConfig(string exp)
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    pointsCFG.range = stoi(parsedFile["points"]["range"].dump());
    pointsCFG.step = 0.001;
    pointsCFG.expression = exp;
    jsonFile.close();

    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double>   expression_t;
    typedef exprtk::parser<double>       parser_t;

    double x;
    symbol_table_t symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();
    expression_t expression;
    expression.register_symbol_table(symbol_table);
    parser_t parser;
    parser.compile(pointsCFG.expression, expression);
    {
        int i = 0;
        int range = pointsCFG.range;
        double step = pointsCFG.step;
        for (x = -range; x <= +range; i++, x += step)
        {
            const double y = expression.value();
            pointsCFG.arrayX[i] = x;
            pointsCFG.arrayY[i] = y;
        }
    }
}

void Win::DrawText()
{
    string pos = "x: " + std::to_string(GetPlaneCoordinate(currentX - movedX)) + " y: " + std::to_string(-GetPlaneCoordinate(currentY - movedY));
    positionOfCursor.setString(pos);
    window.draw(positionOfCursor);
}

void Win::RunWindow()
{
    GetDataFromJSON();
    InitSfFields();
    window.create(sf::VideoMode(windowCFG.side, windowCFG.side), "");
    while (window.isOpen())
    {
        CheckEvent();
        // drawing
        window.clear();
        DrawGrid();
        DrawPoints();
        DrawText();
        window.display();
        QCoreApplication::processEvents();
    }
}