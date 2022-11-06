#include "app.h"
#include "ui_app.h"

void App::tabWidget_Init()
{
    QStringList fontSize;
    fontSize << "8" << "9" << "10" << "11" << "12" << "14" << "16" << "18" << "20"
             << "22" << "24" << "26" << "28" << "36" << "48" << "72";
    ui->comboBox_title_font_size->addItems(fontSize);
    ui->comboBox_leftAxis_min_title_font_size->addItems(fontSize);
    ui->comboBox_bottomAxis_min_title_font_size->addItems(fontSize);
    ui->comboBox_rightAxis_min_title_font_size->addItems(fontSize);
    ui->comboBox_topAxis_min_title_font_size->addItems(fontSize);
    ui->comboBox_legend_object_title_font_size->addItems(fontSize);

    ui->tabWidget_setting->setCurrentIndex(0);
    connect(ui->tabWidget_setting, SIGNAL(tabBarClicked(int)), this, SLOT(tabWidget_Slot(int)));
    connect(ui->pushButton_title_font_color_select, &QPushButton::clicked,
            this, [=](){
       QColor color = QColorDialog::getColor(Qt::white, this);
       if (!color.isValid())
           return ;
       else
       {
           ui->label_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
           plotTitle->setTextColor(color);
           customPlot->replot();
       }
    });
    connect(ui->fontComboBox_title, &QFontComboBox::currentFontChanged, this, [=]{
        QFont font = ui->fontComboBox_title->currentFont();
        // qDebug() << font;
        plotTitle->setFont(font);
        customPlot->replot();
    });
    connect(ui->comboBox_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotTitle->font();
        QStringList fontList = font.toString().split(",");
        qDebug() <<fontList[0] << fontSize;
        bool ok;
        font = QFont(fontList[0], fontSize.toInt(&ok), QFont::Black);
        plotTitle->setFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_title_confirm, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_title_content->toPlainText();
        plotTitle->setText(content);
        customPlot->replot();
    });
}

void App::tabWidget_Slot(int index)
{
    switch (index) {
    case 0:
    {
        this->tabW_plotTitle();
        break;
    }
    case 1:
    {
        this->tabW_plotAxis();
        break;
    }
    case 2:
    {
        this->tabW_plotGraph();
        break;
    }
    default:
        break;
    }
}
void App::tabW_plotTitle()
{
    QString title = plotTitle->text();
    QFont font = plotTitle->font();
    QColor color = plotTitle->textColor();
    QStringList fontList = font.toString().split(",");
    qDebug() << title;
    qDebug() << fontList;
    qDebug() << color.red() << color.green() << color.blue() << color.alpha();
    qDebug() << QString::number(color.red()) << QString::number(color.green())
                 << QString::number(color.blue()) << QString::number(color.alpha());
    QString colorText = "rgb(" + QString::number(color.red()) + ", " + QString::number(color.green())
             + ",  " + QString::number(color.blue()) + ")";
    ui->textEdit_title_content->setText(title);
    ui->fontComboBox_title->setCurrentFont(font);
    ui->comboBox_title_font_size->setCurrentText(fontList[1]);
    // ui->spinBox_title_font_size->setValue(fontList[1].toInt(&ok));
    ui->label_title_font_color_show->setText(colorText);
    // ui->label_title_font_color_show->setStyleSheet("background-color: " + colorText + ";");
}

void App::tabW_plotAxis()
{}

void App::tabW_plotGraph()
{}
