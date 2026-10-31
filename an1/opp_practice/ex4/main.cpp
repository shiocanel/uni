#include <QtWidgets/QApplication>

#include "UI.h"
#include "Test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    try {
        testAll();

        Repository repo("procesoare.txt", "placiDeBaza.txt");
        Service service{ repo };
        UI window{service};
        window.show();
        return app.exec();
    }
    catch(const std::exception& e) {
        QMessageBox::critical(nullptr, "Eroare", e.what());
    }
    return 0;
}
