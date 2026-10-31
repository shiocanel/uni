#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QPushButton button("Qt merge!");
    button.resize(300, 100);
    button.show();

    return app.exec();
}