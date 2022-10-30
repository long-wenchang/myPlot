#include "app.h"
#include "ui_app.h"
#include "QMenu"

App::App(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::App)
{
    ui->setupUi(this);

    this->customPlot_Init();

    dockWidget_data = ui->dockWidget_data;
    dockWidget_setting = ui->dockWidget_setting;
    dockWidget_status = ui->dockWidget_status;

    dockWidget_data->setWindowTitle("数据");
    dockWidget_setting->setWindowTitle("设置");
    dockWidget_status->setWindowTitle("状态");
    dockWidget_data->setHidden(false);
    dockWidget_setting->setHidden(true);
    dockWidget_status->setHidden(true);

    ui->action_save->setText("保存数据");
    ui->action_open->setText("打开文件");
    ui->action_export->setText("导出数据");

    ui->action_data->setText("数据窗口");
    ui->action_setting->setText("设置窗口");
    ui->action_status->setText("状态窗口");

    ui->action_data->setCheckable(true);
    ui->action_setting->setCheckable(true);
    ui->action_status->setCheckable(true);
    ui->action_data->setChecked(true);
    ui->action_setting->setChecked(true);
    ui->action_status->setChecked(true);

    connect(ui->action_data, &QAction::toggled, ui->dockWidget_data, [=](bool state){
        ui->dockWidget_data->setHidden(!state);
    });
    connect(ui->action_setting, &QAction::toggled, ui->dockWidget_setting, [=](bool state){
        ui->dockWidget_setting->setHidden(!state);
    });
    connect(ui->action_status, &QAction::toggled, ui->dockWidget_status, [=](bool state){
        ui->dockWidget_status->setHidden(!state);
    });
}

App::~App()
{
    delete ui;
}

