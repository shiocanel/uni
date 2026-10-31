#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "melodie.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Melodie> melodii;
    std::vector<int> rankCount;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {
        rankCount.resize(11, 0);
    }

    void setMelodii(const std::vector<Melodie>& noiMelodii, const std::vector<int>& noiFrecvente) {
        beginResetModel();
        melodii = noiMelodii;
        rankCount = noiFrecvente;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& m = melodii[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return m.getId();
            if (index.column() == 1) return QString::fromStdString(m.getTitlu());
            if (index.column() == 2) return QString::fromStdString(m.getArtist());
            if (index.column() == 3) return m.getRank();
            if (index.column() == 4) return rankCount[m.getRank()];
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Titlu";
            if (section == 2) return "Artist";
            if (section == 3) return "Rank";
            if (section == 4) return "Acelasi Rank (Count)";
        }
        return QVariant();
    }
};