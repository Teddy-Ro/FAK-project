#include "MainWindow.h"
#include <QApplication>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QSplitter>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>

// Размер рамки окна, за которую можно потянуть для изменения размера
const int RESIZE_MARGIN = 10;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowFlags(Qt::FramelessWindowHint);
    setMouseTracking(true);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создание кастомной панели заголовка
    QWidget* titleBar = new QWidget(centralWidget);
    titleBar->setFixedHeight(30);
    titleBar->setStyleSheet("background-color: #2d2d2d;");

    // Кнопки управления окном
    QPushButton* minButton = new QPushButton("—", titleBar);
    QPushButton* maxButton = new QPushButton("□", titleBar);
    QPushButton* closeButton = new QPushButton("×", titleBar);

    // Стилизация кнопок
    QString buttonStyle =
        "QPushButton {"
        "   background: transparent;"
        "   color: #ffffff;"
        "   border: none;"
        "   padding: 8px 8px;"
        "   font-size: 15px;"
        "}"
        "QPushButton:hover {"
        "   background: #5d5d5d;"
        "}";

    minButton->setStyleSheet(buttonStyle);
    maxButton->setStyleSheet(buttonStyle);
    closeButton->setStyleSheet(buttonStyle + "QPushButton:hover { background: #ff4444; }");

    // Расположение элементов в заголовке
    QHBoxLayout* titleLayout = new QHBoxLayout(titleBar);
    titleLayout->addStretch();
    titleLayout->addWidget(minButton);
    titleLayout->addWidget(maxButton);
    titleLayout->addWidget(closeButton);
    titleLayout->setContentsMargins(0, 0, 0, 0);

    // Основное содержимое
    QWidget* content = new QWidget(centralWidget);
    content->setStyleSheet("background:rgb(121, 17, 17);");

    QPushButton* cursorButton = new QPushButton("change coursor", content);
    cursorButton->setFixedHeight(80);

    QHBoxLayout* tcontentLayout = new QHBoxLayout(content);
    tcontentLayout->addWidget(cursorButton);
    tcontentLayout->setContentsMargins(0, 0, 0, 0);

    // Главный layout
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(titleBar);
    mainLayout->addWidget(content);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Подключение кнопок
    connect(closeButton, &QPushButton::clicked, this, &QMainWindow::close);
    connect(minButton, &QPushButton::clicked, this, &QMainWindow::showMinimized);
    connect(maxButton, &QPushButton::clicked, [this]() { isMaximized() ? showNormal() : showMaximized(); });

    connect(cursorButton, &QPushButton::clicked, [this]() { this->setCursor(Qt::SizeVerCursor); });

    // Настройка окна
    setMinimumSize(800, 600);
    setWindowTitle("Custom Window");

    // Переменные для отслеживания состояния изменения размера
    m_resizeDirection = None;
    m_mousePressed = false;
    m_pressPos = QPoint();
}

