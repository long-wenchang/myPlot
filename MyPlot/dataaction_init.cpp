#include "app.h"
#include "ui_app.h"

void App::dataAction_Init()
{
    connect(ui->action_open, &QAction::triggered, this, &App::action_openFile_Slot);
    connect(ui->action_close, &QAction::triggered, this, &App::action_closeFile_Slot);
    connect(ui->action_save, &QAction::triggered, this, &App::action_saveFile_Slot);
    connect(ui->action_export, &QAction::triggered, this, &App::action_exportFile_Slot);
}

void App::action_openFile_Slot()
{
    QFileDialog dlg(this);
    QString file_name = dlg.getOpenFileName(this, tr("Open"), "./", tr("Text File(*.txt)"));

    if (file_name.isEmpty())
    {
        return;
    }
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        QString strContent = stream.readAll();
        ui->tableWidget_data->clearContents();
        this->tableW_insertData(strContent, 0, 0);
    }
}

void App::action_closeFile_Slot()
{
    ui->tableWidget_data->clearContents();
}

void App::action_saveFile_Slot()
{
    QFileDialog dlg(this);
    QString file_name = dlg.getSaveFileName(this, tr("Save"), "./", tr("Text File(*.txt)"));

    if (file_name.isNull())
    {
        QMessageBox::warning(this, tr("Error"), tr("File path error!"));
        return;
    }
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        int rowCount = ui->tableWidget_data->rowCount();
        int columnCount = ui->tableWidget_data->columnCount();
        for (int i=0; i<rowCount; i++)
        {
            QString rowStr = NULL;
            for (int j=0; j<columnCount; j++)
            {
                QTableWidgetItem* item =  ui->tableWidget_data->item(i, j);
                if (item != nullptr)
                {
                    rowStr += item->text() + "\t";
                }
                else if (item == nullptr)
                {
                    rowStr += + "\t";
                }
                else
                    break;
            }
            rowStr += "\n";
            out << rowStr;
        }
        file.close();
        QMessageBox::information(this, tr("Finish"), tr("Successfully save the file!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Failed to save the file!"));
    }
}

void App::action_exportFile_Slot()
{
    QFileDialog dlg(this);
    QString file_name = dlg.getSaveFileName(this, tr("Save"), "./", tr("PNG(*.png)"));

    if (file_name.isNull())
    {
        QMessageBox::warning(this, tr("Error"), tr("File path error!"));
        return;
    }
    if (customPlot->savePng(file_name, customPlot->width(), customPlot->height()))
    {
        QMessageBox::information(this, tr("Finish"), tr("Image exported successfully!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Error"), tr("Image export failed!"));
    }
}
