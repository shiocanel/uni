#include "GUI.h"

#include <QAbstractItemView>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QIntValidator>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <map>

static QString filmToLine(const Film& film) {
    return QString::fromStdString(
        film.getTitlu() + " | " +
        film.getGen() + " | " +
        std::to_string(film.getAnAparitie()) + " | " +
        film.getActorPrincipal()
    );
}

FilmeWindow::FilmeWindow(QWidget* parent)
    : QDialog(parent), table(new QTableWidget(this)) {
    setWindowTitle("Lista filme");
    resize(750, 450);

    setupTable();

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(table);
}

void FilmeWindow::setupTable() {
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({ "Titlu", "Gen", "An", "Actor principal" });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void FilmeWindow::setFilms(const std::vector<Film>& films) {
    table->clearContents();
    table->setRowCount(static_cast<int>(films.size()));

    for (int i = 0; i < static_cast<int>(films.size()); ++i) {
        const auto& film = films[i];

        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAnAparitie())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActorPrincipal())));
    }
}

void FilmeWindow::setFilms(const Service::FilmView& films) {
    table->clearContents();
    table->setRowCount(static_cast<int>(films.size()));

    int i = 0;
    for (const auto& filmRef : films) {
        const auto& film = filmRef.get();

        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(film.getTitlu())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(film.getGen())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(film.getAnAparitie())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(film.getActorPrincipal())));
        ++i;
    }
}

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent), service("filme.txt") {
    setupUI();
    setupConnections();
    refreshList();
    refreshGenres();
}

void MainWindow::setupUI() {
    setWindowTitle("GUI Filme");
    resize(1200, 650);

    listaFilme = new QListWidget(this);
    listaFilme->setSelectionMode(QAbstractItemView::SingleSelection);

    titluEdit = new QLineEdit(this);
    genEdit = new QLineEdit(this);
    anEdit = new QLineEdit(this);
    actorEdit = new QLineEdit(this);

    titluEdit->setPlaceholderText("Titlu");
    genEdit->setPlaceholderText("Gen");
    anEdit->setPlaceholderText("An");
    actorEdit->setPlaceholderText("Actor principal");
    anEdit->setValidator(new QIntValidator(1888, 2100, this));

    addButton = new QPushButton("Add", this);
    deleteButton = new QPushButton("Remove", this);
    updateButton = new QPushButton("Update", this);
    searchButton = new QPushButton("Search", this);
    undoButton = new QPushButton("Undo", this);
    showAllButton = new QPushButton("Show All", this);
    secondWindowButton = new QPushButton("Open Window 2", this);
    clearButton = new QPushButton("Clear", this);

    filterTitleButton = new QPushButton("FilterByTitle", this);
    filterYearButton = new QPushButton("FilterByYear", this);

    sortTitleButton = new QPushButton("SortByTitle", this);
    sortActorButton = new QPushButton("SortByActor", this);
    sortYearGenreButton = new QPushButton("SortByYear+Genre", this);

    genreList = new QListWidget(this);
    genreInfoLabel = new QLabel("Selecteaza un gen pentru detalii.", this);

    auto* form = new QFormLayout();
    form->addRow("Titlu:", titluEdit);
    form->addRow("Gen:", genEdit);
    form->addRow("An:", anEdit);
    form->addRow("Actor:", actorEdit);

    auto* crudButtons = new QHBoxLayout();
    crudButtons->addWidget(addButton);
    crudButtons->addWidget(updateButton);
    crudButtons->addWidget(deleteButton);

    auto* filterButtons = new QHBoxLayout();
    filterButtons->addWidget(filterTitleButton);
    filterButtons->addWidget(filterYearButton);

    auto* sortButtons = new QHBoxLayout();
    sortButtons->addWidget(sortTitleButton);
    sortButtons->addWidget(sortActorButton);
    sortButtons->addWidget(sortYearGenreButton);

    auto* actionButtons = new QHBoxLayout();
    actionButtons->addWidget(searchButton);
    actionButtons->addWidget(undoButton);
    actionButtons->addWidget(showAllButton);
    actionButtons->addWidget(secondWindowButton);
    actionButtons->addWidget(clearButton);

    auto* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("Lista filme:", this));
    leftLayout->addWidget(listaFilme);
    leftLayout->addLayout(crudButtons);
    leftLayout->addLayout(filterButtons);
    leftLayout->addLayout(sortButtons);
    leftLayout->addLayout(actionButtons);

    auto* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(new QLabel("Date film:", this));
    rightLayout->addLayout(form);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(new QLabel("Genuri existente:", this));
    rightLayout->addWidget(genreList);
    rightLayout->addWidget(genreInfoLabel);
    rightLayout->addStretch();

    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);

    window2 = std::make_unique<FilmeWindow>(this);
}

