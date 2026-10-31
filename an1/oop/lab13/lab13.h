#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab13.h"

class lab13 : public QMainWindow
{
    Q_OBJECT

public:
    lab13(QWidget *parent = nullptr);
    ~lab13();

private:
    Ui::lab13Class ui;
};

