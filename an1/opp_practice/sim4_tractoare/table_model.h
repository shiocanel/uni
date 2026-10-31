#pragma once
#include <QAbstractTableModel>
#include <QColor>
#include <QBrush>
#include <vector>
#include <map>
#include "tractor.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Tractor> tractoare;
    std::map<std::string, int> countPerTip;
    std::string tipSelectatColorare;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setTractoare(const std::vector<Tractor>& newTractoare) {
        beginResetModel();
        tractoare = newTractoare;

        countPerTip.clear();
        for (const auto& t : tractoare) countPerTip[t.getTip()]++;

        endResetModel();
    }

    void setTipSelectat(const std::string& tip) {
        beginResetModel();
        tipSelectatColorare = tip;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return tractoare.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& t = tractoare[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return t.getId();
            if (index.column() == 1) return QString::fromStdString(t.getDenumire());
            if (index.column() == 2) return QString::fromStdString(t.getTip());
            if (index.column() == 3) return t.getNumarRoti();
            if (index.column() == 4) return countPerTip.at(t.getTip());
        }

        if (role == Qt::BackgroundRole) {
            if (t.getTip() == tipSelectatColorare) return QBrush(Qt::red);
        }

        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Denumire";
            if (section == 2) return "Tip";
            if (section == 3) return "Nr. Roti";
            if (section == 4) return "Total Acelasi Tip";
        }
        return QVariant();
    }
};