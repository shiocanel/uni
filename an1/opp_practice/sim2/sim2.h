#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim2.h"

class sim2 : public QMainWindow
{
    Q_OBJECT

public:
    sim2(QWidget *parent = nullptr);
    ~sim2();

private:
    Ui::sim2Class ui;
};

