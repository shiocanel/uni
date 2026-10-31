#pragma once
#include "service.h"
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

class UI : public QWidget {
private:
    Service& service;
    std::vector<Rochie> displayedRochii;

    QListWidget* lista = new QListWidget;
    QPushButton* inchiriereButton = new QPushButton("Inchiriere rochie");
    QPushButton* sortMarimeButton = new QPushButton("Sortare marime");
    QPushButton* sortPretButton = new QPushButton("Sortare pret");
    QPushButton* nesortatButton = new QPushButton("Nesortat");

    int getSelectedIndex() const {
        auto rows = lista->selectionModel()->selectedRows();
        if (rows.empty()) {
            return -1;
        }
        return rows.at(0).row();
    }

    void populateList(const std::vector<Rochie>& rochii) {
        displayedRochii = rochii;
        lista->clear();

        for (const auto& r : displayedRochii) {
            std::string text = r.getDenumire() + " | " + r.getMarime() + " | " + std::to_string(r.getPret()) + " lei";
            auto* item = new QListWidgetItem(QString::fromStdString(text));
            item->setBackground(r.isDisponibila() ? Qt::green : Qt::red);
            lista->addItem(item);
        }
    }

    void connectSignals() {
        QObject::connect(inchiriereButton, &QPushButton::clicked, [this]() {
            int index = getSelectedIndex();
            if (index == -1) {
                QMessageBox::warning(this, "Eroare", "Selecteaza o rochie din lista.");
                return;
            }

            try {
                Rochie selected = displayedRochii.at(index);
                service.inchiriazaRochie(selected.getCod());
                populateList(service.getAll());
            }
            catch (const std::runtime_error& e) {
                QMessageBox::warning(this, "Inchiriere esuata", e.what());
            }
            });

        QObject::connect(sortMarimeButton, &QPushButton::clicked, [this]() {
            populateList(service.sortByMarime());
            });

        QObject::connect(sortPretButton, &QPushButton::clicked, [this]() {
            populateList(service.sortByPret());
            });

        QObject::connect(nesortatButton, &QPushButton::clicked, [this]() {
            populateList(service.getAll());
            });
    }

public:
    UI(Service& service) : service{ service } {
        auto* mainLayout = new QHBoxLayout(this);
        auto* buttonsLayout = new QVBoxLayout;

        mainLayout->addWidget(lista);
        mainLayout->addLayout(buttonsLayout);

        buttonsLayout->addWidget(inchiriereButton);
        buttonsLayout->addWidget(sortMarimeButton);
        buttonsLayout->addWidget(sortPretButton);
        buttonsLayout->addWidget(nesortatButton);

        connectSignals();
        populateList(service.getAll());

        setWindowTitle("Magazin de inchirieri rochii");
        resize(900, 500);
    }
};