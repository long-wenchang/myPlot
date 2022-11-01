#include "app.h"
#include "ui_app.h"

void App::dockWidget_Init()
{
    dockWidget_data = ui->dockWidget_data;
    dockWidget_setting = ui->dockWidget_setting;
    dockWidget_status = ui->dockWidget_status;
    connect(ui->menu_shitu, &QMenu::aboutToShow, this, &App::action_state);

    dockWidget_data->setWindowTitle("数据");
    dockWidget_setting->setWindowTitle("设置");
    dockWidget_status->setWindowTitle("状态");
    dockWidget_data->setHidden(false);
    dockWidget_setting->setHidden(true);
    dockWidget_status->setHidden(true);

    ui->action_save->setText("保存数据");
    ui->action_open->setText("打开文件");
    ui->action_export->setText("导出图片");

    ui->action_data->setText("数据窗口");
    ui->action_setting->setText("设置窗口");
    ui->action_status->setText("状态窗口");

    ui->action_data->setCheckable(true);
    ui->action_setting->setCheckable(true);
    ui->action_status->setCheckable(true);

    connect(ui->action_data, &QAction::toggled, ui->dockWidget_data, [=](bool state){
        ui->dockWidget_data->setHidden(!state);
    });
    connect(ui->action_setting, &QAction::toggled, ui->dockWidget_setting, [=](bool state){
        ui->dockWidget_setting->setHidden(!state);
    });
    connect(ui->action_status, &QAction::toggled, ui->dockWidget_status, [=](bool state){
        ui->dockWidget_status->setHidden(!state);
    });

    this->dockWidget_data_Init();
    this->dockWidget_setting_Init();
    this->dockWidget_state_Init();
}

void App::action_state()
{
#if 0
    mDockWidget *a = qobject_cast<mDockWidget*>(sender());

    if (a == dockWidget_data)
    {
        ui->action_data->setChecked(false);
    }
    else if (a == dockWidget_setting)
    {
        ui->action_setting->setChecked(false);
    }
    else if (a == dockWidget_status)
    {
        ui->action_status->setChecked(false);
    }
#endif
    if (dockWidget_data->isHidden())
        ui->action_data->setChecked(false);
    else
        ui->action_data->setChecked(true);
    if (dockWidget_setting->isHidden())
        ui->action_setting->setChecked(false);
    else
        ui->action_setting->setChecked(true);
    if (dockWidget_status->isHidden())
        ui->action_status->setChecked(false);
    else
        ui->action_status->setChecked(true);
}

void App::dockWidget_data_Init()
{}

void App::dockWidget_setting_Init()
{
//    ui->tabWidget_setting->setTabText(0, "plot title");
//    ui->tabWidget_setting->setTabText(1, "axis");
//    ui->tabWidget_setting->setTabText(2, "plot");
//    ui->tabWidget_setting->setTabText(3, "legend");

//    ui->tabWidget_setting->tabBar()->setTabButton(0, QTabBar::ButtonPosition::LeftSide, ui->widget_setting);
//    ui->tabWidget_setting->tabBar()->setTabButton(1, QTabBar::ButtonPosition::LeftSide, ui->widget_setting);
//    ui->tabWidget_setting->tabBar()->setTabButton(2, QTabBar::ButtonPosition::LeftSide, ui->widget_setting);
//    ui->tabWidget_setting->tabBar()->setTabButton(0, QTabBar::ButtonPosition::LeftSide, ui->widget_setting);

}

void App::dockWidget_state_Init()
{}









































