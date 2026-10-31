#pragma once
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QLabel>
#include <QComboBox>

#include "service.h"
#include "table_model.h"
#include "desen_cercuri_widget.h"

class UI : public QWidget {
private:
    Service& service;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel;

    QLineEdit* txtTitlu = new QLineEdit;
    QLineEdit* txtArtist = new QLineEdit;
    QComboBox* cbGen = new QComboBox;

    QPushButton* btnAdauga = new QPushButton("Adauga Melodie");
    QPushButton* btnSterge = new QPushButton("Sterge Melodie");

    DesenCercuri* widgetCercuri = new DesenCercuri;

    void refreshData() {
        auto melodii = service.getMelodiiSortateDupaArtist();
        auto mapArtisti = service.getContorArtisti();
        auto mapGenuri = service.getContorGenuri();

        model->setDate(melodii, mapArtisti, mapGenuri);
        widgetCercuri->setDate(mapGenuri);
    }

    void connectSignals() {
        QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
            try {
                service.adaugaMelodie(
                    txtTitlu->text().toStdString(),
                    txtArtist->text().toStdString(),
                    cbGen->currentText().toStdString()
                );
                refreshData();
                txtTitlu->clear();
                txtArtist->clear();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare Validare", e.what());
            }
            });

        QObject::connect(btnSterge, &QPushButton::clicked, [this]() {
            auto selectie = table->selectionModel()->selectedRows();
            if (selectie.isEmpty()) {
                QMessageBox::warning(this, "Avertisment", "Nu ai selectat nicio melodie!");
                return;
            }

            int rand = selectie.at(0).row();
            int id = model->data(model->index(rand, 0)).toInt();

            service.stergeMelodie(id);
            refreshData();
            });
    }

public:
    UI(Service& service) : service{ service } {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* susLayout = new QHBoxLayout;

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        susLayout->addWidget(table, 2);

        QVBoxLayout* dreaptaLayout = new QVBoxLayout;

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("Titlu:", txtTitlu);
        formLayout->addRow("Artist:", txtArtist);

        cbGen->addItems({ "pop", "rock", "folk", "disco" });
        formLayout->addRow("Gen:", cbGen);

        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnAdauga);
        dreaptaLayout->addWidget(btnSterge);
        dreaptaLayout->addStretch();

        susLayout->addLayout(dreaptaLayout, 1);

        mainLayout->addLayout(susLayout);
        mainLayout->addWidget(new QLabel("Vizualizare Grafica a Genurilor (Cele 4 colturi):"));
        mainLayout->addWidget(widgetCercuri);

        connectSignals();
        refreshData();

        resize(950, 600);
        setWindowTitle("Gestiune Melodii 2.0");
    }
};