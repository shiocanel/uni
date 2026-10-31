#include "GUI.h"

#include <QAbstractItemView>
#include <QFormLayout>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QMessageBox>
#include <QPainter>
#include <QPaintEvent>
#include <QTableView>
#include <QVBoxLayout>
#include <map>
#include <random>

static QString filmToLine(const Film& film) {
    return QString::fromStdString(
        film.getTitlu() + " | " +
        film.getGen() + " | " +
        std::to_string(film.getAnAparitie()) + " | " +
        film.getActorPrincipal()
    );
}

CosCRUDGUI::CosCRUDGUI(Service& service, QWidget* parent)
    : QDialog(parent),
    service(service),
    table(new QTableView(this)),
    model(new FilmTableModel(this)),
    generateEdit(new QLineEdit(this)),
    clearButton(new QPushButton("Goleste cos", this)),
    generateButton(new QPushButton("Genereaza", this)) {
    setWindowTitle("Cos CRUD");
    resize(750, 500);
    setAttribute(Qt::WA_DeleteOnClose);

    service.getCos().addObserver(this);

    setupUI();
    refreshTable();
}

CosCRUDGUI::~CosCRUDGUI() {
    service.getCos().removeObserver(this);
}

void CosCRUDGUI::setupUI() {
    table->setModel(model);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setStretchLastSection(true);

    generateEdit->setPlaceholderText("Numar");
    generateEdit->setValidator(new QIntValidator(1, 1000, this));

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(generateEdit);
    buttonLayout->addWidget(generateButton);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(table);
    layout->addLayout(buttonLayout);

    connect(clearButton, &QPushButton::clicked, this, [this]() {
        try {
            service.golesteCos();
        }
        catch (const std::exception& ex) {
            QMessageBox::critical(this, "Eroare", ex.what());
        }
        });

    connect(generateButton, &QPushButton::clicked, this, [this]() {
        try {
            bool ok = false;
            const int nr = generateEdit->text().trimmed().toInt(&ok);
            if (!ok) {
                QMessageBox::critical(this, "Eroare", "Numar invalid.");
                return;
            }

            service.genereazaCos(nr);
        }
        catch (const std::exception& ex) {
            QMessageBox::critical(this, "Eroare", ex.what());
        }
        });
}

void CosCRUDGUI::refreshTable() {
    model->setFilms(service.getCos().getAll());
}

void CosCRUDGUI::updateCos() {
    refreshTable();
}
CosReadOnlyGUI::CosReadOnlyGUI(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setWindowTitle("Cos ReadOnly");
    resize(700, 500);
    setAttribute(Qt::WA_DeleteOnClose);

    service.getCos().addObserver(this);
    rebuildShapes();
}

CosReadOnlyGUI::~CosReadOnlyGUI() {
    service.getCos().removeObserver(this);
}

void CosReadOnlyGUI::rebuildShapes() {
    shapes.clear();

    const auto& films = service.getCos().getAll();
    const int n = static_cast<int>(films.size());

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> sizeDist(20, 60);

    for (int i = 0; i < n; ++i) {
        const int w = sizeDist(gen);
        const int h = sizeDist(gen);

        const int xMax = std::max(10, width() - w - 10);
        const int yMax = std::max(10, height() - h - 10);

        std::uniform_int_distribution<int> xDist(10, xMax);
        std::uniform_int_distribution<int> yDist(10, yMax);

        shapes.emplace_back(xDist(gen), yDist(gen), w, h);
    }
}

