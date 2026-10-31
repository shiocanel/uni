#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "ui.h"
#include "test.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    try {
        testAll();

        Repository repo("taskuri.txt");
        Service service{ repo };
        UI mainWindow{ service };

        mainWindow.show();

        return app.exec();
    }
    catch (const exception& e) {
        QMessageBox::critical(nullptr, "Eroare la pornire", e.what());
    }
    return 0;
}