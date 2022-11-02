#include "app.h"
#include "ui_app.h"

void App::tableWidget_Init()
{
    ui->tableWidget_data->setContextMenuPolicy(Qt::CustomContextMenu);      // 设置右击菜单
    // connect(ui->tableWidget_data, &QTableWidget::customContextMenuRequested, this, &App::tableWidget_contextMenu_Slot);
    connect(ui->tableWidget_data, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(tableWidget_contextMenu_Slot(QPoint)));

    ui->tableWidget_data->horizontalHeader()->setStyleSheet("background-color: rgb(200, 200, 200);");
    ui->tableWidget_data->verticalHeader()->setStyleSheet("background-color: rgb(200, 200, 200);");

    QHeaderView *hHeader = ui->tableWidget_data->horizontalHeader();
    hHeader->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(hHeader, &QHeaderView::customContextMenuRequested, this, &App::tableWidgetH_contextMenu_Slot);
    QHeaderView *vHeader = ui->tableWidget_data->verticalHeader();
    vHeader->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(vHeader, &QHeaderView::customContextMenuRequested, this, &App::tableWidgetV_contextMenu_Slot);
}

void App::tableWidget_contextMenu_Slot(QPoint pos)
{
    ui->tableWidget_data->clearSelection();
    QModelIndex index = ui->tableWidget_data->indexAt(pos);

    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction("删除当前行", this, SLOT(tableW_removeRow()))->setData(index.row());
    menu->addAction("删除当前列", this, SLOT(tableW_removeColumn()))->setData(index.column());
    menu->addAction("在上方插入行", this, SLOT(tableW_insertRow()))->setData(index.row());
    menu->addAction("在下方插入行", this, SLOT(tableW_insertRow()))->setData(index.row()+1);
    menu->addAction("在左侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column());
    menu->addAction("在右侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column()+1);


    menu->popup(ui->tableWidget_data->viewport()->mapToGlobal(pos));    //将菜单显示到鼠标所在位置
}

void App::tableWidgetH_contextMenu_Slot(QPoint pos)
{
    ui->tableWidget_data->clearSelection();
    QModelIndex index = ui->tableWidget_data->indexAt(pos);
    ui->tableWidget_data->selectColumn(index.column());

    QMenu *menu = new QMenu(this);
    menu->addAction("删除当前列", this, SLOT(tableW_removeColumn()))->setData(index.column());
    menu->addAction("在左侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column());
    menu->addAction("在右侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column()+1);

    pos.setX(pos.x() + 23);
    menu->popup(ui->tableWidget_data->mapToGlobal(pos));
}

void App::tableWidgetV_contextMenu_Slot(QPoint pos)
{
    ui->tableWidget_data->clearSelection();
    QModelIndex index = ui->tableWidget_data->indexAt(pos);
    ui->tableWidget_data->selectRow(index.row());

    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction("删除当前行", this, SLOT(tableW_removeRow()))->setData(index.row());
    menu->addAction("在上方插入行", this, SLOT(tableW_insertRow()))->setData(index.row());
    menu->addAction("在下方插入行", this, SLOT(tableW_insertRow()))->setData(index.row()+1);

    pos.setY(pos.y() + 25);
    menu->popup(ui->tableWidget_data->mapToGlobal(pos));
}

void App::tableW_removeRow()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->tableWidget_data->removeRow(dataInt);
        }

        this->tableW_resetHeader();
    }
}

void App::tableW_removeColumn()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->tableWidget_data->removeColumn(dataInt);
        }
        this->tableW_resetHeader();
    }
}

void App::tableW_insertRow()
{
    if (QAction *contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->tableWidget_data->insertRow(dataInt);
        }
        this->tableW_resetHeader();
    }
}

void App::tableW_insertColumn()
{
    if (QAction *contextAction = qobject_cast<QAction*>(sender()))
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->tableWidget_data->insertColumn(dataInt);
        }

        this->tableW_resetHeader();
    }
}

void App::tableW_resetHeader()
{
//    int row = ui->tableWidget_data->currentRow();
//    int column = ui->tableWidget_data->currentColumn();
//    qDebug() << row << column;
    int rowCount = ui->tableWidget_data->rowCount();
    int columnCount = ui->tableWidget_data->columnCount();
    QStringList rowCountList, columnCountList;
    QStringList letterList;
    for(int i=0; i<26; i++)
    {
        letterList.append(QString('A' + i));
    }
    for (int i=0; i<rowCount; i++)
    {
         rowCountList.append(letterList[i]);
    }
    for (int i=0; i<columnCount; i++)
    {
        columnCountList.append(QString::number(i+1));
    }
    ui->tableWidget_data->horizontalHeader()->reset();
    ui->tableWidget_data->verticalHeader()->reset();
    ui->tableWidget_data->setRowCount(rowCount);
    ui->tableWidget_data->setColumnCount(columnCount);
    ui->tableWidget_data->setHorizontalHeaderLabels(rowCountList);
    ui->tableWidget_data->setVerticalHeaderLabels(columnCountList);
}
