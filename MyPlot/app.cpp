#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);

    QFile file(":/app.qss");
    file.open(QFile::ReadOnly);
    QTextStream fileText(&file);
    QString qss = fileText.readAll();
    // qDebug() << qss;
    this->setStyleSheet(qss);
    file.close();

    this->customPlot_Init();
    this->dockWidget_Init();
    this->tableWidget_Init();
}

App::~App()
{
    delete ui;
}

