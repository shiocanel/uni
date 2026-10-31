#include <QApplication>
#include "GUI.h"
#include "Test.h"

int main(int argc, char* argv[]) {
    runAllTests();

    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    /*
    1) afisare qlistwidget
    2) vizualizare detalii
    3) sort
    4) tooltip  
    
    */

    return app.exec();
}