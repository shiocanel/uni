#pragma once
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>

#include "service.h"
#include "table_model.h"

class UI : public QWidget {
private:
    Service& service;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel;

    QPushButton* btnPlus = new QPushButton("+");
    QPushButton* btnMinus = new QPushButton("-");
    QPushButton* btnSterge = new QPushButton("Stergere");
    QPushButton* btnUndo = new QPushButton("Undo");
    QPushButton* btnRedo = new QPushButton("Redo");

    void reloadData() {
        model->setMasini(service.getSortedByNrInmatriculare());
    }

    void connectSignals() {
        QObject::connect(btnPlus, &QPushButton::clicked, [this]() {
            service.modificaAn(1);
            reloadData();
            });

        QObject::connect(btnMinus, &QPushButton::clicked, [this]() {
            service.modificaAn(-1);
            reloadData();
            });

        QObject::connect(btnSterge, &QPushButton::clicked, [this]() {
            auto selectedRows = table->selectionModel()->selectedRows();
            if (selectedRows.isEmpty()) {
                QMessageBox::warning(this, "Avertisment", "Nu ai selectat nicio masina!");
                return;
            }

            vector<string> deSters;
            for (const auto& index : selectedRows) {
                // Luam datele de pe coloana 0 (nr inmatriculare, care e unic)
                string nrInmatriculare = model->data(model->index(index.row(), 0)).toString().toStdString();
                deSters.push_back(nrInmatriculare);
            }

            service.stergeMasini(deSters);
            reloadData();
            });

        QObject::connect(btnUndo, &QPushButton::clicked, [this]() {
            try {
                service.undo();
                reloadData();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare", e.what());
            }
            });

        QObject::connect(btnRedo, &QPushButton::clicked, [this]() {
            try {
                service.redo();
                reloadData();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare", e.what());
            }
            });
    }

public:
    UI(Service& service) : service{ service } {
        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        QVBoxLayout* buttonsLayout = new QVBoxLayout;

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::ExtendedSelection);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        mainLayout->addWidget(table);
        mainLayout->addLayout(buttonsLayout);

        buttonsLayout->addWidget(btnPlus);
        buttonsLayout->addWidget(btnMinus);
        buttonsLayout->addWidget(btnSterge);
        buttonsLayout->addStretch();
        buttonsLayout->addWidget(btnUndo);
        buttonsLayout->addWidget(btnRedo);

        connectSignals();
        reloadData();

        resize(900, 500);
        setWindowTitle("Gestiune Masini");
    }
};