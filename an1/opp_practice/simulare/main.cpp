#include <QtWidgets/QApplication>

#include "UI.h"
#include <Test.h>

/*
functia main a aplicatiei
*/
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try {
        testAll();

        Repository repo("postari.txt");
        Service service{ repo };
        UI window{service};
        window.show();

        return app.exec();
    }
    catch (exception& e) {
        QMessageBox::critical(nullptr, "Eroare", e.what());
    }
}
