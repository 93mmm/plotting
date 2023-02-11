#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "exprtk.hpp"
#include <fstream>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetLanguage();

private slots:
    void SetRussianLang();

    void SetEnglishLang();

    void on_actionOpen_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();
    
    void on_actionNew_File_triggered();

    void on_actionPlot_Graph_triggered();

    void on_actionRussianLanguageSelect_triggered();
    
    void on_actionEnglishLanguageSelect_triggered();
    
    void SetText();

    void ChangeText();

private:
    const char *fileNotSaved, *fileNotFound,
                *howToUseNotepad, *openFile, 
                *saveNewFile, *fileSaved;

    QString menuFile, popupSave, popupSaveAs, popupNewFile, popupOpen,
            menuFunction, popupPlotGraph,
            menuLanguage, popupRus, popupEng;

    bool uiSettedUp = false;
    Ui::MainWindow *ui;
    QString currentPath;
};
#endif // MAINWINDOW_H
