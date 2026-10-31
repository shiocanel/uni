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
#include <QSlider>
#include <QLabel>
#include <map>

#include "service.h"
#include "table_model.h"
#include "tip_window.h"

class UI : public QWidget {
private:
    Service& service;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel;

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtNume = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtPret = new QLineEdit;

    QPushButton* btnAdauga = new QPushButton("Adauga Produs");

    QSlider* sliderPret = new QSlider(Qt::Horizontal);
    QLabel* lblSliderValue = new QLabel("0");

    std::map<std::string, TipWindow*> ferestreTip;

    void setupFerestreTip() {
        auto tipuri = service.getTipuriDistincte();
        for (const auto& tip : tipuri) {
            ferestreTip[tip] = new TipWindow(tip, service);
            ferestreTip[tip]->show();
        }
    }

    void deschideFereastraDacaENoua(const std::string& tip) {
        if (ferestreTip.find(tip) == ferestreTip.end()) {
            ferestreTip[tip] = new TipWindow(tip, service);
            ferestreTip[tip]->show();
        }
    }

    void incarcaTabel() {
        model->setProduse(service.getProduseSortate());
    }

    void connectSignals() {
        QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
            try {
                std::string tipNou = txtTip->text().toStdString();
                service.adaugaProdus(
                    txtId->text().toInt(),
                    txtNume->text().toStdString(),
                    tipNou,
                    txtPret->text().toDouble()
                );

                incarcaTabel();
                deschideFereastraDacaENoua(tipNou);

                txtId->clear(); txtNume->clear(); txtTip->clear(); txtPret->clear();
            }
            catch (const ValidatorException& e) {
                QMessageBox::critical(this, "Erori Validare", e.what());
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare", e.what());
            }
            });

        QObject::connect(sliderPret, &QSlider::valueChanged, [this](int val) {
            lblSliderValue->setText(QString::number(val));
            model->schimbaPragFiltru(static_cast<double>(val));
            });
    }

public:
    UI(Service& service) : service{ service } {
        QHBoxLayout* mainLayout = new QHBoxLayout(this);

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        mainLayout->addWidget(table, 6);

        QVBoxLayout* dreaptaLayout = new QVBoxLayout;

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("ID:", txtId);
        formLayout->addRow("Nume:", txtNume);
        formLayout->addRow("Tip:", txtTip);
        formLayout->addRow("Pret:", txtPret);

        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnAdauga);

        dreaptaLayout->addSpacing(30);
        dreaptaLayout->addWidget(new QLabel("Filtreaza / Coloreaza Produse cu pret <="));

        sliderPret->setRange(1, 100);
        sliderPret->setTickPosition(QSlider::TicksBelow);
        sliderPret->setTickInterval(10);

        QHBoxLayout* sliderLayout = new QHBoxLayout;
        sliderLayout->addWidget(sliderPret);
        sliderLayout->addWidget(lblSliderValue);
        dreaptaLayout->addLayout(sliderLayout);

        dreaptaLayout->addStretch();
        mainLayout->addLayout(dreaptaLayout, 4);

        connectSignals();
        incarcaTabel();

        setupFerestreTip();

        resize(900, 500);
        setWindowTitle("Gestiune Produse");
    }

    ~UI() {
        for (auto& pair : ferestreTip) {
            delete pair.second;
        }
    }
};