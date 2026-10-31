#pragma once
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLAyout>
#include <QPushButton>
#include <QMessageBox>

#include "service.h"

using namespace std;

class UI : public QWidget {
private:
	Service& service;

	vector<Masina> displayedMasini;

	QListWidget* lista = new QListWidget;
	QPushButton* sorteazaByNumar = new QPushButton("Sorteaza Numar");
	QPushButton* sorteazaByModel = new QPushButton("Sorteaza Model");
	QPushButton* nesortat = new QPushButton("Nesortat");

	int getSelected() const {
		auto rows = lista->selectionModel()->selectedRows();
		if (!rows.isEmpty())
			return -1;
		return rows.at(0).row();
	}

	void populateList(vector<Masina> masini) {
		displayedMasini = masini;
		lista->clear();

		for (Masina& masina : displayedMasini) {
			string text = to_string(masina.getNrMatricol()) + " | " + masina.getModel() + " | " + to_string(masina.getKmRulati());
			auto* item = new QListWidgetItem(QString::fromStdString(text));
			if (masina.getCuloare() == "rosu")
				item->setBackground(Qt::red);
			else if (masina.getCuloare() == "albastru")
				item->setBackground(Qt::blue);
			else if (masina.getCuloare() == "galben")
				item->setBackground(Qt::yellow);

			lista->addItem(item);
		}
	}

	void connectSignals() {
		QObject::connect(sorteazaByNumar, &QPushButton::clicked, [this]() {
			populateList(service.sorteazaByNrMatricol());
			});
		QObject::connect(sorteazaByModel, &QPushButton::clicked, [this]() {
			populateList(service.sorteazaByModel());
			});
		QObject::connect(nesortat, &QPushButton::clicked, [this]() {
			populateList(service.getAll());
			});
	}

public:
	UI(Service& service) : service{ service } {
		QHBoxLayout* mainLayout = new QHBoxLayout(this);
		QVBoxLayout* buttonLayout = new QVBoxLayout;

		mainLayout->addWidget(lista);
		mainLayout->addLayout(buttonLayout);

		buttonLayout->addWidget(sorteazaByModel);
		buttonLayout->addWidget(sorteazaByNumar);
		buttonLayout->addWidget(nesortat);

		populateList(service.getAll());
		connectSignals();

		resize(900, 500);
	}
};