void MainWindow::updateCursorShape() {
    QRect windowRect = rect();
    int left = windowRect.left();
    int right = windowRect.right();
    int top = windowRect.top();
    int bottom = windowRect.bottom();

    QPoint cursorPos = mapFromGlobal(QCursor::pos());

    if (cursorPos.x() >= left && cursorPos.x() <= left + RESIZE_MARGIN && cursorPos.y() >= top && cursorPos.y() <= top + RESIZE_MARGIN) {
        setCursor(Qt::SizeFDiagCursor);  // Курсор для верхнего левого угла
    } else if (cursorPos.x() >= right - RESIZE_MARGIN && cursorPos.x() <= right && cursorPos.y() >= top && cursorPos.y() <= top + RESIZE_MARGIN) {
        setCursor(Qt::SizeBDiagCursor);  // Курсор для верхнего правого угла
    } else if (cursorPos.x() >= left && cursorPos.x() <= left + RESIZE_MARGIN && cursorPos.y() >= bottom - RESIZE_MARGIN && cursorPos.y() <= bottom) {
        setCursor(Qt::SizeBDiagCursor);  // Курсор для нижнего левого угла
    } else if (cursorPos.x() >= right - RESIZE_MARGIN && cursorPos.x() <= right && cursorPos.y() >= bottom - RESIZE_MARGIN &&
               cursorPos.y() <= bottom) {
        setCursor(Qt::SizeFDiagCursor);  // Курсор для нижнего правого угла
    } else if (cursorPos.x() >= left && cursorPos.x() <= left + RESIZE_MARGIN) {
        setCursor(Qt::SizeHorCursor);  // Курсор для левой стороны
    } else if (cursorPos.x() >= right - RESIZE_MARGIN && cursorPos.x() <= right) {
        setCursor(Qt::SizeHorCursor);  // Курсор для правой стороны
    } else if (cursorPos.y() >= top && cursorPos.y() <= top + RESIZE_MARGIN) {
        setCursor(Qt::SizeVerCursor);  // Курсор для верхней стороны
    } else if (cursorPos.y() >= bottom - RESIZE_MARGIN && cursorPos.y() <= bottom) {
        setCursor(Qt::SizeVerCursor);  // Курсор для нижней стороны
    } else {
        unsetCursor();  // Устанавливаем стандартный курсор
    }
}

MainWindow::ResizeDirection MainWindow::getResizeDirection(const QPoint& pos) const {
    QRect windowRect = rect();
    int left = windowRect.left();
    int right = windowRect.right();
    int top = windowRect.top();
    int bottom = windowRect.bottom();

    // Определяем направление изменения размера
    if (pos.x() >= left && pos.x() <= left + RESIZE_MARGIN && pos.y() >= top && pos.y() <= top + RESIZE_MARGIN) {
        return TopLeft;
    } else if (pos.x() >= right - RESIZE_MARGIN && pos.x() <= right && pos.y() >= top && pos.y() <= top + RESIZE_MARGIN) {
        return TopRight;
    } else if (pos.x() >= left && pos.x() <= left + RESIZE_MARGIN && pos.y() >= bottom - RESIZE_MARGIN && pos.y() <= bottom) {
        return BottomLeft;
    } else if (pos.x() >= right - RESIZE_MARGIN && pos.x() <= right && pos.y() >= bottom - RESIZE_MARGIN && pos.y() <= bottom) {
        return BottomRight;
    } else if (pos.x() >= left && pos.x() <= left + RESIZE_MARGIN) {
        return Left;
    } else if (pos.x() >= right - RESIZE_MARGIN && pos.x() <= right) {
        return Right;
    } else if (pos.y() >= top && pos.y() <= top + RESIZE_MARGIN) {
        return Top;
    } else if (pos.y() >= bottom - RESIZE_MARGIN && pos.y() <= bottom) {
        return Bottom;
    }

    return None;
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->buttons() == Qt::LeftButton) {
        m_mousePressed = true;
        m_pressPos = event->globalPosition().toPoint();
        m_resizeDirection = getResizeDirection(event->pos());
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
    if (!m_mousePressed || m_resizeDirection == None) {
        return;
    }

    QPoint globalCursorPos = event->globalPosition().toPoint();
    QRect currentGeometry = geometry();

    switch (m_resizeDirection) {
        case Left:
            currentGeometry.setLeft(globalCursorPos.x());
            break;
        case Right:
            currentGeometry.setRight(globalCursorPos.x());
            break;
        case Top:
            currentGeometry.setTop(globalCursorPos.y());
            break;
        case Bottom:
            currentGeometry.setBottom(globalCursorPos.y());
            break;
        case TopLeft:
            currentGeometry.setTopLeft(globalCursorPos);
            break;
        case TopRight:
            currentGeometry.setTopRight(globalCursorPos);
            break;
        case BottomLeft:
            currentGeometry.setBottomLeft(globalCursorPos);
            break;
        case BottomRight:
            currentGeometry.setBottomRight(globalCursorPos);
            break;
        default:
            break;
    }

    setGeometry(currentGeometry);
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        m_mousePressed = false;
        m_resizeDirection = None;
    }
}