void CosReadOnlyGUI::updateCos() {
    rebuildShapes();
    QWidget::update();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent* ev) {
    Q_UNUSED(ev);

    QPainter p(this);
    p.fillRect(rect(), Qt::white);
    p.setRenderHint(QPainter::Antialiasing, true);

    if (shapes.empty()) {
        p.drawText(rect(), Qt::AlignCenter, "Cosul este gol");
        return;
    }

    p.setPen(QPen(Qt::black, 2));
    for (const auto& r : shapes) {
        p.drawEllipse(r);
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
    resize(1300, 700);

    listaFilme = new QTableView(this);
    filmModel = new FilmTableModel(this);
    listaFilme->setModel(filmModel);
    listaFilme->setSelectionBehavior(QAbstractItemView::SelectRows);
    listaFilme->setSelectionMode(QAbstractItemView::SingleSelection);
    listaFilme->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listaFilme->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    listaFilme->horizontalHeader()->setStretchLastSection(true);

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
    clearButton = new QPushButton("Clear", this);

    filterTitleButton = new QPushButton("FilterByTitle", this);
    filterYearButton = new QPushButton("FilterByYear", this);

    sortTitleButton = new QPushButton("SortByTitle", this);
    sortActorButton = new QPushButton("SortByActor", this);
    sortYearGenreButton = new QPushButton("SortByYear+Genre", this);

    addToCosButton = new QPushButton("Add To Cos", this);
    removeFromCosButton = new QPushButton("Remove From Cos", this);
    generateCosButton = new QPushButton("Generate Cos", this);
    openCosCRUDButton = new QPushButton("Open Cos CRUD", this);
    openCosReadOnlyButton = new QPushButton("Open Cos ReadOnly", this);

    cosCountEdit = new QLineEdit(this);
    cosCountEdit->setPlaceholderText("Nr");
    cosCountEdit->setValidator(new QIntValidator(1, 1000, this));

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
    actionButtons->addWidget(clearButton);

    auto* cosButtons1 = new QHBoxLayout();
    cosButtons1->addWidget(addToCosButton);
    cosButtons1->addWidget(removeFromCosButton);

    auto* cosButtons2 = new QHBoxLayout();
    cosButtons2->addWidget(cosCountEdit);
    cosButtons2->addWidget(generateCosButton);
    cosButtons2->addWidget(openCosCRUDButton);
    cosButtons2->addWidget(openCosReadOnlyButton);

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
    rightLayout->addSpacing(10);
    rightLayout->addWidget(new QLabel("Cos:", this));
    rightLayout->addLayout(cosButtons1);
    rightLayout->addLayout(cosButtons2);
    rightLayout->addStretch();

    auto* mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(leftLayout, 3);
    mainLayout->addLayout(rightLayout, 1);
}

void MainWindow::setupConnections() {
    connect(listaFilme, &QTableView::clicked, this, [this](const QModelIndex& index) {
        if (!index.isValid()) {
            return;
        }

        const auto& film = filmModel->filmAt(index.row());

        currentSelectedTitle = QString::fromStdString(film.getTitlu());
        titluEdit->setText(QString::fromStdString(film.getTitlu()));
        genEdit->setText(QString::fromStdString(film.getGen()));
        anEdit->setText(QString::number(film.getAnAparitie()));
        actorEdit->setText(QString::fromStdString(film.getActorPrincipal()));
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
            QMessageBox::information(this, "Rezultat cautare", filmToLine(film));
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

    connect(clearButton, &QPushButton::clicked, this, [this]() {
        clearFields();
        });

    connect(filterTitleButton, &QPushButton::clicked, this, [this]() {
        try {
            const std::string fragment = titluEdit->text().trimmed().toStdString();
            auto rezultate = service.filtreazaDupaTitlu(fragment);
            loadFilmsIntoModel(rezultate);
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
            loadFilmsIntoModel(rezultate);
            showInfo("Filtrare dupa an realizata.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(sortTitleButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaTitlu();
        loadFilmsIntoModel(rezultate);
        showInfo("Sortare dupa titlu realizata.");
        });

    connect(sortActorButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaActor();
        loadFilmsIntoModel(rezultate);
        showInfo("Sortare dupa actor realizata.");
        });

    connect(sortYearGenreButton, &QPushButton::clicked, this, [this]() {
        auto rezultate = service.sorteazaDupaAnSiGen();
        loadFilmsIntoModel(rezultate);
        showInfo("Sortare dupa an si gen realizata.");
        });

    connect(addToCosButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string titlu = currentSelectedTitle.toStdString();
            if (titlu.empty()) {
                titlu = titluEdit->text().trimmed().toStdString();
            }

            if (titlu.empty()) {
                showError("Selecteaza un film sau scrie titlul lui.");
                return;
            }

            service.adaugaInCos(titlu);
            showInfo("Film adaugat in cos.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(removeFromCosButton, &QPushButton::clicked, this, [this]() {
        try {
            std::string titlu = currentSelectedTitle.toStdString();
            if (titlu.empty()) {
                titlu = titluEdit->text().trimmed().toStdString();
            }

            if (titlu.empty()) {
                showError("Selecteaza un film sau scrie titlul lui.");
                return;
            }

            service.stergeDinCos(titlu);
            showInfo("Film sters din cos.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(generateCosButton, &QPushButton::clicked, this, [this]() {
        try {
            bool ok = false;
            const int nr = cosCountEdit->text().trimmed().toInt(&ok);
            if (!ok) {
                showError("Numarul pentru generare nu este valid.");
                return;
            }

            service.genereazaCos(nr);
            showInfo("Cos generat.");
        }
        catch (const std::exception& ex) {
            showError(ex.what());
        }
        });

    connect(openCosCRUDButton, &QPushButton::clicked, this, [this]() {
        auto* wnd = new CosCRUDGUI(service, this);
        wnd->show();
        wnd->raise();
        wnd->activateWindow();
        });

    connect(openCosReadOnlyButton, &QPushButton::clicked, this, [this]() {
        auto* wnd = new CosReadOnlyGUI(service, this);
        wnd->show();
        wnd->raise();
        wnd->activateWindow();
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

void MainWindow::loadFilmsIntoModel(const std::vector<Film>& films) {
    filmModel->setFilms(films);
}

void MainWindow::loadFilmsIntoModel(const Service::FilmView& films) {
    std::vector<Film> copie;
    copie.reserve(films.size());

    for (const auto& filmRef : films) {
        copie.push_back(filmRef.get());
    }

    filmModel->setFilms(std::move(copie));
}

void MainWindow::refreshList() {
    loadFilmsIntoModel(service.getAll());
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