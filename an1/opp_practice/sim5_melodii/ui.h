#pragma once
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>

#include "service.h"
#include "table_model.h"
#include "histograma_widget.h"

class UI : public QWidget {
private:
    Service& service;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel;

    QLineEdit* txtTitlu = new QLineEdit;
    QSlider* sliderRank = new QSlider(Qt::Horizontal);
    QLabel* lblRankValue = new QLabel("0");

    QPushButton* btnUpdate = new QPushButton("Update Melodie");
    QPushButton* btnDelete = new QPushButton("Sterge Melodie");

    DesenBare* widgetDesen = new DesenBare;

    int idSelectat = -1;

    void incarcaDate() {
        auto melodiiSortate = service.getMelodiiSortateDupaRank();
        auto frecvente = service.getFrecventeRank();

        model->setMelodii(melodiiSortate, frecvente);
        widgetDesen->setDate(frecvente);
    }

    void connectSignals() {
        QObject::connect(sliderRank, &QSlider::valueChanged, [this](int val) {
            lblRankValue->setText(QString::number(val));
            });

        QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
            auto selectie = table->selectionModel()->selectedRows();
            if (selectie.isEmpty()) {
                idSelectat = -1;
                return;
            }

            int rand = selectie.at(0).row();
            idSelectat = model->data(model->index(rand, 0)).toInt();

            txtTitlu->setText(model->data(model->index(rand, 1)).toString());
            int rankMelodie = model->data(model->index(rand, 3)).toInt();
            sliderRank->setValue(rankMelodie);
            });

        QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
            if (idSelectat == -1) {
                QMessageBox::warning(this, "Avertisment", "Nu ai selectat nicio melodie!");
                return;
            }
            try {
                service.modificaMelodie(idSelectat, txtTitlu->text().toStdString(), sliderRank->value());
                incarcaDate();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare", e.what());
            }
            });

        QObject::connect(btnDelete, &QPushButton::clicked, [this]() {
            if (idSelectat == -1) {
                QMessageBox::warning(this, "Avertisment", "Nu ai selectat nicio melodie!");
                return;
            }
            try {
                service.stergeMelodie(idSelectat);
                incarcaDate();
                txtTitlu->clear();
                sliderRank->setValue(0);
            }
            catch (const exception& e) {
                QMessageBox::warning(this, "Eroare Stergere", e.what());
            }
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
        susLayout->addWidget(table, 6);

        QVBoxLayout* dreaptaLayout = new QVBoxLayout;

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("Titlu Nou:", txtTitlu);

        sliderRank->setRange(0, 10);
        sliderRank->setTickPosition(QSlider::TicksBelow);
        sliderRank->setTickInterval(1);

        QHBoxLayout* sliderLayout = new QHBoxLayout;
        sliderLayout->addWidget(sliderRank);
        sliderLayout->addWidget(lblRankValue);

        formLayout->addRow("Rank Nou:", sliderLayout);

        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnUpdate);
        dreaptaLayout->addWidget(btnDelete);
        dreaptaLayout->addStretch();

        susLayout->addLayout(dreaptaLayout, 4);

        mainLayout->addLayout(susLayout);
        mainLayout->addWidget(new QLabel("Repartizarea melodiilor in functie de Rank (0 - 10):"));
        mainLayout->addWidget(widgetDesen);

        connectSignals();
        incarcaDate();

        resize(950, 600);
        setWindowTitle("Gestiune Melodii");
    }
};