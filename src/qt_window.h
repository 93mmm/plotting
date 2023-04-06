#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <fstream>
#include <nlohmann/json.hpp>

#include "../include/exprtk.hpp"
#include "sfml_window.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using std::string;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        void SetLanguage();

    private slots:
        // set language
        void SetRussianLang();
        void SetEnglishLang();
        void SetText();
        void ChangeText();
        // set language end

        // actions triggers
        void on_actionOpen_triggered();
        void on_actionSave_As_triggered();
        void on_actionSave_triggered();
        void on_actionNew_File_triggered();
        void on_actionPlot_Graph_triggered();
        void on_actionRussianLanguageSelect_triggered();
        void on_actionEnglishLanguageSelect_triggered();
        // actions triggers end

    private:
        string fileNotSaved, fileNotFound,
               howToUseNotepad, openFile, 
               saveNewFile, fileSaved;

        QString menuFile, popupSave, popupSaveAs, 
                popupNewFile, popupOpen,
                menuFunction, popupPlotGraph,
                menuLanguage, popupRus, popupEng;

        bool uiSettedUp = false;
        Ui::MainWindow *ui;
        QString currentPath;
};
#endif // MAINWINDOW_H
