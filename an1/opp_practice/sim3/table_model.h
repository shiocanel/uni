#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "joc.h"

class MyTableModel : public QAbstractTableModel {
private:
    std::vector<Joc> jocuri;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setJocuri(const std::vector<Joc>& newJocuri) {
        beginResetModel();
        jocuri = newJocuri;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return jocuri.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& j = jocuri[index.row()];
        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return j.getId();
            if (index.column() == 1) return j.getDim();
            if (index.column() == 2) return QString::fromStdString(j.getTabla());
            if (index.column() == 3) return QString::fromStdString(j.getJucator());
            if (index.column() == 4) return QString::fromStdString(j.getStare());
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Dimensiune";
            if (section == 2) return "Tabla";
            if (section == 3) return "Urmatorul";
            if (section == 4) return "Stare";
        }
        return QVariant();
    }
};