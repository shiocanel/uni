#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QHeaderView>
#include <QComboBox>
#include <QLabel>
#include <sstream>

#include "service.h"
#include "table_model.h"
#include "state_window.h"

class UI : public QWidget, public Observer {
private:
    Service& service;

    QTableView* table = new QTableView;
    TaskTableModel* model = new TaskTableModel;

    QLineEdit* txtSearch = new QLineEdit;

    QLineEdit* txtId = new QLineEdit;
    QLineEdit* txtDesc = new QLineEdit;
    QComboBox* cbStare = new QComboBox;
    QLineEdit* txtProgs = new QLineEdit;
    QPushButton* btnAdauga = new QPushButton("Adauga Task");

    std::vector<StateWindow*> ferestreSecundare;

    void incarcaDate() {
        model->setDate(service.getTasksFilteredAndSorted(txtSearch->text().toStdString()));
    }

    std::vector<std::string> getProgramatoriList(const std::string& str) {
        std::vector<std::string> res;
        std::stringstream ss(str);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty()) res.push_back(token);
        }
        return res;
    }

public:
    UI(Service& srv) : service{ srv } {
        QHBoxLayout* mainLayout = new QHBoxLayout(this);

        QVBoxLayout* stangaLayout = new QVBoxLayout;
        stangaLayout->addWidget(new QLabel("Cautare dupa programator:"));
        stangaLayout->addWidget(txtSearch);

        table->setModel(model);
        table->setSelectionBehavior(QAbstractItemView::SelectRows);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        stangaLayout->addWidget(table);

        mainLayout->addLayout(stangaLayout, 2);

        QVBoxLayout* dreaptaLayout = new QVBoxLayout;
        QFormLayout* form = new QFormLayout;

        form->addRow("ID:", txtId);
        form->addRow("Descriere:", txtDesc);

        cbStare->addItems({ "open", "inprogress", "closed" });
        form->addRow("Stare:", cbStare);

        txtProgs->setPlaceholderText("Ex: Ion,Vasile,Ana");
        form->addRow("Programatori:", txtProgs);

        dreaptaLayout->addLayout(form);
        dreaptaLayout->addWidget(btnAdauga);
        dreaptaLayout->addStretch();

        mainLayout->addLayout(dreaptaLayout, 1);

        QObject::connect(txtSearch, &QLineEdit::textChanged, [this]() {
            incarcaDate();
            });

        QObject::connect(btnAdauga, &QPushButton::clicked, [this]() {
            try {
                service.adaugaTask(
                    txtId->text().toInt(),
                    txtDesc->text().toStdString(),
                    cbStare->currentText().toStdString(),
                    getProgramatoriList(txtProgs->text().toStdString())
                );
                txtId->clear(); txtDesc->clear(); txtProgs->clear();
            }
            catch (const exception& e) {
                QMessageBox::critical(this, "Eroare validare", e.what());
            }
            });

        ferestreSecundare.push_back(new StateWindow(service, "open"));
        ferestreSecundare.push_back(new StateWindow(service, "inprogress"));
        ferestreSecundare.push_back(new StateWindow(service, "closed"));

        for (auto fw : ferestreSecundare) fw->show();

        service.addObserver(this);
        incarcaDate();

        resize(800, 500);
        setWindowTitle("Fereastra Principala - Gestiune Task-uri");
    }

    void update() override {
        incarcaDate();
    }

    ~UI() {
        service.removeObserver(this);
        for (auto fw : ferestreSecundare) delete fw;
    }
};