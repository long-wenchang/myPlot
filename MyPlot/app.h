#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QDockWidget>
#include <qcustomplot.h>
#include <mDockWidget.h>

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
    void dockWidget_Init();
    void dockWidget_data_Init();
    void dockWidget_setting_Init();
    void dockWidget_state_Init();

private slots:
    void action_state();

    void titleDoubleClick_Slot(QMouseEvent *event);
    void axisLabelDoubleClick_Slot(QCPAxis *axis, QCPAxis::SelectablePart part);
    void legendDoubleClick_Slot(QCPLegend *legend, QCPAbstractLegendItem *item);

    void selectionChanged_Slot();

    void mousePress_Slot();
    void mouseWheel_Slot();
    void addRandomGraph_Slot();
    void removeSelectedGraph_Slot();
    void removeAllGraphs_Slot();
    void contextMenuRequest_Slot(QPoint pos);
    void moveLenged_Slot();
    void graphClicked_Slot(QCPAbstractPlottable *plotTable, int dataIndex);

private:
    Ui::App *ui;

    QCustomPlot *customPlot;
    //mDockWidget *dockWidget_data, *dockWidget_setting, *dockWidget_status;
    QDockWidget *dockWidget_data, *dockWidget_setting, *dockWidget_status;
};


#endif // APP_H
