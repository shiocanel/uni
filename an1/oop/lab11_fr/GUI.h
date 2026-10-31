#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTableWidget>
#include <QWidget>
#include <memory>
#include <QString>

#include "Service.h"

class FilmeWindow : public QDialog {
private:
    QTableWidget* table;

    void setupTable();

public:
    explicit FilmeWindow(QWidget* parent = nullptr);

    void setFilms(const std::vector<Film>& films);
    void setFilms(const Service::FilmView& films);
};

class MainWindow : public QWidget {
private:
    Service service;

    QListWidget* listaFilme;

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
    QPushButton* secondWindowButton;
    QPushButton* clearButton;

    QPushButton* filterTitleButton;
    QPushButton* filterYearButton;

    QPushButton* sortTitleButton;
    QPushButton* sortActorButton;
    QPushButton* sortYearGenreButton;

    QListWidget* genreList;
    QLabel* genreInfoLabel;

    std::unique_ptr<FilmeWindow> window2;
    QString currentSelectedTitle;

private:
    void setupUI();
    void setupConnections();

    void refreshList();
    void refreshGenres();

    void clearFields();
    void loadFilmsIntoList(const std::vector<Film>& films);
    void loadFilmsIntoList(const Service::FilmView& films);

    void showError(const QString& message);
    void showInfo(const QString& message);

public:
    explicit MainWindow(QWidget* parent = nullptr);
};