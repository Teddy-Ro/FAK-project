#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>

constexpr QPoint kInvalidPoint(-1, -1);

class ToolWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ToolWindow(QWidget* _parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* _event) override;
    void mouseMoveEvent(QMouseEvent* _event) override;
    void mouseReleaseEvent(QMouseEvent* _event) override;

private:
    QPoint pos_;
};

#endif // TOOLWINDOW_H
