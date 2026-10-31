#pragma once
#include <QWidget>
#include <QPainter>
#include <vector>
#include <algorithm>

using namespace std;

class DesenBare : public QWidget {
private:
    vector<int> frecvente;

public:
    DesenBare(QWidget* parent = nullptr) : QWidget(parent) {
        /*
        constructor care initializeaza DesenBare care este o subclasa QWidget
        pre:
        post:
        */

        setMinimumHeight(150);
        frecvente.resize(11, 0);
    }

    void setDate(const vector<int>& noiFrecvente) {
        /*
        da update la frecventa
        pre: noi (vector<int>)
        post: fecvente este modificat cu noiFrecvente
        */

        frecvente = noiFrecvente;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        /*
        functie care se ocupa de desenarea barilor la pozitiile x, y si cu latime w si inaltime h
        pre:
        post:
        */

        QPainter p(this);
        int w = width();
        int h = height();

        int spatiu_jos = 20;
        int inaltime_max = h - spatiu_jos - 10;
        int bar_latime = w / 11;

        int maxVal = *std::max_element(frecvente.begin(), frecvente.end());
        if (maxVal == 0) 
            maxVal = 1;

        for (int i = 0; i <= 10; ++i) {
            int bar_inaltime = (frecvente[i] * inaltime_max) / maxVal;
            
            p.setBrush(Qt::darkCyan);
            p.drawRect(i * bar_latime + 2, h - spatiu_jos - bar_inaltime, bar_latime - 4, bar_inaltime);

            p.drawText(i * bar_latime + bar_latime / 2 - 5, h - 5, QString::number(i));
        }
    }
};