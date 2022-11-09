#include "app.h"
#include "ui_app.h"
#define DSpinBoxMax     (10000)
#define DSpinBoxMin     (-10000)

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

    ui->doubleSpinBox_bottomAxis_max->setMaximum(DSpinBoxMax);
    ui->doubleSpinBox_bottomAxis_min->setMinimum(DSpinBoxMin);
    ui->doubleSpinBox_leftAxis_max->setMaximum(DSpinBoxMax);
    ui->doubleSpinBox_leftAxis_min->setMinimum(DSpinBoxMin);
    ui->doubleSpinBox_topAxis_max->setMaximum(DSpinBoxMax);
    ui->doubleSpinBox_topAxis_min->setMinimum(DSpinBoxMin);
    ui->doubleSpinBox_rightAxis_max->setMaximum(DSpinBoxMax);
    ui->doubleSpinBox_rightAxis_min->setMinimum(DSpinBoxMin);
    this->tabW_plotTitle();
    this->tabW_plotAxis(0);
    this->tabW_plotAxis(1);
    this->tabW_plotAxis(2);
    this->tabW_plotAxis(3);

    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssNone;
    shapes << QCPScatterStyle::ssDot;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    shapes << QCPScatterStyle::ssPixmap;
    shapes << QCPScatterStyle::ssCustom;
    QStringList scatterStyleList;
    scatterStyleList << "ssNone"
                     << "ssDot"
                     << "ssCross"
                     << "ssPlus"
                     << "ssCircle"
                     << "ssDisc"
                     << "ssSquare"
                     << "ssDiamond"
                     << "ssStar"
                     << "ssTriangle"
                     << "ssTriangleInverted"
                     << "ssCrossSquare"
                     << "ssPlusSquare"
                     << "ssCrossCircl"
                     << "ssPlusCircle"
                     << "ssPeace"
                     << "ssPixmap"
                     << "ssCustom";
    ui->comboBox_legend_sytle->addItems(scatterStyleList);
    this->tabW_plotGraph();

    // plot title
    ui->tabWidget_setting->setCurrentIndex(0);
    connect(ui->tabWidget_setting, SIGNAL(tabBarClicked(int)), this, SLOT(tabWidget_Slot(int)));
    connect(ui->pushButton_title_font_color_select, &QPushButton::clicked,this, [=](){
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
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotTitle->setFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_title_confirm, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_title_content->toPlainText();
        plotTitle->setText(content);
        customPlot->replot();
    });

    // plot axis left
    connect(ui->pushButton_leftAxis_range_confirm, &QPushButton::clicked, this, [=]{
        QCPRange range(ui->doubleSpinBox_leftAxis_min->value(), ui->doubleSpinBox_leftAxis_max->value());
        plotYAxis->setRange(range);
        customPlot->replot();
    });
    connect(ui->fontComboBox_leftAxis_title, &QFontComboBox::currentFontChanged, this, [=]{
       QFont font = ui->fontComboBox_leftAxis_title->currentFont();
       plotYAxis->setLabelFont(font);
       plotYAxis->setTickLabelFont(font);
       customPlot->replot();
    });
    connect(ui->comboBox_leftAxis_min_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotYAxis->labelFont();
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotYAxis->setLabelFont(font);
        plotYAxis->setTickLabelFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_leftAxis_font_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label_leftAxis_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
            plotYAxis->setLabelColor(color);
            plotYAxis->setTickLabelColor(color);
            customPlot->replot();
        }
    });
    connect(ui->pushButton_confirm_leftAxis, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_leftAxis_min_title_content->toPlainText();
        plotYAxis->setLabel(content);
        customPlot->replot();
    });

    // plot axis bottom
    connect(ui->pushButton_bottomAxis_range_confirm, &QPushButton::clicked, this, [=]{
        QCPRange range(ui->doubleSpinBox_bottomAxis_min->value(), ui->doubleSpinBox_bottomAxis_max->value());
        plotXAxis->setRange(range);
        customPlot->replot();
    });
    connect(ui->fontComboBox_bottomAxis_title, &QFontComboBox::currentFontChanged, this, [=]{
       QFont font = ui->fontComboBox_bottomAxis_title->currentFont();
       plotXAxis->setLabelFont(font);
       plotXAxis->setTickLabelFont(font);
       customPlot->replot();
    });
    connect(ui->comboBox_bottomAxis_min_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotXAxis->labelFont();
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotXAxis->setLabelFont(font);
        plotXAxis->setTickLabelFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_bottomAxis_font_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label_bottomAxis_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
            plotXAxis->setLabelColor(color);
            plotXAxis->setTickLabelColor(color);
            customPlot->replot();
        }
    });
    connect(ui->pushButton_confirm_bottomAxis, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_bottomAxis_min_title_content->toPlainText();
        plotXAxis->setLabel(content);
        customPlot->replot();
    });

    // plot axis right
    connect(ui->pushButton_rightAxis_range_confirm, &QPushButton::clicked, this, [=]{
        QCPRange range(ui->doubleSpinBox_rightAxis_min->value(), ui->doubleSpinBox_rightAxis_max->value());
        plotYAxis2->setRange(range);
        customPlot->replot();
    });
    connect(ui->fontComboBox_rightAxis_title, &QFontComboBox::currentFontChanged, this, [=]{
       QFont font = ui->fontComboBox_rightAxis_title->currentFont();
       plotYAxis2->setLabelFont(font);
       plotYAxis2->setTickLabelFont(font);
       customPlot->replot();
    });
    connect(ui->comboBox_rightAxis_min_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotYAxis2->labelFont();
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotYAxis2->setLabelFont(font);
        plotYAxis2->setTickLabelFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_rightAxis_font_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label_rightAxis_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
            plotYAxis2->setLabelColor(color);
            plotYAxis2->setTickLabelColor(color);
            customPlot->replot();
        }
    });
    connect(ui->pushButton_confirm_rightAxis, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_rightAxis_min_title_content->toPlainText();
        plotYAxis2->setLabel(content);
        customPlot->replot();
    });

    // plot axis top
    connect(ui->pushButton_topAxis_range_confirm, &QPushButton::clicked, this, [=]{
        QCPRange range(ui->doubleSpinBox_topAxis_min->value(), ui->doubleSpinBox_topAxis_max->value());
        plotXAxis2->setRange(range);
        customPlot->replot();
    });
    connect(ui->fontComboBox_topAxis_title, &QFontComboBox::currentFontChanged, this, [=]{
       QFont font = ui->fontComboBox_topAxis_title->currentFont();
       plotXAxis2->setLabelFont(font);
       plotXAxis2->setTickLabelFont(font);
       customPlot->replot();
    });
    connect(ui->comboBox_topAxis_min_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotXAxis2->labelFont();
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotXAxis2->setLabelFont(font);
        plotXAxis2->setTickLabelFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_topAxis_font_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label_topAxis_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
            plotXAxis2->setLabelColor(color);
            plotXAxis2->setTickLabelColor(color);
            customPlot->replot();
        }
    });
    connect(ui->pushButton_confirm_topAxis, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_topAxis_min_title_content->toPlainText();
        plotXAxis2->setLabel(content);
        customPlot->replot();
    });

    // plot graph
    connect(ui->pushButton_legend_confirm, &QPushButton::clicked, this, [=]{
        QString content = ui->textEdit_legend_object_content->toPlainText();
        plotGraph->setName(content);
        customPlot->replot();
    });
    connect(ui->fontComboBox_legend_object_title_font, &QFontComboBox::currentFontChanged, this, [=]{
        QFont font = ui->fontComboBox_legend_object_title_font->currentFont();
        plotLegend->setFont(font);
        customPlot->replot();
    });
    connect(ui->comboBox_legend_object_title_font_size, &QComboBox::currentTextChanged, this, [=](QString fontSize){
        QFont font = plotLegend->font();
        bool ok;
        font = QFont(font.family(), fontSize.toInt(&ok), QFont::Black);
        plotLegend->setFont(font);
        customPlot->replot();
    });
    connect(ui->pushButton_legend_object_title_font_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label__legend_object_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
            plotLegend->setTextColor(color);
            customPlot->replot();
        }
    });
    connect(ui->pushButton_legend_sytle_color_select, &QPushButton::clicked, this, [=]{
        QColor color = QColorDialog::getColor(Qt::white, this);
        if (!color.isValid())
            return ;
        else
        {
            ui->label_legend_style_color_show->setStyleSheet("background-color: " + color.name() + ";");
            QPen graphPen;
            graphPen.setColor(color);
            plotGraph->setPen(graphPen);
            customPlot->replot();
        }
    });
    connect(ui->spinBox_legend_style_size, SIGNAL(valueChanged(int)), this, SLOT(plotGraph_SizeChanged(int)));
    connect(ui->comboBox_legend_sytle, &QComboBox::currentTextChanged, this, [=]{
        int index = ui->comboBox_legend_sytle->currentIndex();
        plotGraph->setScatterStyle(QCPScatterStyle(shapes.at(index)));
        customPlot->replot();
    });
}

