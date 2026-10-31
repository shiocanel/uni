#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "melodie.h"

using namespace std;

class MyTableModel : public QAbstractTableModel {
private:
    vector<Melodie> melodii;
    vector<int> rankCount;

public:
    MyTableModel(QObject* parent = nullptr) : QAbstractTableModel(parent) {
        rankCount.resize(11, 0);
    }

    void setMelodii(const vector<Melodie>& noiMelodii, const vector<int>& noiFrecvente) {
        /*
        functie care updatteaza melodiile si rankcount-ul
        pre:
        post: melodii si rankCount sunt update-ate
        */

        beginResetModel();
        
        melodii = noiMelodii;
        rankCount = noiFrecvente;

        endResetModel();
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        /*
        functie override care seteaza numarul de randuri = cate melodii avem
        pre:
        post:
        */

        return melodii.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        /*
        functie override care seteaza numarul de coloana = 5
        pre:
        post:
        */

        return 5;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        /*
        functie care completeaza randul cu date din vectorul melodii
        pre: 
        post: afiseaza datele din melodii[index.row()]
        */

        if (!index.isValid()) 
            return QVariant();

        const auto& m = melodii[index.row()];

        if (role == Qt::DisplayRole) {
            if (index.column() == 0)
                return m.getId();
            if (index.column() == 1) 
                return QString::fromStdString(m.getTitlu());
            if (index.column() == 2) 
                return QString::fromStdString(m.getArtist());
            if (index.column() == 3) 
                return m.getRank();
            if (index.column() == 4) 
                return rankCount[m.getRank()];
        }
        return QVariant();
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        /*
        functie care seteaza campurile de sus in tabel
        pre: 
        post: ID | Titlu | Artist | Rank | Count
        */

        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if (section == 0) 
                return "ID";
            if (section == 1) 
                return "Titlu";
            if (section == 2) 
                return "Artist";
            if (section == 3) 
                return "Rank";
            if (section == 4) 
                return "Acelasi Rank (Count)";
        }

        return QVariant();
    }
};