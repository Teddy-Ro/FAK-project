#include "ToolWindow.h"

ToolWindow::ToolWindow(QWidget* _parent)
    : QWidget(_parent)
    , pos_(kInvalidPoint)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
    resize(256, 256);
}

void ToolWindow::mousePressEvent(QMouseEvent* _event)
{
    if (_event->button() == Qt::LeftButton &&
        _event->modifiers() == Qt::NoModifier)
    {
        pos_ = _event->globalPos();
        setCursor(Qt::CloseHandCursor);
        return;
    }
    QWidget::mousePressEvent(_event);
}

void ToolWindow::mouseMoveEvent(QMouseEvent* _event)
{
    if (pos_ == kInvalidPoint)
        return QWidget::mouseMoveEvent(_event);

    const QPoint delta = _event->globalPos() - pos_;
    move(pos() + delta);
    pos_ = _event->globalPos();
}

void ToolWindow::mouseReleaseEvent(QMouseEvent* _event)
{
    pos_ = kInvalidPoint;
    setCursor(Qt::OpenHandCursor);
    QWidget::mouseReleaseEvent(_event);
}
