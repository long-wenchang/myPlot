#include "app.h"
#include "ui_app.h"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);

    this->dataAction_Init();
    this->customPlot_Init();
    this->dockWidget_Init();
    this->tableWidget_Init();

    connect(ui->pushButton_plot, &QPushButton::clicked, this, &App::plot_Slot);

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

void App::plot_Slot()
{
    // 根据选中区域进行绘图
    QList<QTableWidgetSelectionRange> sRangeList = ui->tableWidget_data->selectedRanges();
    QVector<double> x, y;
    for (const auto &p : qAsConst(sRangeList))
    {
        for (auto i=p.topRow(); i<=p.bottomRow(); i++)
        {
            QTableWidgetItem *itemx = ui->tableWidget_data->item(i, p.leftColumn());
            QTableWidgetItem *itemy = ui->tableWidget_data->item(i, p.rightColumn());
            if (itemx != nullptr && itemy != nullptr )
            {
                bool ok;
                double dx = itemx->text().toDouble(&ok);
                double dy = itemy->text().toDouble(&ok);
                x.append(dx);
                y.append(dy);
            }
        }
    }
    this->addGraph4data(x, y);
}

void App::addGraph4data(QVector<double> x, QVector<double> y)
{
    customPlot->addGraph();
    customPlot->graph()->setName(QString("New graph %1").arg(customPlot->graphCount() - 1));
    customPlot->graph()->setData(x, y);
    customPlot->graph()->setLineStyle((QCPGraph::LineStyle)(rand()%5 + 1));
    if (rand()%100 > 50)
    {
        customPlot->graph()->setScatterStyle(QCPScatterStyle((QCPScatterStyle::ScatterShape)(rand()%14+ 1)));
    }
    QPen graphPen;
    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10));
    graphPen.setWidthF(rand()/(double)RAND_MAX*2 + 1);
    customPlot->graph()->setPen(graphPen);
    customPlot->replot();
}

void App::dragEnterEvent(QDragEnterEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (!mimeData->hasUrls())
        return;

    const QList<QUrl> urls = mimeData->urls();
    QMimeType mimeType = QMimeDatabase().mimeTypeForUrl(urls.at(0));
    if (mimeType.inherits("text/plain"))
        event->acceptProposedAction();
    else
        qDebug() << mimeType.name();
}

void App::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    if (!mimeData->hasUrls())
        return;

    const QList<QUrl> urls = mimeData->urls();
    QString filePath = urls.at(0).toLocalFile();
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QTextStream stream(&file);
    QString strContent = stream.readAll();
    qDebug() << strContent;
    ui->tableWidget_data->clearContents();
    this->tableW_insertData(strContent, 0, 0);
}
