#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class App; }
QT_END_NAMESPACE

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget *parent = nullptr);
    ~App();

protected:
    void customPlot_Init();

private slots:
    void titleDoubleClick_Slot(QMouseEvent *event);
    void axisLabelDoubleClick_Slot(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick_Slot(QCPLegend *legend, QCPAbstractItem *item);

    void selectionChanged_Slot();

    void mousePress_Slot();
    void mouseWheel_Slot();
    void addRandomGraph_Slot();
    void removeSlectedGraph_Slot();
    void removeAllGraph_Slot();
    void contextMenuRequest_Slot(QPoint pos);
    void moveLenged_Slot();
    void graphClicked_Slot(QCPAbstractPlottable *plotTable, int dataIndex);

private:
    Ui::App *ui;

    QCustomPlot *customPlot;
};
#endif // APP_H
