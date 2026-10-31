#include <QtWidgets/QApplication>
#include <QMessageBox>
#include "ui.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    try {
        Repository repo("tractoare.txt");
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