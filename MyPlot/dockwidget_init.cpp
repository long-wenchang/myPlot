#include "app.h"
#include "ui_app.h"

void App::dockWidget_Init()
{
    dock_data = ui->dockWidget_data;
    dock_setting = ui->dockWidget_setting;
    connect(ui->menu_windows, &QMenu::aboutToShow, this, &App::action_window_Slot);

    dock_data->setHidden(false);
    dock_setting->setHidden(true);

    ui->action_data_window->setCheckable(true);
    ui->action_setting_window->setCheckable(true);

    connect(ui->action_data_window, &QAction::toggled, dock_data, [=](bool ok){
        dock_data->setHidden(!ok);
    });
    connect(ui->action_setting_window, &QAction::toggled, dock_setting, [=](bool ok){
        dock_setting->setHidden(!ok);
    });
}

void App::action_window_Slot()
{
    if (dock_data->isHidden())
        ui->action_data_window->setChecked(false);
    else
        ui->action_data_window->setChecked(true);
    if (dock_setting->isHidden())
        ui->action_setting_window->setChecked(false);
    else
        ui->action_setting_window->setChecked(true);
}
