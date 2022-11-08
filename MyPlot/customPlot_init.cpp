#include "app.h"
#include "ui_app.h"

void App::customPlot_Init()
{
    customPlot = ui->customPlot;

    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectItems | QCP::iSelectOther |
                                QCP::iSelectPlottables | QCP::iSelectPlottablesBeyondAxisRect);
    plotXAxis  = customPlot->xAxis;
    plotYAxis  = customPlot->yAxis;
    plotXAxis2 = customPlot->xAxis2;
    plotYAxis2 = customPlot->yAxis2;
    plotXAxis->setRange(-10, 10);
    plotYAxis->setRange(-5, 5);
    QFont plotFont = QFont("Times New Roman", 22, QFont::Black);
    plotXAxis->setTickLabelFont(plotFont);
    plotYAxis->setTickLabelFont(plotFont);
    plotXAxis->setSelectedTickLabelFont(plotFont);
    plotYAxis->setSelectedTickLabelFont(plotFont);
    customPlot->axisRect()->setupFullAxesBox();

    customPlot->plotLayout()->insertRow(0);
    plotTitle = new QCPTextElement(customPlot, "Title", plotFont);
    customPlot->plotLayout()->addElement(0, 0, plotTitle);

    plotXAxis->setLabel("X");
    plotYAxis->setLabel("Y");
    plotXAxis->setLabelFont(plotFont);
    plotYAxis->setLabelFont(plotFont);
    plotXAxis->setSelectedLabelFont(plotFont);
    plotYAxis->setSelectedLabelFont(plotFont);

    plotXAxis->setTickLabelPadding(10);
    plotXAxis->setLabelPadding(5);
    plotXAxis->setPadding(20);
    plotYAxis->setTickLabelPadding(10);
    plotYAxis->setLabelPadding(5);
    plotYAxis->setPadding(20);
    plotXAxis2->setPadding(20);
    plotYAxis2->setPadding(20);

//    for (int index=0; index<customPlot->graphCount(); ++index)
//    {
//        plotGraph = customPlot->graph(index);
//    }
//    QCPPlottableLegendItem *item = plotLegend->itemWithPlottable(plotGraph);

    plotLegend = customPlot->legend;

    if (customPlot->graphCount() != 0)
        plotLegend->setVisible(true);
    else
        plotLegend->setVisible(false);

    plotLegend->setFont(plotFont);
    plotLegend->setSelectedFont(plotFont);

    // 图例框不能选择，只能选择图例物品
    plotLegend->setSelectableParts(QCPLegend::spItems);
    // customPlot->legend->setSelectableParts(QCPLegend::spLegendBox);

    customPlot->rescaleAxes();
    // 连接插槽，将一些轴的选择连接在一起(特别是相反的轴):
    connect(customPlot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged_Slot()));

    // 连接插槽，注意当选择一个轴时，只有该方向可以拖动和缩放:
    connect(customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress_Slot()));
    connect(customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel_Slot()));

    // 让底部和左侧轴将它们的范围转移到顶部和右侧轴:
    connect(plotXAxis, SIGNAL(rangeChanged(QCPRange)), plotXAxis2, SLOT(setRange(QCPRange)));
    connect(plotYAxis, SIGNAL(rangeChanged(QCPRange)), plotYAxis2, SLOT(setRange(QCPRange)));

    // 连接一些交互槽:
    // connect(customPlot, &QCustomPlot::axisDoubleClick, this, &App::axisLabelDoubleClick_Slot);
    connect(customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick_Slot(QCPAxis*,QCPAxis::SelectablePart)));
    connect(customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick_Slot(QCPLegend*,QCPAbstractLegendItem*)));
    connect(plotTitle, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick_Slot(QMouseEvent*)));

    // 连接槽，点击图形时在状态栏显示消息:
    connect(customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked_Slot(QCPAbstractPlottable*,int)));

    // 设置策略和连接插槽的上下文菜单弹出:
    customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest_Slot(QPoint)));

    connect(customPlot, &QCustomPlot::beforeReplot, this, &App::updateLegend_Slot);
}

void App::updateLegend_Slot()
{
    if (customPlot->graphCount() != 0)
        plotLegend->setVisible(true);
    else
        plotLegend->setVisible(false);
}

void App::titleDoubleClick_Slot(QMouseEvent *event)
{
    Q_UNUSED(event)
    if (QCPTextElement *title = qobject_cast<QCPTextElement*>(sender()))
    {
        // 通过双击它来设置情节标题
        bool ok;
        QString newTitle = QInputDialog::getText(this, "QCustomPlot dialog", "New plot title:", QLineEdit::Normal, title->text(), &ok);
        if (ok)
        {
            title->setText(newTitle);
            customPlot->replot();
        }
    }
}

void App::axisLabelDoubleClick_Slot(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // 通过双击设置一个轴标签
    if (part == QCPAxis::spAxisLabel) // 只在实际的轴标签被点击时做出反应，而不是打勾标签或轴骨干
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "QCustomPlot example", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok)
        {
            axis->setLabel(newLabel);
            customPlot->replot();
        }
    }
}

void App::legendDoubleClick_Slot(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    Q_UNUSED(legend)

    // 只在项目被点击时做出反应(用户可以点击图例的边框填充，如果没有项目，则项目为0)
    if (item)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        bool ok;
        QString newName = QInputDialog::getText(this, "QCustomPlot example", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
        if (ok)
        {
            plItem->plottable()->setName(newName);
            customPlot->replot();
        }
    }
}

