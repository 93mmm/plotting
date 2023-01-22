#include "header.hpp"
#include "mainwindow.h"
#include "./ui_mainwindow.h"

using std::string;
using std::cout;;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    Parser::pointsConfig points;
    Window::windowConfig window;
    Parser::setPointsConfig(points);
    Window::setWindowConfig(window);

    string expression =  ui->plainTextEdit->textCursor().selectedText().toStdString();
    points.range = 5;
    points.expression = expression;
    Parser::getPoints<double>(points);
    Window::createWindow(points, window);
}
