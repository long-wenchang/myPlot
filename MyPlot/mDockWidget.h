#ifndef MDOCKWIDGET_H
#define MDOCKWIDGET_H
#include <QDockWidget>
#include <QObject>
#include <QEvent>

class mDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit mDockWidget(QWidget *parent = nullptr);

    bool event(QEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void close();

signals:
    void closeWidget();
};

#endif // MDOCKWIDGET_H
