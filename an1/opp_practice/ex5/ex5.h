#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ex5.h"

class ex5 : public QMainWindow
{
    Q_OBJECT

public:
    ex5(QWidget *parent = nullptr);
    ~ex5();

private:
    Ui::ex5Class ui;
};

