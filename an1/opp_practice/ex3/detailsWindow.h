#pragma once
#include <QDialog>
#include <QFormLayout>
#include <QLabel>

#include "produs.h"

class DetailsWindow : public QDialog {
public:
	DetailsWindow(Produs& produs, QWidget* parent = nullptr) {
		setWindowTitle("Detalii Produs");

		auto* layout = new QFormLayout(this);

		layout->addRow("Cod Produs: ", new QLabel(QString::number(produs.getCodProdus())));
		layout->addRow("Denumire: ", new QLabel(QString::fromStdString(produs.getDenumire())));
		layout->addRow("Categorie: ", new QLabel(QString::fromStdString(produs.getCategorie())));
		layout->addRow("An Fabricatie: ", new QLabel(QString::number(produs.getAnFabricatie())));
		layout->addRow("Pret: ", new QLabel(QString::number(produs.getPret())));

		setLayout(layout);

		resize(350, 200);
	}
};