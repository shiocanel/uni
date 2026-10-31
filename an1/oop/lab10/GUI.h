#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <memory>
#include "Service.h"

class FilmeWindow : public QDialog {
private:
    QTextEdit* text;

public:
    explicit FilmeWindow(QWidget* parent = nullptr);
    void setFilms(const std::vector<Film>& films);
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

    QListWidget* genreList;
    QLabel* genreInfoLabel;

    std::unique_ptr<FilmeWindow> window2;

private:
    void setupUI();
    void setupConnections();
    void refreshList();
    void refreshGenres();
    void clearFields();
    void showError(const QString& message);
    void showInfo(const QString& message);

public:
    explicit MainWindow(QWidget* parent = nullptr);
};