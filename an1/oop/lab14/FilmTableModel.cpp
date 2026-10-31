#include "FilmTableModel.h"

#include <QString>
#include <stdexcept>

FilmTableModel::FilmTableModel(QObject* parent)
    : QAbstractTableModel(parent) {
}

int FilmTableModel::rowCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return static_cast<int>(films.size());
}

int FilmTableModel::columnCount(const QModelIndex& parent) const {
    if (parent.isValid()) {
        return 0;
    }
    return 4;
}

QVariant FilmTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) {
        return {};
    }

    if (index.row() < 0 || index.row() >= static_cast<int>(films.size())) {
        return {};
    }

    const auto& film = films[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return QString::fromStdString(film.getTitlu());
        case 1: return QString::fromStdString(film.getGen());
        case 2: return film.getAnAparitie();
        case 3: return QString::fromStdString(film.getActorPrincipal());
        default: return {};
        }
    }

    return {};
}

QVariant FilmTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Titlu";
        case 1: return "Gen";
        case 2: return "An";
        case 3: return "Actor principal";
        default: return {};
        }
    }

    return section + 1;
}

Qt::ItemFlags FilmTableModel::flags(const QModelIndex& index) const {
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

void FilmTableModel::setFilms(std::vector<Film> newFilms) {
    beginResetModel();
    films = std::move(newFilms);
    endResetModel();
}

const Film& FilmTableModel::filmAt(int row) const {
    if (row < 0 || row >= static_cast<int>(films.size())) {
        throw std::out_of_range("Rand invalid.");
    }
    return films[row];
}