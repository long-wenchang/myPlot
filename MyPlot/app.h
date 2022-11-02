#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QDockWidget>

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
    void tableWidget_Init();

private slots:
    // dockWidget
    void action_window_Slot();

    // customPlot
    void updateLegend_Slot();
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
    void moveLegend_Slot();
    void graphClicked_Slot(QCPAbstractPlottable *plotTable, int dataIndex);

    // tableWidget
    void tableWidget_contextMenu_Slot(QPoint pos);
    void tableWidgetH_contextMenu_Slot(QPoint pos);
    void tableWidgetV_contextMenu_Slot(QPoint pos);

    void tableW_removeRow();
    void tableW_removeColumn();
    void tableW_insertRow();
    void tableW_insertColumn();
    void tableW_resetHeader();

private:
    Ui::App *ui;

    QCustomPlot *customPlot;

    QDockWidget *dock_data, *dock_setting;
};
#endif // APP_H
