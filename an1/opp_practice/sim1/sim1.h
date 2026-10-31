#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim1.h"

class sim1 : public QMainWindow
{
    Q_OBJECT

public:
    sim1(QWidget *parent = nullptr);
    ~sim1();

private:
    Ui::sim1Class ui;
};

