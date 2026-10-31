#pragma once
#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
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

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtDim = new QLineEdit;
    QLineEdit* txtTabla = new QLineEdit;
    QLineEdit* txtJucator = new QLineEdit;
    QLineEdit* txtStare = new QLineEdit;

    QPushButton* btnAdauga = new QPushButton("Adauga Joc Nou");
    QPushButton* btnModifica = new QPushButton("Modifica Joc Existent");

    QWidget* widgetTabla = new QWidget;
    QGridLayout* layoutTabla = new QGridLayout(widgetTabla);

    int idJocCurent = -1;

    void incarcaTabel() {
        model->setJocuri(service.getJocuriSortate());
    }

    void deseneazaTablaDeJoc(int id) {
        QLayoutItem* item;
        while ((item = layoutTabla->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        try {
            Joc joc = service.getJoc(id);
            int dim = joc.getDim();
            string tabla = joc.getTabla();

            for (int i = 0; i < dim; ++i) {
                for (int j = 0; j < dim; ++j) {
                    int indexString = i * dim + j;
                    char valoare = tabla[indexString];

                    QPushButton* buton = new QPushButton();
                    buton->setFixedSize(60, 60);

                    if (valoare == 'X' || valoare == 'O') {
                        buton->setText(QString(valoare));
                    }

                    QObject::connect(buton, &QPushButton::clicked, [this, id, indexString]() {
                        try {
                            service.joacaMutare(id, indexString);
                            incarcaTabel();
                            deseneazaTablaDeJoc(id);

                            selecteazaLinieDupaId(id);
                        }
                        catch (const exception& e) {
                            QMessageBox::warning(this, "Eroare Mutare", e.what());
                        }
                        });

                    layoutTabla->addWidget(buton, i, j);
                }
            }
        }
        catch (...) {
            // Jocul nu exista sau a aparut o eroare, oprim desenarea
        }
    }

    void selecteazaLinieDupaId(int id) {
        for (int r = 0; r < model->rowCount(); ++r) {
            int rowId = model->data(model->index(r, 0)).toInt();
            if (rowId == id) {
                table->selectRow(r);
                break;
            }
        }
    }

    void connectSignals() {
        QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
            try {
                service.adaugaJoc(txtId->text().toInt(), txtDim->text().toInt(),
                    txtTabla->text().toStdString(), txtJucator->text().toStdString());
                incarcaTabel();
            }
            catch (const exception& e) { QMessageBox::critical(this, "Eroare", e.what()); }
            });

        QObject::connect(btnModifica, &QPushButton::clicked, [this]() {
            try {
                int id = txtId->text().toInt();
                service.modificaJoc(id, txtDim->text().toInt(), txtTabla->text().toStdString(),
                    txtJucator->text().toStdString(), txtStare->text().toStdString());
                incarcaTabel();
                if (idJocCurent == id) deseneazaTablaDeJoc(id);
            }
            catch (const exception& e) { QMessageBox::critical(this, "Eroare", e.what()); }
            });

        QObject::connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
            auto selectie = table->selectionModel()->selectedRows();
            if (selectie.isEmpty()) return;

            int rand = selectie.at(0).row();
            idJocCurent = model->data(model->index(rand, 0)).toInt();

            txtId->setText(model->data(model->index(rand, 0)).toString());
            txtDim->setText(model->data(model->index(rand, 1)).toString());
            txtTabla->setText(model->data(model->index(rand, 2)).toString());
            txtJucator->setText(model->data(model->index(rand, 3)).toString());
            txtStare->setText(model->data(model->index(rand, 4)).toString());

            deseneazaTablaDeJoc(idJocCurent);
            });
    }

public:
    UI(Service& service) : service{ service } {
        QHBoxLayout* mainLayout = new QHBoxLayout(this);
        QVBoxLayout* dreaptaLayout = new QVBoxLayout;

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        mainLayout->addWidget(table, 2);

        QFormLayout* formLayout = new QFormLayout;
        formLayout->addRow("ID:", txtId);
        formLayout->addRow("Dimensiune:", txtDim);
        formLayout->addRow("Tabla (ex. X-O...):", txtTabla);
        formLayout->addRow("Jucator (X/O):", txtJucator);
        formLayout->addRow("Stare:", txtStare);

        dreaptaLayout->addLayout(formLayout);
        dreaptaLayout->addWidget(btnAdauga);
        dreaptaLayout->addWidget(btnModifica);

        dreaptaLayout->addSpacing(30);
        dreaptaLayout->addWidget(widgetTabla);
        dreaptaLayout->addStretch();

        mainLayout->addLayout(dreaptaLayout, 1);

        connectSignals();
        incarcaTabel();

        resize(1000, 600);
        setWindowTitle("Examen - Joc TicTacToe");
    }
};