#pragma once
#include <vector>
#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>

#include "student.h"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
	vector<Student> studenti;

public:
	MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {
	
	}

	void setStudenti(const vector<Student>& newstudenti) {
		beginResetModel();
		studenti = newstudenti;
		endResetModel();
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return studenti.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (!index.isValid())
			return QVariant();

		const auto& s = studenti[index.row()];

		if (role == Qt::DisplayRole) {
			if (index.column() == 0)
				return s.getNrMatrcol();
			if (index.column() == 1)
				return QString::fromStdString(s.getNume());
			if (index.column() == 2)
				return s.getVarsta();
			if (index.column() == 3)
				return QString::fromStdString(s.getFacultate());
		}

		if (role == Qt::BackgroundRole) {
			if (s.getFacultate() == "mate") return QBrush(QColor(173, 216, 230)); // Albastru deschis
			if (s.getFacultate() == "info") return QBrush(QColor(144, 238, 144)); // Verde deschis
			if (s.getFacultate() == "mate-info") return QBrush(QColor(255, 255, 224)); // Galben deschis
			if (s.getFacultate() == "ai") return QBrush(QColor(255, 182, 193)); // Rosu deschis
		}

		return QVariant();
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			if (section == 0) return "Nr. Matricol";
			if (section == 1) return "Nume";
			if (section == 2) return "Varsta";
			if (section == 3) return "Facultate";
		}
		return QVariant();
	}
};