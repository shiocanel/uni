#pragma once
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <functional>

class DesenRoti : public QWidget {
private:
    int numarRoti = 0;
    int raza = 15;
    int spatiu = 10;
    std::function<void()> onClick;

public:
    DesenRoti(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumHeight(50);
    }

    void setSate(int nrRoti, std::function<void()> callback) {
        numarRoti = nrRoti;
        onClick = callback;
        update(); // Forteaza redesenarea (apeleaza paintEvent)
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);
        p.setBrush(Qt::darkGray);

        for (int i = 0; i < numarRoti; i++) {
            int x = spatiu + i * (2 * raza + spatiu);
            int y = spatiu;
            p.drawEllipse(x, y, raza * 2, raza * 2);
        }
    }

    void mousePressEvent(QMouseEvent* event) override {
        int mouseX = event->pos().x();
        int mouseY = event->pos().y();

        for (int i = 0; i < numarRoti; i++) {
            int x = spatiu + i * (2 * raza + spatiu);
            int y = spatiu;

            QRect rectDedicat(x, y, raza * 2, raza * 2);
            if (rectDedicat.contains(mouseX, mouseY)) {
                if (onClick) onClick();
                break;
            }
        }
    }
};