#include "app.h"
#include "ui_app.h"

void App::tableWidget_Init()
{
//    QStringList rowCountList, columnCountList;
//    for(int i=0; i<26; i++)
//    {
//        rowCountList.append(QString('A' + i));
//    }
//    for (int i=0; i<100; i++)
//    {
//        rowCountList.append(QString::number(i));
//    }
//    ui->tableWidget_data->horizontalHeader()->reset();
//    ui->tableWidget_data->verticalHeader()->reset();
    ui->tableWidget_data->setColumnCount(26);
    ui->tableWidget_data->setRowCount(1000);
//    ui->tableWidget_data->setHorizontalHeaderLabels(rowCountList);
//    ui->tableWidget_data->setVerticalHeaderLabels(columnCountList);

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
    QModelIndex index = ui->tableWidget_data->indexAt(pos);

    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction("删除当前行", this, SLOT(tableW_removeRow()))->setData(index.row());
    menu->addAction("删除当前列", this, SLOT(tableW_removeColumn()))->setData(index.column());
    menu->addAction("在上方插入行", this, SLOT(tableW_insertRow()))->setData(index.row());
    menu->addAction("在下方插入行", this, SLOT(tableW_insertRow()))->setData(index.row()+1);
    menu->addAction("在左侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column());
    menu->addAction("在右侧插入列", this, SLOT(tableW_insertColumn()))->setData(index.column()+1);
    // menu->addAction("复制全部内容", this, SLOT(tableW_copy()))->isChecked();
    menu->addAction("复制选中内容", this, SLOT(tableW_copySelect()))->isChecked();
    menu->addAction("粘贴内容", this, SLOT(tableW_paste()))->isChecked();

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

        // this->tableW_resetHeader();
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
        // this->tableW_resetHeader();
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
        // this->tableW_resetHeader();
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
        // this->tableW_resetHeader();
    }
}

void App::tableW_resetHeader()
{
    int rowCount = ui->tableWidget_data->rowCount();
    int columnCount = ui->tableWidget_data->columnCount();
    QStringList rowCountList, columnCountList;
    QStringList letterList;
    for(int i=0; i<columnCount; i++)
    {
            letterList.append(QString('A' + i));
    }
    for (int i=0; i<rowCount; i++)
    {
         rowCountList.append(QString::number(i+1));
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

#if 0
bool App::tableW_copy()
{
    int rows = ui->tableWidget_data->rowCount();
    int column = ui->tableWidget_data->columnCount();
    QString str = "";
    for (int i=0; i<column; i++){
        //ui->TableWidget->horizontalHeaderItem(0)->text();//获取表头第1行第1列的内容
        str += ui->tableWidget_data->horizontalHeaderItem(i)->text();
        str += "\t";
    }
    str+="\n";
    for(int i=0; i<rows; i++) // 取出每个格子的内容
    {
        for(int j=0; j<column; j++)
        {
            if(ui->tableWidget_data->item(i,j) != NULL)
            {//一定要先判断非空，否则会报错
                str+=ui->tableWidget_data->item(i,j)->text();
                str+="\t";
            }
            else
            {
                str+=""; //空字符弄成空格
                str+="\t";
            }
        }
        str+="\n";
    }
    QClipboard *board = QApplication::clipboard();
    board->setText(str);
    QMessageBox::information(NULL, "信息", "复制成功！");
    return true;
}
#endif

void App::tableW_copySelect()
{
    QList<QTableWidgetSelectionRange> sRangeList = ui->tableWidget_data->selectedRanges();
    for(const auto &p : qAsConst(sRangeList))
    {
        QString str;
        for (auto i = p.topRow(); i <= p.bottomRow(); i++)
        {
            QString rowStr;
            for (auto j = p.leftColumn(); j <= p.rightColumn(); j++)
            {
                QTableWidgetItem* item =  ui->tableWidget_data->item(i, j);
                if(item != nullptr)
                {
                    if(j == p.leftColumn())
                        rowStr = item->text() + "\t";
                    else if (j == p.rightColumn())
                        rowStr = rowStr + item->text() + "\t\n";
                    else
                        rowStr = rowStr + item->text() + "\t";
                }
                else if (item == nullptr)
                {
                    if(j == p.leftColumn())
                        rowStr = "\t";
                    else if (j == p.rightColumn())
                        rowStr = rowStr + "\t\n";
                    else
                        rowStr = rowStr + "\t";
                }
                else
                    break;
            }
            str += rowStr;
        }
        QClipboard *board= QApplication::clipboard();
        board->setText(str);
    }
}

void App::tableW_paste()
{
    // 粘贴，根据选中的第一个单元格开始
    QList<QTableWidgetSelectionRange> sRangeList = ui->tableWidget_data->selectedRanges();

    int widgetRow_1 = ui->tableWidget_data->rowCount();
    int widgetColumn_1= ui->tableWidget_data->columnCount();
    int topRow_0=0, leftColumn_0=0;
    int pasteRow_1, pasteColumn_1;

    QClipboard *board = QApplication::clipboard();
    QString str = board->text();
    QList<QString> rowList = str.split("\n");
    pasteRow_1 = rowList.size();
    QList<QString> columnList = rowList[0].split("\t");
    pasteColumn_1 = columnList.size();

    for (const auto &p : qAsConst(sRangeList))
    {
        topRow_0 = p.topRow();
        leftColumn_0 = p.leftColumn();
    }
    int x_0 = topRow_0;

    if (pasteRow_1 > widgetRow_1-topRow_0)      // 如果复制的行数大于剩余的行数，去除掉多余的赋值内容
    {
        for (int i = pasteRow_1-1; i >= widgetRow_1-topRow_0; i--)
        {
            rowList.removeAt(i);
        }
    }

    for (int i=0; i<rowList.size(); i++)
    {
        if (!rowList.isEmpty())
        {
            QList<QString> columnList = rowList[i].split("\t");
            if (pasteColumn_1 > widgetColumn_1-leftColumn_0)
            {
                for (int j=pasteColumn_1-1; j >= widgetColumn_1-leftColumn_0; j--)
                {
                    columnList.removeAt(j);
                }
            }
            int y_0 = leftColumn_0;
            for (int j = 0; j < columnList.size(); j++)
            {
                QTableWidgetItem *item = ui->tableWidget_data->item(x_0, y_0);
                if (item == nullptr)
                {
                    ui->tableWidget_data->setItem(x_0, y_0, new QTableWidgetItem(columnList[j]));
                    // ui->tableWidget_data->item(x_0, y_0)->setForeground(QBrush(QColor(255,0,0)));
                }
                else if (item != nullptr)
                {
                    ui->tableWidget_data->item(x_0, y_0)->setText(columnList[j]);
                }
                y_0++;
            }
        }
        x_0++;
    }
}

































