#include "ui.h"
#include "test.h"
#include <QApplication>
#include <QFont>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    try {
        testAll();

        Repository repo("rochii.txt");
        Service service{ repo };
        UI ui{ service };

        ui.show();

        return a.exec();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Eroare", e.what());
    }

    return 0;
}