#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);
//    this->setAcceptDrops(true);
    ui->tableWidget_data->setAcceptDrops(true);

    this->customPlot_Init();
    this->dockWidget_Init();
    this->tableWidget_Init();

    QFile file(":/app.qss");
    file.open(QFile::ReadOnly);
    QTextStream fileText(&file);
    QString qss = fileText.readAll();
    // qDebug() << qss;
    this->setStyleSheet(qss);
    file.close();
}

App::~App()
{
    delete ui;
}

void App::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uil-list"))
    {
        event->acceptProposedAction();
    }
}

void App::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (!mimeData->hasUrls())
        return;

    const QUrl url = mimeData->urls().first();
    QMimeType mimeType = QMimeDatabase().mimeTypeForUrl(url);
    if (mimeType.inherits("text/plain"))
        qDebug() << "文本文件";
    else
        qDebug() << mimeType.name();
}
