#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ex3.h"

class ex3 : public QMainWindow
{
    Q_OBJECT

public:
    ex3(QWidget *parent = nullptr);
    ~ex3();

private:
    Ui::ex3Class ui;
};

