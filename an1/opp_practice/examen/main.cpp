#include <QtWidgets/QApplication>
#include <QMessageBox>

#include "ui.h"
#include "test.h"

using namespace std;

int main(int argc, char* argv[]){
    QApplication app(argc, argv);

    try {
        testAll();

        Repository repo("melodii.txt");
        Service service{ repo };
        UI window{ service };

        window.show();

        return app.exec();
    }
    catch (const exception& e) {
        QMessageBox::critical(nullptr, "Eroaare", e.what());
    }
    return 0;
}


/*
1;Die;Violent Viora;7
2;Smells like Teens Spirits;Nirvana;8
3;M'son 'Mbriacato;Giovanni; 10
4;Azzuro;Antonino;8
5;Mega;Tarantiono;5
6;Trieste;Sckrilex;2
7;I luv u;Ed Sheeran;6
8;Mai nu stiu piese;eu;8
9;Change;Deftones;9
10;Shape of You;Ed Sheeran;9
*/