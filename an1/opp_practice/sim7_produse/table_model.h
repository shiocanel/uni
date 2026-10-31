#pragma once
#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>
#include <vector>
#include "produs.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Produs> produse;
    double pragFiltruSlider = 0.0;

    int numaraVocale(const std::string& str) const {
        int count = 0;
        std::string vocale = "aeiouAEIOU";
        for (char c : str) {
            if (vocale.find(c) != std::string::npos) count++;
        }
        return count;
    }

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setProduse(const std::vector<Produs>& p, double sliderPrag = -1) {
        beginResetModel();
        produse = p;
        if (sliderPrag != -1) pragFiltruSlider = sliderPrag;
        endResetModel();
    }

    void schimbaPragFiltru(double sliderPrag) {
        beginResetModel();
        pragFiltruSlider = sliderPrag;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return produse.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& p = produse[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return p.getId();
            if (index.column() == 1) return QString::fromStdString(p.getNume());
            if (index.column() == 2) return QString::fromStdString(p.getTip());
            if (index.column() == 3) return p.getPret();
            if (index.column() == 4) return numaraVocale(p.getNume());
        }

        if (role == Qt::BackgroundRole) {
            if (pragFiltruSlider > 0 && p.getPret() <= pragFiltruSlider) {
                return QBrush(Qt::red);
            }
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Nume";
            if (section == 2) return "Tip";
            if (section == 3) return "Pret";
            if (section == 4) return "Nr. Vocale";
        }
        return QVariant();
    }
};