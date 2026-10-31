#include "GUI.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <map>

FilmeWindow::FilmeWindow(QWidget* parent)
    : QDialog(parent), text(new QTextEdit(this)) {
    setWindowTitle("Lista filme");
    resize(500, 400);

    text->setReadOnly(true);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(text);
}

void FilmeWindow::setFilms(const std::vector<Film>& films) {
    QString result;

    if (films.empty()) {
        result = "Nu exista filme.\n";
    }
    else {
        for (const auto& film : films) {
            result += QString::fromStdString(film.getTitlu()) + " | "
                + QString::fromStdString(film.getGen()) + " | "
                + QString::number(film.getAnAparitie()) + " | "
                + QString::fromStdString(film.getActorPrincipal()) + "\n";
        }
    }

    text->setPlainText(result);
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
    resize(1000, 500);

    listaFilme = new QListWidget(this);

    titluEdit = new QLineEdit(this);
    genEdit = new QLineEdit(this);
    anEdit = new QLineEdit(this);
    actorEdit = new QLineEdit(this);

    titluEdit->setPlaceholderText("Titlu");
    genEdit->setPlaceholderText("Gen");
    anEdit->setPlaceholderText("An");
    actorEdit->setPlaceholderText("Actor principal");
    anEdit->setValidator(new QIntValidator(1800, 2100, this));

    addButton = new QPushButton("Add", this);
    deleteButton = new QPushButton("Remove", this);
    updateButton = new QPushButton("Update", this);
    searchButton = new QPushButton("Search", this);
    undoButton = new QPushButton("Undo", this);
    showAllButton = new QPushButton("Show All", this);
    secondWindowButton = new QPushButton("Fereastra 2", this);
    clearButton = new QPushButton("Clear", this);

    genreList = new QListWidget(this);
    genreInfoLabel = new QLabel("Apasa pe un gen ca sa vezi cate filme sunt.", this);

    auto* form = new QFormLayout();
    form->addRow("Titlu:", titluEdit);
    form->addRow("Gen:", genEdit);
    form->addRow("An:", anEdit);
    form->addRow("Actor:", actorEdit);

    auto* buttons1 = new QHBoxLayout();
    buttons1->addWidget(addButton);
    buttons1->addWidget(updateButton);
    buttons1->addWidget(deleteButton);

    auto* buttons2 = new QHBoxLayout();
    buttons2->addWidget(searchButton);
    buttons2->addWidget(undoButton);
    buttons2->addWidget(clearButton);

    auto* buttons3 = new QHBoxLayout();
    buttons3->addWidget(showAllButton);
    buttons3->addWidget(secondWindowButton);

    auto* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(listaFilme);
    leftLayout->addLayout(form);
    leftLayout->addLayout(buttons1);
    leftLayout->addLayout(buttons2);
    leftLayout->addLayout(buttons3);

    auto* rightLayout = new QVBoxLayout();
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
    connect(addButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titlu = titluEdit->text().toStdString();
            const std::string gen = genEdit->text().toStdString();
            const std::string actor = actorEdit->text().toStdString();
            const int an = anEdit->text().toInt();

            service.adaugaFilm(titlu, gen, an, actor);
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Film adaugat.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(deleteButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titlu = titluEdit->text().toStdString();
            if (titlu.empty()) {
                showError("Scrie titlul filmului pe care vrei sa-l stergi.");
                return;
            }

            service.stergeFilm(titlu);
            refreshList();
            refreshGenres();
            clearFields();
            showInfo("Film sters.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(updateButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titluVechi = titluEdit->text().toStdString();
            const std::string genNou = genEdit->text().toStdString();
            const std::string actorNou = actorEdit->text().toStdString();
            const int anNou = anEdit->text().toInt();

            if (titluVechi.empty()) {
                showError("Scrie titlul filmului pe care vrei sa-l modifici.");
                return;
            }

            service.modificaFilm(
                titluVechi,
                titluVechi,
                genNou,
                anNou,
                actorNou
            );

            refreshList();
            refreshGenres();
            showInfo("Film modificat.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(searchButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string titlu = titluEdit->text().toStdString();
            if (titlu.empty()) {
                showError("Scrie un titlu in campul Titlu.");
                return;
            }

            const Film& film = service.cautaFilm(titlu);

            QMessageBox::information(
                this,
                "Rezultat cautare",
                QString::fromStdString(
                    film.getTitlu() + " | " +
                    film.getGen() + " | " +
                    std::to_string(film.getAnAparitie()) + " | " +
                    film.getActorPrincipal()
                )
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
            showInfo("Undo facut.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(showAllButton, &QPushButton::clicked, this, [this]() {
        window2->setFilms(service.getAll());
        window2->show();
        window2->raise();
        window2->activateWindow();
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

        genreInfoLabel->setText("Genul " + genSelectat + " are " + QString::number(count) + " filme.");
        });
}

void MainWindow::refreshList() {
    listaFilme->clear();

    const auto& all = service.getAll();
    for (const auto& film : all) {
        auto* item = new QListWidgetItem(
            QString::fromStdString(
                film.getTitlu() + " | " +
                film.getGen() + " | " +
                std::to_string(film.getAnAparitie()) + " | " +
                film.getActorPrincipal()
            )
        );
        listaFilme->addItem(item);
    }
}

void MainWindow::clearFields() {
    titluEdit->clear();
    genEdit->clear();
    anEdit->clear();
    actorEdit->clear();
}

void MainWindow::showError(const QString& message) {
    QMessageBox::critical(this, "Eroare", message);
}

void MainWindow::showInfo(const QString& message) {
    QMessageBox::information(this, "Info", message);
}

void MainWindow::refreshGenres() {
    genreList->clear();

    std::map<std::string, int> counts;

    for (const auto& film : service.getAll()) {
        counts[film.getGen()]++;
    }

    for (const auto& pair : counts) {
        const std::string& gen = pair.first;
        int count = pair.second;

        auto* item = new QListWidgetItem(
            QString::fromStdString(gen + " (" + std::to_string(count) + ")")
        );
        item->setData(Qt::UserRole, QString::fromStdString(gen));
        genreList->addItem(item);
    }
}