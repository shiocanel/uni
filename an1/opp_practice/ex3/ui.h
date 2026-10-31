#pragma once

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QComboBox>
#include <QLineEdit>
#include <QColor>

#include "service.h"
#include "detailsWindow.h"

using namespace std;

class UI : public QWidget {
private:
	Service& service;

	vector<Produs> displayedProduse;

	QListWidget* lista = new QListWidget;
	QComboBox* categorii = new QComboBox;
	QLineEdit* cauta = new QLineEdit;

	int getSelected() const {
		auto rows = lista->selectionModel()->selectedRows();
		if (!rows.isEmpty())
			return -1;

		return rows.at(0).row();
	}

	void populateList(vector<Produs> produse) {
		displayedProduse = produse;
		lista->clear();

		for (Produs& produs : displayedProduse) {
			string text = to_string(produs.getCodProdus()) + " | " + produs.getDenumire() + " | " + produs.getCategorie() + " | " +
				to_string(produs.getAnFabricatie()) + " | " + to_string(produs.getPret());

			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(text));
			
			if (produs.getAnFabricatie() >= 2020)
				item->setBackground(Qt::green);
			else if (produs.getAnFabricatie() >= 2015)
				item->setBackground(QColor(255, 165, 0));
			else if (produs.getAnFabricatie() >= 2010)
				item->setBackground(Qt::yellow);
			else
				item->setBackground(Qt::red);

			lista->addItem(item);
		}
	}

	void populateCategory() {
		categorii->clear();
		categorii->addItem("Toate");

		for (const auto& categorie : service.getCategorii())
			categorii->addItem(QString::fromStdString(categorie));
	}

	void refreshList() {
		string categorie = categorii->currentText().toStdString();
		string denumire = cauta->text().toStdString();

		auto ans = service.cautaSiFiltreaza(categorie, denumire);
		populateList(ans);
	}

	void connectSignals() {
		QObject::connect(categorii, &QComboBox::currentTextChanged, [this]() {
			refreshList();
			});

		QObject::connect(cauta, &QLineEdit::textChanged, [this]() {
			refreshList();
			});

		QObject::connect(lista, &QListWidget::itemClicked, [this](QListWidgetItem* item) {
			int row = lista->row(item);
			if (row < 0 || row >= static_cast<int>(displayedProduse.size()))
				return;

			DetailsWindow dialog(displayedProduse[row], this);
			dialog.exec();
			});
	}

public:
	UI(Service& service) : service{ service } {
		auto* mainLayout = new QVBoxLayout(this);
		auto* topLayout = new QHBoxLayout;

		cauta->setPlaceholderText("Cauta dupa denumire...");
		categorii->setMinimumWidth(180);

		topLayout->addWidget(categorii);
		topLayout->addWidget(cauta);

		mainLayout->addLayout(topLayout);
		mainLayout->addWidget(lista);

		connectSignals();
		populateCategory();
		refreshList();

		resize(900, 500);
	}
};