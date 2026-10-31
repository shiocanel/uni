#pragma once
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#include <QHeaderView>
#include <QLabel>

#include "service.h"
#include "table_model.h"
#include "roti_widget.h"

class UI : public QWidget {
private:
    Service& service;

    QTableView* table = new QTableView;
    MyTableModel* model = new MyTableModel;

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtDenumire = new QLineEdit;
    QLineEdit* txtTip = new QLineEdit;
    QLineEdit* txtNumarRoti = new QLineEdit;
    QPushButton* btnAdauga = new QPushButton("Adauga Tractor");

    QComboBox* comboFiltru = new QComboBox;

    DesenRoti* widgetRoti = new DesenRoti;

    int idSelectat = -1;

    void incarcaTabel() {
        model->setTractoare(service.getTractoareSortate());
    }

    void incarcaComboBox() {
        comboFiltru->clear();
        comboFiltru->addItem("--- Neselectat ---");
        for (const auto& tip : service.getTipuriDistincte()) {
            comboFiltru->addItem(QString::fromStdString(tip));
        }
    }

    void actualizeazaDesen(int numarRotiSelectat) {
        widgetRoti->setSate(numarRotiSelectat, [this]() {
            if (idSelectat != -1) {
                service.decrementRoti(idSelectat);
                incarcaTabel();

                for (int r = 0; r < model->rowCount(); ++r) {
                    if (model->data(model->index(r, 0)).toInt() == idSelectat) {
                        int rotiActualizate = model->data(model->index(r, 3)).toInt();
                        actualizeazaDesen(rotiActualizate);
                        table->selectRow(r); 
                        break;
                    }
                }
            }
            });
    }

    void connectSignals() {
        QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
            try {
                service.adaugaTractor(
                    txtId->text().toInt(),
                    txtDenumire->text().toStdString(),
                    txtTip->text().toStdString(),
                    txtNumarRoti->text().toInt()
                );
                incarcaTabel();
                incarcaComboBox();
            }
            catch (const ValidatorException& e) {
                QMessageBox::critical(this, "Erori Validare", e.what());
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare", e.what());
            }
            });

        QObject::connect(comboFiltru, &QComboBox::currentTextChanged, [this](const QString& text) {
            model->setTipSelectat(text.toStdString());
            });

        QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
            auto selectie = table->selectionModel()->selectedRows();
            if (selectie.isEmpty()) {
                idSelectat = -1;
                actualizeazaDesen(0);
                return;
            }

            int rand = selectie.at(0).row();
            idSelectat = model->data(model->index(rand, 0)).toInt();
            int nrRoti = model->data(model->index(rand, 3)).toInt();

            actualizeazaDesen(nrRoti);
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
        formLayout->addRow("ID:", txtId);
        formLayout->addRow("Denumire:", txtDenumire);
        formLayout->addRow("Tip:", txtTip);
        formLayout->addRow("Nr. Roti:", txtNumarRoti);

        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnAdauga);

        dreaptaLayout->addSpacing(20);
        dreaptaLayout->addWidget(new QLabel("Coloreaza tractoare de tipul:"));
        dreaptaLayout->addWidget(comboFiltru);
        dreaptaLayout->addStretch();

        susLayout->addLayout(dreaptaLayout, 1);

        mainLayout->addLayout(susLayout);

        mainLayout->addWidget(new QLabel("Roti Tractor Selectat (Click pentru a scadea cate 2):"));
        mainLayout->addWidget(widgetRoti);

        connectSignals();
        incarcaTabel();
        incarcaComboBox();

        resize(950, 500);
        setWindowTitle("Gestiune Tractoare");
    }
};