#include <QtWidgets/QApplication>

#include "ui.h"
#include "test.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    try {
        testAll();

        Repository repo("masini.txt");
        Service service{ repo };
        UI window{service};
        
        window.show();

        return app.exec();
    }
    catch (const exception& e) {
        QMessageBox::critical(nullptr, "Eroare", e.what());
    }
    return 0;
}
