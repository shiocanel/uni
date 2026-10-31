#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim4_tractoare.h"

class sim4_tractoare : public QMainWindow
{
    Q_OBJECT

public:
    sim4_tractoare(QWidget *parent = nullptr);
    ~sim4_tractoare();

private:
    Ui::sim4_tractoareClass ui;
};

