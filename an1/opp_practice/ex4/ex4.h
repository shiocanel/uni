#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ex4.h"

class ex4 : public QMainWindow
{
    Q_OBJECT

public:
    ex4(QWidget *parent = nullptr);
    ~ex4();

private:
    Ui::ex4Class ui;
};

