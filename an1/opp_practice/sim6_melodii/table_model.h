#pragma once
#include <QAbstractTableModel>
#include <vector>
#include <map>
#include "melodie.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Melodie> melodii;
    std::map<std::string, int> countArtist;
    std::map<std::string, int> countGen;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setDate(const std::vector<Melodie>& m, const std::map<std::string, int>& ca, const std::map<std::string, int>& cg) {
        beginResetModel();
        melodii = m;
        countArtist = ca;
        countGen = cg;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 6;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& m = melodii[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return m.getId();
            if (index.column() == 1) return QString::fromStdString(m.getTitlu());
            if (index.column() == 2) return QString::fromStdString(m.getArtist());
            if (index.column() == 3) return QString::fromStdString(m.getGen());
            if (index.column() == 4) return countArtist.at(m.getArtist());
            if (index.column() == 5) return countGen.at(m.getGen());
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Titlu";
            if (section == 2) return "Artist";
            if (section == 3) return "Gen";
            if (section == 4) return "Acelasi Artist";
            if (section == 5) return "Acelasi Gen";
        }
        return QVariant();
    }
};