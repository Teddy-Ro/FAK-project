#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint>

class MainWindow : public QMainWindow {
    Q_OBJECT

 public:
    explicit MainWindow(QWidget* parent = nullptr);

 protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

 private:
    enum ResizeDirection {
        None,
        Left,
        Right,
        Top,
        Bottom,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    void updateCursorShape();

    ResizeDirection getResizeDirection(const QPoint& pos) const;

    bool m_mousePressed;
    QPoint m_pressPos;
    ResizeDirection m_resizeDirection;

    static constexpr int RESIZE_MARGIN = 10;
};

#endif  // MAINWINDOW_H
