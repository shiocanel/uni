#pragma once
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>

#include "Service.h"

class UI : public QWidget {
private:
	Service& service;

	vector<Apartament> displayedApartamente;

	QListWidget* lista = new QListWidget;
	
	QPushButton* sterge = new QPushButton("Sterge Apartament");
	QPushButton* filtreazaSuprafata = new QPushButton("Filtreaza Suprafata");
	QPushButton* filtreazaPret = new QPushButton("Filtreaza Pret");

	QLineEdit* lowSuprafata = new QLineEdit;
	QLineEdit* upSuprafata = new QLineEdit;
	QLineEdit* lowPret = new QLineEdit;
	QLineEdit* upPret = new QLineEdit;

	int lowSupr = -1, upSupr = -1;
	int lowPre = -1, upPre = -1;

	int getSelected() const {
		auto rows = lista->selectionModel()->selectedRows();
		if (rows.isEmpty())
			return -1;
		return rows.at(0).row();
	}

	void populateList(vector<Apartament> apartamente) {
		displayedApartamente = apartamente;
		lista->clear();

		for (Apartament apartament : displayedApartamente) {
			string text = to_string(apartament.getCodApartament()) + " | " + apartament.getStrada() + " | " +
				to_string(apartament.getSuprafata()) + " | " + to_string(apartament.getPret());

			auto* item = new QListWidgetItem(QString::fromStdString(text));
			lista->addItem(item);
		}
	}

	void connectSignals() {
		QObject::connect(sterge, &QPushButton::clicked, [this]() {
			int idx = getSelected();

			if(idx == -1){
				QMessageBox::warning(this, "Eroare", "Nu ai selectat apartamentul");
				return;
			}

			try {
				service.stergeApartament(displayedApartamente[idx].getCodApartament());
				populateList(service.getAll());
			}
			catch (runtime_error& e) {
				QMessageBox::warning(this, "Eroare", e.what());
			}
			});

		QObject::connect(filtreazaSuprafata, &QPushButton::clicked, [this]() {
			try {
				lowSupr = stoi(lowSuprafata->text().toStdString());
				upSupr = stoi(upSuprafata->text().toStdString());

				populateList(service.filtreazaPretSuprafata(lowPre, upPre, lowSupr, upSupr));
			}
			catch (runtime_error& e) {
				QMessageBox::warning(this, "Eroare", e.what());
			}
			});

		QObject::connect(filtreazaPret, &QPushButton::clicked, [this]() {
			try {
				lowPre = stoi(lowPret->text().toStdString());
				upPre = stoi(upPret->text().toStdString());

				populateList(service.filtreazaPretSuprafata(lowPre, upPre, lowSupr, upSupr));
			}
			catch (runtime_error& e) {
				QMessageBox::warning(this, "Eroare", e.what());
			}
			});
	}

public:
	UI(Service& service) : service{ service } {
		auto* mainLayout = new QHBoxLayout(this);
		
		auto* rightLayout = new QVBoxLayout;

		mainLayout->addWidget(lista);
		mainLayout->addLayout(rightLayout);

		rightLayout->addWidget(sterge);

		auto* form1 = new QFormLayout;
		form1->addRow("Suprafata1", lowSuprafata);
		form1->addRow("Supeafata2", upSuprafata);
		form1->addWidget(filtreazaSuprafata);

		rightLayout->addLayout(form1);

		auto* form2 = new QFormLayout;
		form2->addRow("Pret1", lowPret);
		form2->addRow("Pret2", upPret);
		form2->addWidget(filtreazaPret);

		rightLayout->addLayout(form2);

		populateList(service.getAll());
		connectSignals();

		resize(900, 500);
	}
};