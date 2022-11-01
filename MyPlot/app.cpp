#include "app.h"
#include "ui_app.h"
#include "QMenu"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);

    QFile file(":/qss/app.qss");
    file.open(QFile::ReadOnly);
    QTextStream fileText(&file);
    QString ss = fileText.readAll();
    qDebug() << ss;
    this->setStyleSheet(ss);
    file.close();

    this->customPlot_Init();

    this->dockWidget_Init();
}

App::~App()
{
    delete ui;
}
