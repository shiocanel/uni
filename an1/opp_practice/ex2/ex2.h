#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ex2.h"

class ex2 : public QMainWindow
{
    Q_OBJECT

public:
    ex2(QWidget *parent = nullptr);
    ~ex2();

private:
    Ui::ex2Class ui;
};

