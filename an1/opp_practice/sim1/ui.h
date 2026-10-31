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

	QPushButton* btnIntinerire = new QPushButton("Intinerire");
	QPushButton* btnImbatranire = new QPushButton("Imbatranire");
	QPushButton* btnSterge = new QPushButton("Sterge");
	QPushButton* btnUndo = new QPushButton("Undo");
	QPushButton* btnRedo = new QPushButton("Redo");

	void reloadData() {
		model->setStudenti(service.getSortedByVarsta());
	}

	void connectSignals() {
		QObject::connect(btnIntinerire, &QPushButton::clicked, [this]() {
			service.modificaVarsta(-1);
			reloadData();
			});

		QObject::connect(btnImbatranire, &QPushButton::clicked, [this]() {
			service.modificaVarsta(1);
			reloadData();
			});

		QObject::connect(btnSterge, &QPushButton::clicked, [this]() {
			auto selectedRows = table->selectionModel()->selectedRows();
			if (selectedRows.isEmpty()) {
				QMessageBox::warning(this, "Avertisment", "Nu ai selectat nici un student");
				return;
			}

			vector<int> deSters;
			for (const auto& index : selectedRows) {
				int nrMatricol = model->data(model->index(index.row(), 0)).toInt();
				deSters.push_back(nrMatricol);
			}

			service.stergeStudenti(deSters);
			reloadData();
			});

		QObject::connect(btnUndo, &QPushButton::clicked, [this]() {
			try {
				service.undo();
				reloadData();
			}
			catch (const exception& e) {
				QMessageBox::critical(this, "Eroare Undo", e.what());
			}
			});

		QObject::connect(btnRedo, &QPushButton::clicked, [this]() {
			try {
				service.redo();
				reloadData();
			}
			catch (const exception& e) {
				QMessageBox::critical(this, "Eroare Redo", e.what());
			}
			});
	}
public:
	UI(Service& service) : service{service} {
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		QVBoxLayout* buttonsLayout = new QVBoxLayout;

		table->setModel(model);
		table->setSelectionBehavior(QAbstractItemView::SelectRows);
		table->setSelectionMode(QAbstractItemView::ExtendedSelection); // Selectie multipla activata
		table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

		mainLayout->addWidget(table);
		mainLayout->addLayout(buttonsLayout);

		buttonsLayout->addWidget(btnIntinerire);
		buttonsLayout->addWidget(btnImbatranire);
		buttonsLayout->addWidget(btnSterge);
		buttonsLayout->addStretch();
		buttonsLayout->addWidget(btnUndo);
		buttonsLayout->addWidget(btnRedo);

		connectSignals();
		reloadData();

		resize(800, 400);
		setWindowTitle("Gestiune Studenti");
	}
};