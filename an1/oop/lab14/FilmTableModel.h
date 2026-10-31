#pragma once

#include <QAbstractTableModel>
#include <vector>

#include "Film.h"

class FilmTableModel : public QAbstractTableModel {
private:
    std::vector<Film> films;

public:
    explicit FilmTableModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setFilms(std::vector<Film> newFilms);

    const Film& filmAt(int row) const;
};