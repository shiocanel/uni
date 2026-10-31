#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QWidget>
#include <memory>
#include <QString>
#include <QListWidget>

#include "Observer.h"
#include "Service.h"
#include "FilmTableModel.h"

class CosCRUDGUI : public QDialog, public CosObserver {
private:
    Service& service;

    QTableView* table;
    FilmTableModel* model;

    QLineEdit* generateEdit;
    QPushButton* clearButton;
    QPushButton* generateButton;

    void setupUI();
    void refreshTable();

public:
    explicit CosCRUDGUI(Service& service, QWidget* parent = nullptr);
    ~CosCRUDGUI() override;

    void updateCos() override;
};

class CosReadOnlyGUI : public QWidget, public CosObserver {
private:
    Service& service;
    std::vector<QRect> shapes;

    void rebuildShapes();

public:
    explicit CosReadOnlyGUI(Service& service, QWidget* parent = nullptr);
    ~CosReadOnlyGUI() override;

    void updateCos() override;

protected:
    void paintEvent(QPaintEvent* ev) override;
};

class MainWindow : public QWidget {
private:
    Service service;

    QTableView* listaFilme;
    FilmTableModel* filmModel;

    QLineEdit* titluEdit;
    QLineEdit* genEdit;
    QLineEdit* anEdit;
    QLineEdit* actorEdit;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* searchButton;
    QPushButton* undoButton;
    QPushButton* showAllButton;
    QPushButton* clearButton;

    QPushButton* filterTitleButton;
    QPushButton* filterYearButton;

    QPushButton* sortTitleButton;
    QPushButton* sortActorButton;
    QPushButton* sortYearGenreButton;

    QPushButton* addToCosButton;
    QPushButton* removeFromCosButton;
    QPushButton* generateCosButton;
    QPushButton* openCosCRUDButton;
    QPushButton* openCosReadOnlyButton;

    QLineEdit* cosCountEdit;

    QListWidget* genreList;
    QLabel* genreInfoLabel;

    QString currentSelectedTitle;

private:
    void setupUI();
    void setupConnections();

    void refreshList();
    void refreshGenres();

    void clearFields();
    void loadFilmsIntoModel(const std::vector<Film>& films);
    void loadFilmsIntoModel(const Service::FilmView& films);

    void showError(const QString& message);
    void showInfo(const QString& message);

public:
    explicit MainWindow(QWidget* parent = nullptr);
};