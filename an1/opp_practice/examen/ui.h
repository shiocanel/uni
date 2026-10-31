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

    QLineEdit* txt_titlu = new QLineEdit;
    QSlider* slider_rank = new QSlider(Qt::Horizontal);
    QLabel* lblRankValue = new QLabel("0");

    QPushButton* btnUpdate = new QPushButton("Update Melodie");
    QPushButton* btnDelete = new QPushButton("Sterge Melodie");

    DesenBare* widgetDesen = new DesenBare;

    int idSelectat = -1;

    void incarcaDate() {
        /*
        face update la model si widget cu melodiile sortate si frecvente
        pre:
        post:
        */

        auto melodiiSortate = service.getMelodiiSortateDupaRank();
        auto frecvente = service.getFrecventeRank();

        model->setMelodii(melodiiSortate, frecvente);
        widgetDesen->setDate(frecvente);
    }

    void connectSignals() {
        /*
        functie care stabileste o legatra intre elementele de Ui si functionalitatile sale
        pre:
        post:
        */

        QObject::connect(slider_rank, &QSlider::valueChanged, [this](int val) {
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

            txt_titlu->setText(model->data(model->index(rand, 1)).toString());
            int rankMelodie = model->data(model->index(rand, 3)).toInt();
            slider_rank->setValue(rankMelodie);
            });

        QObject::connect(btnUpdate, &QPushButton::clicked, [this]() {
            if (idSelectat == -1) {
                QMessageBox::warning(this, "Eroarre", "Nu ai selectat nciciio melodie");
                return;
            }


            try {
                service.modificaMelodie(idSelectat, txt_titlu->text().toStdString(), slider_rank->value());
                incarcaDate();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroarte", e.what());
            }
            });

        QObject::connect(btnDelete, &QPushButton::clicked, [this]() {
            if (idSelectat == -1) {
                QMessageBox::warning(this, "Eroare", "Nu ai selectat nicio melodie");
                return;
            }

            try {
                service.stergeMelodie(idSelectat);
                incarcaDate();
                txt_titlu->clear();
                slider_rank->setValue(0);
            }
            catch (const exception& e) {
                QMessageBox::warning(this, "Eroare stergere!!!", e.what());
            }
            });
    }

public:
    UI(Service& service) : service{ service } {
        /*
        constructor pentru UI care populeaza fereastra cu toate elementele cerute
        pre:
        post:
        */

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        QHBoxLayout* susLayout = new QHBoxLayout;

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //table->setModel(model);

        susLayout->addWidget(table, 6);

        QVBoxLayout* dreaptaLayout = new QVBoxLayout;

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("Titlu nou:", txt_titlu);

        slider_rank->setRange(0, 10);
        slider_rank->setTickPosition(QSlider::TicksBelow);
        slider_rank->setTickInterval(1);

        QHBoxLayout* sliderLayout = new QHBoxLayout;
        sliderLayout->addWidget(slider_rank);
        sliderLayout->addWidget(lblRankValue);

        formLayout->addRow("Rank nou:", sliderLayout);
        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnUpdate);
        dreaptaLayout->addWidget(btnDelete);
        dreaptaLayout->addStretch();

        susLayout->addLayout(dreaptaLayout, 4);

        mainLayout->addLayout(susLayout);
        mainLayout->addWidget(new QLabel("Repartizarea melodiilor"));
        mainLayout->addWidget(widgetDesen);

        connectSignals();
        incarcaDate();

        resize(950, 600);
        setWindowTitle("Gestiune Melodii");
    }
};