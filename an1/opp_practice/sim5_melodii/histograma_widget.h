#pragma once
#include <QWidget>
#include <QPainter>
#include <vector>
#include <algorithm>

class DesenBare : public QWidget {
private:
    std::vector<int> frecvente;

public:
    DesenBare(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(150);
        frecvente.resize(11, 0);
    }

    void setDate(const std::vector<int>& noiFrecvente) {
        frecvente = noiFrecvente;
        update();
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter p(this);
        int w = width();
        int h = height();

        int spatiuJos = 20;
        int inaltimeMaximaBara = h - spatiuJos - 10;
        int barWidth = w / 11;

        int maxVal = *std::max_element(frecvente.begin(), frecvente.end());
        if (maxVal == 0) maxVal = 1;

        for (int i = 0; i <= 10; ++i) {
            int barHeight = (frecvente[i] * inaltimeMaximaBara) / maxVal;

            p.setBrush(Qt::darkCyan);
            p.drawRect(i * barWidth + 2, h - spatiuJos - barHeight, barWidth - 4, barHeight);

            p.drawText(i * barWidth + barWidth / 2 - 5, h - 5, QString::number(i));
        }
    }
};