void App::plotGraph_SizeChanged(int size)
{
    QColor gColor = plotGraph->pen().color();
    QPen graphPen;
    graphPen.setColor(gColor);
    graphPen.setWidth(size);
    plotGraph->setPen(graphPen);
    customPlot->replot();
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
        this->tabW_plotAxis(ui->toolBox_axis->currentIndex());
        break;
    }
    case 2:
    {
        // this->tabW_plotGraph();
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
    ui->textEdit_title_content->setText(title);
    ui->fontComboBox_title->setCurrentFont(font);
    ui->comboBox_title_font_size->setCurrentText(QString::number(font.pointSize()));
    ui->label_title_font_color_show->setStyleSheet("background-color: " + color.name() + ";");
}
void App::tabW_plotAxis(int index)
{
    if (index == 1)
    {
        QCPRange xRange = plotXAxis->range();
        QString xTitle = plotXAxis->label();
        QFont xFont = plotXAxis->labelFont();
        // QFont font0 = plotXAxis->tickLabelFont();
        QColor xColor = plotXAxis->labelColor();
        ui->doubleSpinBox_bottomAxis_min->setValue(xRange.lower);
        ui->doubleSpinBox_bottomAxis_max->setValue(xRange.upper);
        ui->textEdit_bottomAxis_min_title_content->setText(xTitle);
        ui->fontComboBox_bottomAxis_title->setCurrentFont(xFont);
        ui->comboBox_bottomAxis_min_title_font_size->setCurrentText(QString::number(xFont.pointSize()));
        ui->label_bottomAxis_title_font_color_show->setStyleSheet("background-color: " + xColor.name() + ";");
    }
    else if (0 == index)
    {
        QCPRange yRange = plotYAxis->range();
        QString yTitle = plotYAxis->label();
        QFont yFont = plotYAxis->labelFont();
        // QFont font0 = plotXAxis->tickLabelFont();
        QColor yColor = plotYAxis->labelColor();
        ui->doubleSpinBox_leftAxis_max->setValue(yRange.upper);
        ui->doubleSpinBox_leftAxis_min->setValue(yRange.lower);
        ui->textEdit_leftAxis_min_title_content->setText(yTitle);
        ui->fontComboBox_leftAxis_title->setCurrentFont(yFont);
        ui->comboBox_leftAxis_min_title_font_size->setCurrentText(QString::number(yFont.pointSize()));
        ui->label_leftAxis_title_font_color_show->setStyleSheet("background-color: " + yColor.name() + ";");
    }
    else if (3 == index)
    {
        QCPRange x2Range = plotXAxis2->range();
        QString x1Title = plotXAxis2->label();
        QFont x1Font = plotXAxis2->labelFont();
        // QFont font0 = plotXAxis->tickLabelFont();
        QColor x1Color = plotXAxis2->labelColor();
        ui->doubleSpinBox_topAxis_max->setValue(x2Range.upper);
        ui->doubleSpinBox_topAxis_min->setValue(x2Range.lower);
        ui->textEdit_topAxis_min_title_content->setText(x1Title);
        ui->fontComboBox_topAxis_title->setCurrentFont(x1Font);
        ui->comboBox_topAxis_min_title_font_size->setCurrentText(QString::number(x1Font.pointSize()));
        ui->label_topAxis_title_font_color_show->setStyleSheet("background-color: " + x1Color.name() + ";");
    }
    else if (2 == index)
    {
        QCPRange y2Range = plotYAxis2->range();
        QString y1Title = plotYAxis2->label();
        QFont y1Font = plotYAxis2->labelFont();
        // QFont font0 = plotXAxis->tickLabelFont();
        QColor y1Color = plotYAxis2->labelColor();
        ui->doubleSpinBox_rightAxis_max->setValue(y2Range.upper);
        ui->doubleSpinBox_rightAxis_min->setValue(y2Range.lower);
        ui->textEdit_rightAxis_min_title_content->setText(y1Title);
        ui->fontComboBox_rightAxis_title->setCurrentFont(y1Font);
        ui->comboBox_rightAxis_min_title_font_size->setCurrentText(QString::number(y1Font.pointSize()));
        ui->label_rightAxis_title_font_color_show->setStyleSheet("background-color: " + y1Color.name() + ";");
    }
}
void App::tabW_plotGraph()
{

}










































