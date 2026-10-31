#include <QtWidgets/QApplication>
#include "ui.h"
#include "test.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    try {
        testAll();

        Repository repo("jocuri.txt");
        Service service{ repo };
        UI window{ service };

        window.show();

        return app.exec();
    }
    catch (const exception& e) {
        QMessageBox::critical(nullptr, "Eroare la pornire", e.what());
    }
    return 0;
}