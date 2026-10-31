#include <QtWidgets/QApplication>

#include "UI.h"
#include "Test.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    try {
        testAll();

        Repository repo("apartamente.txt");
        Service service{ repo };
        UI window{service};
        window.show();

        return app.exec();
    }
    catch (const exception& e) {

    }
    return 0;
}
