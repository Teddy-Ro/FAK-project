#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QFrame>
#include <QStyleFactory>

class MainWindow : public QMainWindow {
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Устанавливаем минималистичный стиль
        QApplication::setStyle(QStyleFactory::create("Fusion"));

        // Создаем главный виджет
        QWidget *centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);

        // Создаем горизонтальный layout для главного виджета
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

        // Создаем боковую панель
        QFrame *sidePanel = new QFrame(this);
        sidePanel->setFrameShape(QFrame::StyledPanel);
        sidePanel->setFixedWidth(200);

        // Создаем вертикальный layout для боковой панели
        QVBoxLayout *sidePanelLayout = new QVBoxLayout(sidePanel);

        // Создаем разделитель для боковой панели
        QSplitter *splitter = new QSplitter(Qt::Vertical, sidePanel);

        // Верхняя часть боковой панели
        QWidget *topWidget = new QWidget(splitter);
        QVBoxLayout *topLayout = new QVBoxLayout(topWidget);
        QPushButton *button1 = new QPushButton("Button 1", topWidget);
        QPushButton *button2 = new QPushButton("Button 2", topWidget);
        topLayout->addWidget(button1);
        topLayout->addWidget(button2);
        topWidget->setLayout(topLayout);

        // Нижняя часть боковой панели
        QWidget *bottomWidget = new QWidget(splitter);
        QVBoxLayout *bottomLayout = new QVBoxLayout(bottomWidget);
        QPushButton *button3 = new QPushButton("Button 3", bottomWidget);
        QPushButton *button4 = new QPushButton("Button 4", bottomWidget);
        bottomLayout->addWidget(button3);
        bottomLayout->addWidget(button4);
        bottomWidget->setLayout(bottomLayout);

        // Добавляем разделитель в боковую панель
        sidePanelLayout->addWidget(splitter);
        sidePanel->setLayout(sidePanelLayout);

        // Добавляем боковую панель в главный layout
        mainLayout->addWidget(sidePanel);

        // Создаем основное содержимое
        QWidget *mainContent = new QWidget(this);
        mainLayout->addWidget(mainContent, 1);

        // Устанавливаем layout для главного виджета
        centralWidget->setLayout(mainLayout);

        // Настройка темной темы
        setStyleSheet(
            // Общие стили для всего приложения
            "QWidget {"
            "   background-color: #2d2d2d;" // Темный фон
            "   color: #ffffff;" // Белый текст
            "}"
            "QFrame {"
            "   background-color: #3d3d3d;" // Темный фон для боковой панели
            "   border: 1px solid #444;" // Граница
            "}"
            "QPushButton {"
            "   background-color: #4d4d4d;" // Темный фон для кнопок
            "   color: #ffffff;" // Белый текст
            "   border: 1px solid #555;" // Граница
            "   padding: 5px;" // Отступы
            "   border-radius: 3px;" // Закругленные углы
            "}"
            "QPushButton:hover {"
            "   background-color: #5d5d5d;" // Изменение цвета при наведении
            "}"
            "QSplitter::handle {"
            "   background-color: #444;" // Цвет разделителя
            "}"
        );
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Dark Theme App");
    window.resize(800, 600);
    window.show();

    return app.exec();
}
