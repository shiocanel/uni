#pragma once
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <string>
#include "service.h"
#include "observer.h"

class TipWindow : public QWidget, public Observer {
private:
    std::string tipProdus;
    Service& service;
    QLabel* lblCount = new QLabel;

    void updateCount() {
        int nr = service.getNumarProduseTip(tipProdus);
        lblCount->setText(QString("Numar produse de tipul '%1': %2")
            .arg(QString::fromStdString(tipProdus)).arg(nr));
    }

public:
    TipWindow(std::string tip, Service& srv) : tipProdus(tip), service(srv) {
        setWindowTitle(QString::fromStdString(tipProdus));

        QVBoxLayout* layout = new QVBoxLayout(this);

        lblCount->setStyleSheet("font-size: 16px; font-weight: bold;");
        layout->addWidget(lblCount);

        resize(300, 150);

        updateCount();

        service.addObserver(this);
    }

    void update() override {
        updateCount();
    }

    ~TipWindow() {
        service.removeObserver(this);
    }
};