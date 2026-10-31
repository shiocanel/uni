#pragma once
#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>
#include <vector>
#include "masina.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Masina> masini;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setMasini(const std::vector<Masina>& newMasini) {
        beginResetModel();
        masini = newMasini;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return masini.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();

        const auto& m = masini[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return QString::fromStdString(m.getNrInmatriculare());
            if (index.column() == 1) return QString::fromStdString(m.getDenumire());
            if (index.column() == 2) return m.getAnFabricatie();
            if (index.column() == 3) return QString::fromStdString(m.getTip());
        }

        if (role == Qt::BackgroundRole) {
            if (m.getTip() == "sedan") return QBrush(QColor(173, 216, 230)); // Albastru
            if (m.getTip() == "hatch") return QBrush(QColor(144, 238, 144)); // Verde
            if (m.getTip() == "suv")   return QBrush(QColor(255, 182, 193)); // Rosu/Roz
            if (m.getTip() == "van")   return QBrush(QColor(255, 255, 224)); // Galben
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "Nr. Inmatriculare";
            if (section == 1) return "Denumire";
            if (section == 2) return "An Fabricatie";
            if (section == 3) return "Tip";
        }
        return QVariant();
    }
};