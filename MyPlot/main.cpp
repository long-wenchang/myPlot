#include "app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    App w;
    w.setWindowIcon(QIcon(":/img/app.ico"));
    w.show();
    return a.exec();
}
