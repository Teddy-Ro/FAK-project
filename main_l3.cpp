#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLabel label("this is where the FAK project started!");
    label.show();

    return app.exec();
}
