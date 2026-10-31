#pragma once
#include <QWidget>
#include <QPainter>
#include <map>
#include <string>

class DesenCercuri : public QWidget {
private:
    std::map<std::string, int> countGenuri;

public:
    DesenCercuri(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(200);
    }

    void setDate(const std::map<std::string, int>& cg) {
        countGenuri = cg;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        int w = width();
        int h = height();
        int margine = 50;

        QPoint centerPop(margine, margine);
        QPoint centerRock(w - margine, margine);
        QPoint centerFolk(margine, h - margine);
        QPoint centerDisco(w - margine, h - margine);

        deseneazaGrupCercuri(p, centerPop, "pop");
        deseneazaGrupCercuri(p, centerRock, "rock");
        deseneazaGrupCercuri(p, centerFolk, "folk");
        deseneazaGrupCercuri(p, centerDisco, "disco");

        p.setPen(Qt::black);
        p.drawText(centerPop + QPoint(20, 0), "POP");
        p.drawText(centerRock + QPoint(-45, 0), "ROCK");
        p.drawText(centerFolk + QPoint(20, 0), "FOLK");
        p.drawText(centerDisco + QPoint(-45, 0), "DISCO");
    }

private:
    void deseneazaGrupCercuri(QPainter& p, QPoint center, const std::string& gen) {
        p.setPen(Qt::black);
        p.setBrush(Qt::NoBrush);

        int razaDeBaza = 5;
        p.drawEllipse(center, razaDeBaza, razaDeBaza);

        int numarMelodii = countGenuri[gen];

        for (int i = 1; i <= numarMelodii; ++i) {
            int razaNoua = razaDeBaza + (i * 10);
            p.drawEllipse(center, razaNoua, razaNoua);
        }
    }
};