void App::selectionChanged_Slot()
{
    /*
     * 通常，轴基线，轴勾标签和轴标签是可单独选择的，
     * 但我们想用户只能作为一个整体来选择坐标轴，
     * 所以我们把选中的状态系在勾标上轴和基线在一起。
     * 然而，轴标签应该是可单独选择的。
     *
     * 左右轴的选择状态应同步上下轴。
     *
     * 此外，我们希望将图的选择与各自的选择状态同步属于该图的图例项。
     * 因此，用户可以通过单击图形本身来选择图形
    */

    // 使上下轴同步选择，将轴和勾标签处理为一个可选择对象:
    if (plotXAxis->selectedParts().testFlag(QCPAxis::spAxis) || plotXAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        plotXAxis2->selectedParts().testFlag(QCPAxis::spAxis) || plotXAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        plotXAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        plotXAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // 使左右轴同步选择，将轴和勾标签处理为一个可选择对象:
    if (plotYAxis->selectedParts().testFlag(QCPAxis::spAxis) || plotYAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
        plotYAxis2->selectedParts().testFlag(QCPAxis::spAxis) || plotYAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        plotYAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        plotYAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }

    // 同步图形的选择与对应图例项的选择:
    for (int i=0; i<customPlot->graphCount(); ++i)
    {
        plotGraph = customPlot->graph(i);
        plotItem = plotLegend->itemWithPlottable(plotGraph);
        if (plotItem->selected() || plotGraph->selected())
        {
            plotItem->setSelected(true);
            plotGraph->setSelection(QCPDataSelection(plotGraph->data()->dataRange()));
        }
    }
}

void App::mousePress_Slot()
{
    // 如果选择了一个轴，则只允许拖动该轴的方向
    // 如果没有选择轴，两个方向都可以拖动

    if (plotXAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeDrag(plotXAxis->orientation());
    else if (customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeDrag(plotYAxis->orientation());
    else
        customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void App::mouseWheel_Slot()
{
    // 如果一个轴被选中，只允许该轴的方向被放大
    // 如果没有选择轴，两个方向都可以放大
    if (plotXAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeZoom(plotXAxis->orientation());
    else if (plotYAxis->selectedParts().testFlag(QCPAxis::spAxis))
        customPlot->axisRect()->setRangeZoom(plotYAxis->orientation());
    else
        customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void App::addRandomGraph_Slot()
{
    // 增加一条曲线
    int n = 50;
    double xScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double yScale = (rand()/(double)RAND_MAX + 0.5)*2;
    double xOffset = (rand()/(double)RAND_MAX - 0.5)*4;
    double yOffset = (rand()/(double)RAND_MAX - 0.5)*10;
    double r1 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r2 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r3 = (rand()/(double)RAND_MAX - 0.5)*2;
    double r4 = (rand()/(double)RAND_MAX - 0.5)*2;
    QVector<double> x(n), y(n);
    for (int i = 0; i<n; i++)
    {
        x[i] = (i/(double)n-0.5)*10.0*xScale + xOffset;
        y[i] = (qSin(x[i]*r1*5)*qSin(qCos(x[i]*r2)*r4*3)+r3*qCos(qSin(x[i])*r4*2))*yScale + yOffset;
    }

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
//    plotGraphIndexList.append(plotGraphIndex);
//    plotGraphIndex++;
}

void App::removeSelectedGraph_Slot()
{
    // 移除选中的曲线
    if (customPlot->selectedGraphs().size() > 0)
    {
        qDebug() << customPlot->selectedGraphs();
        customPlot->removeGraph(customPlot->selectedGraphs().first());
        customPlot->replot();
//        if (customPlot->graphCount() == 0)
//        {
//            plotGraphIndex = 0;
//            plotGraphIndexList.clear();
//        }
    }
}


void App::removeAllGraphs_Slot()
{
    // 移除全部曲线
    customPlot->clearGraphs();
    customPlot->replot();
//    plotGraphIndex = 0;
//    plotGraphIndexList.clear();
}

void App::contextMenuRequest_Slot(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);



    if (plotLegend->selectTest(pos, false) >= 0) // 请求图例上的上下文菜单
    {
        menu->addAction("Move to top left", this, SLOT(moveLegend_Slot()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend_Slot()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend_Slot()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend_Slot()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend_Slot()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    }
    else  // 请求图形的通用上下文菜单
    {
        menu->addAction("Add random graph", this, SLOT(addRandomGraph_Slot()));
        if (customPlot->selectedGraphs().size() > 0)
            menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph_Slot()));
        if (customPlot->graphCount() > 0)
            menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs_Slot()));
    }

    menu->popup(customPlot->mapToGlobal(pos));
}

void App::moveLegend_Slot()
{
    // 确保这个槽是由上下文菜单操作调用的，这样它就携带了我们需要的数据
    if (QAction* contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            customPlot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            customPlot->replot();
        }
    }
}

void App::graphClicked_Slot(QCPAbstractPlottable *plotTable, int dataIndex)
{
    // 因为我们知道我们在图中只有qcpgraph，我们可以立即访问interface1D()
    // 通常最好先检查interface1D()是否返回非零，然后才使用它。
    double dataValue = plotTable->interface1D()->dataMainValue(dataIndex);
    QString message = QString("Clicked on graph '%1' at data point #%2 with value %3.").arg(plotTable->name()).arg(dataIndex).arg(dataValue);
    ui->statusbar->showMessage(message, 5000);
}
