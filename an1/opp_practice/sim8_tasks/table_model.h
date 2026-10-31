#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "task.h"

class TaskTableModel : public QAbstractTableModel {
private:
    std::vector<Task> taskuri;

public:
    TaskTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {}

    void setDate(const std::vector<Task>& t) {
        beginResetModel();
        taskuri = t;
        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return taskuri.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid()) return QVariant();
        const auto& t = taskuri[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0) return t.getId();
            if (index.column() == 1) return QString::fromStdString(t.getDescriere());
            if (index.column() == 2) return QString::fromStdString(t.getStare());
            if (index.column() == 3) return (int)t.getProgramatori().size();
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) return "ID";
            if (section == 1) return "Descriere";
            if (section == 2) return "Stare";
            if (section == 3) return "Nr. Programatori";
        }
        return QVariant();
    }
};