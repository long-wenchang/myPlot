#include "mDockWidget.h"

mDockWidget::mDockWidget(QWidget *parent) : QDockWidget(parent)
{}

bool mDockWidget::event(QEvent *event)
{
    if (QEvent::ZOrderChange == event->type()) {
            if (isFloating()) {
                QWidget w;
                setMaximumSize(w.maximumSize());
                setWindowFlags(Qt::Dialog
                               | Qt::WindowCloseButtonHint
                               //| Qt::WindowMaximizeButtonHint
                               //| Qt::WindowMinimizeButtonHint
                               );
            }
        }

        return QDockWidget::event(event);
}

void mDockWidget::closeEvent(QCloseEvent *event)
{
    // 关闭信号
    emit closeWidget();
}
