#pragma once
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>

#include "Service.h"

class UI : public QWidget {
private:
	Service& service;

	vector<Procesor> displayedProcesoare;
	vector<PlacaDeBaza> displayedPlaci;

	QListWidget* listaProcesoare = new QListWidget;
	QListWidget* listaPlaci = new QListWidget;

	QLineEdit* numePlaca = new QLineEdit;
	QLineEdit* socluPlaca = new QLineEdit;
	QLineEdit* pretPlaca = new QLineEdit;

	QPushButton* adaugaPlaca = new QPushButton("Adauga Placa");
	QPushButton* totalPret = new QPushButton("Calculeaza Pret");

	QLabel* totalLabel = new QLabel("Total: 0");

	int getSelectedProcesor() const {
		auto rows = listaProcesoare->selectionModel()->selectedRows();
		if (rows.isEmpty())
			return -1;

		return rows.at(0).row();
	}

	int getSelectedPlaca() {
		auto rows = listaPlaci->selectionModel()->selectedRows();
		if (rows.isEmpty())
			return -1;
		return rows.at(0).row();
	}

	void populateProcesor(vector<Procesor> procesoare) {
		displayedProcesoare = procesoare;
		listaProcesoare->clear();

		for (Procesor procesor : displayedProcesoare) {
			string text = procesor.getNume() + " | " + to_string(procesor.getNrThreaduri()) + " | " + procesor.getSocluProcesor() +
				" | " + to_string(procesor.getPret());
			auto* item = new QListWidgetItem(QString::fromStdString(text));
			listaProcesoare->addItem(item);
		}
	}

	void populatePlaci(vector<PlacaDeBaza> placi) {
		displayedPlaci= placi;
		listaPlaci->clear();

		for (PlacaDeBaza placa : displayedPlaci) {
			string text = placa.getNume() + " | " + placa.getSocluProcesor() +
				" | " + to_string(placa.getPret());
			auto* item = new QListWidgetItem(QString::fromStdString(text));
			listaPlaci->addItem(item);
		}
	}

	void connectSignals() {
		QObject::connect(adaugaPlaca, &QPushButton::clicked, [this]() {
			string nume = numePlaca->text().toStdString();
			string soclu = socluPlaca->text().toStdString();
			double pret;

			try {
				pret = stoi(pretPlaca->text().toStdString());
			}
			catch (...) {
				QMessageBox::warning(this, "Eroare", "Invalid Pret");
			}

			service.addPlacaDeBaza(nume, soclu, pret);

			populatePlaci(service.getPlaciDeBaza());
			});

		QObject::connect(listaProcesoare, &QListWidget::itemSelectionChanged, [this]() {
			int idx = getSelectedProcesor();
			if (idx == -1)
				return;

			Procesor selected = displayedProcesoare[idx];
			populatePlaci(service.filtrareSoclu(selected.getSocluProcesor()));
			});
		
		QObject::connect(totalPret, &QPushButton::clicked, [this]() {
			int procesorIdx = getSelectedProcesor();
			int placaIdx = getSelectedPlaca();

			if (procesorIdx == -1 || placaIdx == -1) {
				QMessageBox::warning(this, "Eroare", "Selecteaza un procesor si o placa");
				return;
			}

			double total = displayedProcesoare[procesorIdx].getPret() + displayedPlaci[placaIdx].getPret();

			totalLabel->setText("Total" + QString::number(total));

			});
	}

public:
	UI(Service& service) : service{ service } {
		auto* mainLayout = new QHBoxLayout(this);
		
		auto* leftLayout = new QVBoxLayout;
		auto* rightLayout = new QVBoxLayout;

		auto* formLayout = new QFormLayout;

		mainLayout->addLayout(leftLayout);
		mainLayout->addLayout(rightLayout);

		leftLayout->addWidget(listaProcesoare);

		formLayout->addRow("Nume", numePlaca);
		formLayout->addRow("Soclu", socluPlaca);
		formLayout->addRow("Pret", pretPlaca);

		rightLayout->addWidget(listaPlaci);
		rightLayout->addLayout(formLayout);
	
		rightLayout->addWidget(adaugaPlaca);
		rightLayout->addWidget(totalPret);
		rightLayout->addWidget(totalLabel);

		connectSignals();

		populateProcesor(service.getProcesoare());
		populatePlaci(service.getPlaciDeBaza());

		resize(900, 500);
	}
};