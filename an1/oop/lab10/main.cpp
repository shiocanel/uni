#include <QApplication>
#include "GUI.h"
#include "Test.h"

int main(int argc, char* argv[]) {
    runAllTests();

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    //ui.run();

    return app.exec();
}