void MainWindow::setupConnections() {
    connect(listaFilme, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        if (!item) {
            return;
        }

        const QString titlu = item->data(Qt::UserRole).toString();
        const QString gen = item->data(Qt::UserRole + 1).toString();
        const QString an = item->data(Qt::UserRole + 2).toString();
        const QString actor = item->data(Qt::UserRole + 3).toString();

        currentSelectedTitle = titlu;

        titluEdit->setText(titlu);
        genEdit->setText(gen);
        anEdit->setText(an);
        actorEdit->setText(actor);
        });

    connect(addButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titlu = titluEdit->text().trimmed().toStdString();
            const std::string gen = genEdit->text().trimmed().toStdString();
            const std::string actor = actorEdit->text().trimmed().toStdString();

            bool ok = false;
            const int an = anEdit->text().trimmed().toInt(&ok);
            if (!ok) {
                showError("Anul introdus nu este valid.");
                return;
            }

            service.adaugaFilm(titlu, gen, an, actor);
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Film adaugat cu succes.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string titlu = currentSelectedTitle.toStdString();
            if (titlu.empty()) {
                titlu = titluEdit->text().trimmed().toStdString();
            }

            if (titlu.empty()) {
                showError("Selecteaza un film sau scrie titlul lui.");
                return;
            }

            service.stergeFilm(titlu);
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Film sters cu succes.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(updateButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string titluVechi = currentSelectedTitle.toStdString();
            if (titluVechi.empty()) {
                titluVechi = titluEdit->text().trimmed().toStdString();
            }

            const std::string titluNou = titluEdit->text().trimmed().toStdString();
            const std::string genNou = genEdit->text().trimmed().toStdString();
            const std::string actorNou = actorEdit->text().trimmed().toStdString();

            bool ok = false;
            const int anNou = anEdit->text().trimmed().toInt(&ok);
            if (!ok) {
                showError("Anul introdus nu este valid.");
                return;
            }

            if (titluVechi.empty()) {
                showError("Selecteaza un film sau scrie titlul filmului de modificat.");
                return;
            }

            service.modificaFilm(titluVechi, titluNou, genNou, anNou, actorNou);
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Film modificat cu succes.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(searchButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titlu = titluEdit->text().trimmed().toStdString();
            if (titlu.empty()) {
                showError("Scrie titlul filmului in campul Titlu.");
                return;
            }

            const Film& film = service.cautaFilm(titlu);

            QMessageBox::information(
                this,
                "Rezultat cautare",
                filmToLine(film)
            );
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(undoButton, &QPushButton::clicked, this, [this]() {
        try {
            service.undo();
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Undo realizat cu succes.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(showAllButton, &QPushButton::clicked, this, [this]() {
        refreshList();
        showInfo("Lista completa afisata.");
        });

    connect(secondWindowButton, &QPushButton::clicked, this, [this]() {
        window2->setFilms(service.getAll());
        window2->show();
        window2->raise();
        window2->activateWindow();
        });

    connect(clearButton, &QPushButton::clicked, this, [this]() {
        clearFields();
        });

    connect(filterTitleButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string fragment = titluEdit->text().trimmed().toStdString();
            auto rezultate = service.filtreazaDupaTitlu(fragment);
            loadFilmsIntoList(rezultate);
            showInfo("Filtrare dupa titlu realizata.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(filterYearButton, &QPushButton::clicked, this, [this]() {
        try {
            bool ok = false;
            const int an = anEdit->text().trimmed().toInt(&ok);
            if (!ok) {
                showError("Anul introdus nu este valid.");
                return;
            }

            auto rezultate = service.filtreazaDupaAn(an);
            loadFilmsIntoList(rezultate);
            showInfo("Filtrare dupa an realizata.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(sortTitleButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaTitlu();
        loadFilmsIntoList(rezultate);
        showInfo("Sortare dupa titlu realizata.");
        });

    connect(sortActorButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaActor();
        loadFilmsIntoList(rezultate);
        showInfo("Sortare dupa actor realizata.");
        });

    connect(sortYearGenreButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaAnSiGen();
        loadFilmsIntoList(rezultate);
        showInfo("Sortare dupa an si gen realizata.");
        });

    connect(genreList, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) {
        if (!item) {
            return;
        }

        const QString genSelectat = item->data(Qt::UserRole).toString();

        int count = 0;
        for (const auto& film : service.getAll()) {
            if (QString::fromStdString(film.getGen()) == genSelectat) {
                count++;
            }
        }

        genreInfoLabel->setText(
            "Genul \"" + genSelectat + "\" are " + QString::number(count) + " filme."
        );
        });
}

void MainWindow::loadFilmsIntoList(const std::vector<Film>& films) {
    listaFilme->clear();

    for (const auto& film : films) {
        auto* item = new QListWidgetItem(filmToLine(film));
        item->setData(Qt::UserRole, QString::fromStdString(film.getTitlu()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(film.getGen()));
        item->setData(Qt::UserRole + 2, film.getAnAparitie());
        item->setData(Qt::UserRole + 3, QString::fromStdString(film.getActorPrincipal()));
        listaFilme->addItem(item);
    }
}

void MainWindow::loadFilmsIntoList(const Service::FilmView& films) {
    listaFilme->clear();

    for (const auto& filmRef : films) {
        const auto& film = filmRef.get();

        auto* item = new QListWidgetItem(filmToLine(film));
        item->setData(Qt::UserRole, QString::fromStdString(film.getTitlu()));
        item->setData(Qt::UserRole + 1, QString::fromStdString(film.getGen()));
        item->setData(Qt::UserRole + 2, film.getAnAparitie());
        item->setData(Qt::UserRole + 3, QString::fromStdString(film.getActorPrincipal()));
        listaFilme->addItem(item);
    }
}

void MainWindow::refreshList() {
    loadFilmsIntoList(service.getAll());
    currentSelectedTitle.clear();
    listaFilme->clearSelection();
}

void MainWindow::refreshGenres() {
    genreList->clear();

    std::map<std::string, int> counts;

    for (const auto& film : service.getAll()) {
        counts[film.getGen()]++;
    }

    for (const auto& pair : counts) {
        const std::string& gen = pair.first;
        const int count = pair.second;

        auto* item = new QListWidgetItem(
            QString::fromStdString(gen + " (" + std::to_string(count) + ")")
        );
        item->setData(Qt::UserRole, QString::fromStdString(gen));
        genreList->addItem(item);
    }

    genreInfoLabel->setText("Selecteaza un gen pentru detalii.");
}

void MainWindow::clearFields() {
    titluEdit->clear();
    genEdit->clear();
    anEdit->clear();
    actorEdit->clear();

    currentSelectedTitle.clear();
    listaFilme->clearSelection();
}

void MainWindow::showError(const QString& message) {
    QMessageBox::critical(this, "Eroare", message);
}

void MainWindow::showInfo(const QString& message) {
    QMessageBox::information(this, "Info", message);
}