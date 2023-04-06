#include "qt_window.h"

using json = nlohmann::json;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    SetLanguage();
    ui->setupUi(this);
    uiSettedUp = true;
    ChangeText();
    currentPath = QString::fromStdString(howToUseNotepad);
    SetText();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetLanguage()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();
    string language = parsedFile["language"];
    if (language == "rus")
        SetRussianLang();
    else if (language == "eng")
        SetEnglishLang();
    if (uiSettedUp)
        ChangeText();
}

void MainWindow::SetRussianLang()
{
    fileNotSaved = "Файл не сохранён!";
    fileNotFound = "Файл не найден!";
    howToUseNotepad = "text_files/how_to_use_notepad_rus.txt";
    openFile = "Открыть файл";
    saveNewFile = "Сохранить новый файл";
    fileSaved = "Файл сохранён!";
    
    menuFile = QString::fromStdString("Файл");
    popupSave = QString::fromStdString("Сохранить");
    popupSaveAs = QString::fromStdString("Сохранить Как");
    popupNewFile = QString::fromStdString("Новый Файл");
    popupOpen = QString::fromStdString("Открыть");
    menuFunction = QString::fromStdString("Функция");
    popupPlotGraph = QString::fromStdString("Построить График");
    menuLanguage = QString::fromStdString("Язык");
    popupRus = QString::fromStdString("Русский");
    popupEng = QString::fromStdString("Английский");

    const char *anotherPath = "text_files/how_to_use_notepad_eng.txt";
    if (currentPath.toStdString() == anotherPath)
        currentPath = QString::fromStdString(howToUseNotepad);
    SetText();
}

void MainWindow::SetEnglishLang()
{
    fileNotSaved = "File not saved!";
    fileNotFound = "File not found!";
    howToUseNotepad = "text_files/how_to_use_notepad_eng.txt";
    openFile = "Open file";
    saveNewFile = "Save new file";
    fileSaved = "File saved!";

    menuFile = QString::fromStdString("File");
    popupSave = QString::fromStdString("Save");
    popupSaveAs = QString::fromStdString("Save As");
    popupNewFile = QString::fromStdString("New File");
    popupOpen = QString::fromStdString("Open");
    menuFunction = QString::fromStdString("Function");
    popupPlotGraph = QString::fromStdString("Plot Graph");
    menuLanguage = QString::fromStdString("Language");
    popupRus = QString::fromStdString("Russian");
    popupEng = QString::fromStdString("English");

    const char *anotherPath = "text_files/how_to_use_notepad_rus.txt";
    if (currentPath.toStdString() == anotherPath)
        currentPath = QString::fromStdString(howToUseNotepad);
    SetText();
}

void MainWindow::on_actionOpen_triggered()
{
    currentPath = QFileDialog::getOpenFileName(this, QString::fromStdString(openFile));
    SetText();
}

void MainWindow::on_actionSave_As_triggered()
{
    currentPath = QFileDialog::getSaveFileName(this, QString::fromStdString(saveNewFile));
    if (currentPath.toStdString() != "")
        on_actionSave_triggered();
    else
        statusBar()->showMessage(QString::fromStdString(fileNotSaved), 5000);
}

void MainWindow::on_actionSave_triggered()
{
    if (currentPath == QString::fromStdString(""))
        on_actionSave_As_triggered();
    else
    {
        std::ofstream file;
        file.open(currentPath.toStdString());
        file << ui->plainTextEdit->toPlainText().toStdString();
        file.close();
        statusBar()->showMessage(QString::fromStdString(fileSaved), 5000);
    }
}

void MainWindow::on_actionNew_File_triggered()
{
    currentPath = QString::fromStdString("");
    ui->plainTextEdit->setPlainText(QString::fromStdString(""));
}

void MainWindow::on_actionPlot_Graph_triggered()
{
    string function = ui->plainTextEdit->textCursor().selectedText().toStdString();
    SFMLWindow sfml_win = SFMLWindow(function);
}

void MainWindow::SetText()
{
    std::ifstream ifs;
    ifs.open(currentPath.toStdString());
    if (!ifs.is_open())
        statusBar()->showMessage(QString::fromStdString(fileNotFound), 5000);
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

void MainWindow::on_actionRussianLanguageSelect_triggered()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();

    parsedFile["language"] = "rus";

    std::ofstream file("json/settings.json");
    file << parsedFile.dump(4);
    file.close();

    SetLanguage();
}
    
void MainWindow::on_actionEnglishLanguageSelect_triggered()
{
    std::ifstream jsonFile("json/settings.json");
    json parsedFile = json::parse(jsonFile);
    jsonFile.close();

    parsedFile["language"] = "eng";

    std::ofstream file("json/settings.json");
    file << parsedFile.dump(4);
    file.close();

    SetLanguage();
}

void MainWindow::ChangeText()
{
    ui->menufile->setTitle(menuFile);
    ui->menufile->setTitle(menuFile);
    ui->actionSave->setText(popupSave);
    ui->actionSave_As->setText(popupSaveAs);
    ui->actionNew_File->setText(popupNewFile);
    ui->actionOpen->setText(popupOpen);
    ui->menufunction->setTitle(menuFunction);
    ui->actionPlot_Graph->setText(popupPlotGraph);
    ui->menulanguage->setTitle(menuLanguage);
    ui->actionRussianLanguageSelect->setText(popupRus);
    ui->actionEnglishLanguageSelect->setText(popupEng);
}