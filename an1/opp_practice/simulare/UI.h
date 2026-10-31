#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QToolTip>

#include "Service.h"

class UI : public QWidget {
private:
	Service& service;

	vector<Postare> displayedPostari;

	QListWidget* lista = new QListWidget;

	QPushButton* sortCreatorCresc = new QPushButton("Sorteaza Dupa Creator (Cresc)");
	QPushButton* sortCreatorDesc = new QPushButton("Sorteaza Dupa Creator (Descr)");
	QPushButton* sortPlatformaCresc = new QPushButton("Sorteaza Dupa Platforma (Cresc)");
	QPushButton* sortPlatformaDesc = new QPushButton("Sorteaza Dupa Platforma (Descr)");
	QPushButton* nesortat = new QPushButton("Nesortat");

	QLineEdit* codPostareEdit = new QLineEdit;
	QLineEdit* tipContinutEdit = new QLineEdit;

	/*
	functie care returneaza indexul elementului selectat din lista
	return : int
	*/
	int getSelected() const {
		auto rows = lista->selectionModel()->selectedRows();
		if (rows.isEmpty())
			return -1;
		return rows.at(0).row();
	}

	/*
	functie care populeaza lista din GUI dupa postari dat ca argument
	postari : vector<Postare>
	*/
	void populateList(vector<Postare> postari) {
		displayedPostari = postari;
		lista->clear();
		

		for (Postare postare : displayedPostari) {
			string text = to_string(postare.getCodPostare()) + " | " + postare.getCreator() + " | " + postare.getTipContinut() + " | " +
				postare.getPlatforma();
			auto* item = new QListWidgetItem(QString::fromStdString(text));

			item->setToolTip(QString::fromStdString(service.getDescrierePlatforma(postare.getPlatforma())));

			lista->addItem(item);
		}
	}

	/*
	functie care conecteaza butoanele, lineEditurile si tooltipurile cu un eveniment specific
	*/
	void connectSignals() {
		QObject::connect(sortCreatorCresc, &QPushButton::clicked, [this]() {
			populateList(service.sortCreatorCresc());
			});
		QObject::connect(sortCreatorDesc, &QPushButton::clicked, [this]() {
			populateList(service.sortCreatorDesc());
			});

		QObject::connect(sortPlatformaCresc, &QPushButton::clicked, [this]() {
			populateList(service.sortPlatformaCresc());
			});
		QObject::connect(sortPlatformaDesc, &QPushButton::clicked, [this]() {
			populateList(service.sortPlatformaDesc());
			});

		QObject::connect(nesortat, &QPushButton::clicked, [this]() {
			populateList(service.getAll());
			});

		QObject::connect(lista, &QListWidget::itemSelectionChanged, [this]() {
			//QMessageBox::warning(this, "fjdnsdifj", "dsfkjn");
			int idx = getSelected();
			if (idx == -1) {
				return;
			}

			try {
				Postare postare = displayedPostari[idx];
				codPostareEdit->setText(QString::fromStdString(to_string(postare.getCodPostare())));
				tipContinutEdit->setText(QString::fromStdString(postare.getTipContinut()));
			}
			catch (runtime_error& e) {
				QMessageBox::warning(this, "Eroare", e.what());
			}
			});
	}

public:
	/*
	Constructortul UI cu toate Layout urile 
	service : Service
	*/
	UI(Service& service) : service{ service } {
		auto* mainLayout = new QHBoxLayout(this);
		auto* rightLayout = new QVBoxLayout;

		mainLayout->addWidget(lista);
		mainLayout->addLayout(rightLayout);

		auto* formLayout = new QFormLayout;
		formLayout->addRow("Cod Postare", codPostareEdit);
		formLayout->addRow("Tip Continut", tipContinutEdit);
		rightLayout->addLayout(formLayout);

		rightLayout->addWidget(sortCreatorCresc);
		rightLayout->addWidget(sortCreatorDesc);

		rightLayout->addWidget(sortPlatformaCresc);
		rightLayout->addWidget(sortPlatformaDesc);

		rightLayout->addWidget(nesortat);

		connectSignals();
		populateList(service.getAll());

		resize(900, 500);
	}
};