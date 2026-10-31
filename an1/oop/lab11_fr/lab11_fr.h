#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab11_fr.h"

class lab11_fr : public QMainWindow
{
    Q_OBJECT

public:
    lab11_fr(QWidget *parent = nullptr);
    ~lab11_fr();

private:
    Ui::lab11_frClass ui;
};

