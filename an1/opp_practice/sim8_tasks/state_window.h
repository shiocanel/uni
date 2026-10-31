#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include "service.h"
#include "observer.h"

class StateWindow : public QWidget, public Observer {
private:
    Service& service;
    std::string stareCurenta;

    QListWidget* list = new QListWidget;
    QPushButton* btnOpen = new QPushButton("Open");
    QPushButton* btnInProgress = new QPushButton("In Progress");
    QPushButton* btnClosed = new QPushButton("Closed");

    void reloadData() {
        list->clear();
        auto taskuri = service.getTasksFilteredAndSorted();
        for (const auto& t : taskuri) {
            if (t.getStare() == stareCurenta) {
                QListWidgetItem* item = new QListWidgetItem(
                    QString::number(t.getId()) + " - " + QString::fromStdString(t.getDescriere())
                );
                item->setData(Qt::UserRole, t.getId());
                list->addItem(item);
            }
        }
    }

    void schimbaStare(const std::string& stareNoua) {
        if (list->currentItem() == nullptr) {
            QMessageBox::warning(this, "Atentie", "Selecteaza un task!");
            return;
        }
        int id = list->currentItem()->data(Qt::UserRole).toInt();
        service.schimbaStareTask(id, stareNoua);
    }

public:
    StateWindow(Service& srv, const std::string& stare) : service{ srv }, stareCurenta{ stare } {
        setWindowTitle(QString::fromStdString(stareCurenta));
        resize(350, 400);

        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->addWidget(list);

        QHBoxLayout* btnLayout = new QHBoxLayout;
        btnLayout->addWidget(btnOpen);
        btnLayout->addWidget(btnInProgress);
        btnLayout->addWidget(btnClosed);
        mainLayout->addLayout(btnLayout);

        QObject::connect(btnOpen, &QPushButton::clicked, [this]() { schimbaStare("open"); });
        QObject::connect(btnInProgress, &QPushButton::clicked, [this]() { schimbaStare("inprogress"); });
        QObject::connect(btnClosed, &QPushButton::clicked, [this]() { schimbaStare("closed"); });

        service.addObserver(this);
        reloadData();
    }

    void update() override {
        reloadData();
    }

    ~StateWindow() {
        service.removeObserver(this);
    }
};