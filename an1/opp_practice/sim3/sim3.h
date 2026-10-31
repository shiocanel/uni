#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim3.h"

class sim3 : public QMainWindow
{
    Q_OBJECT

public:
    sim3(QWidget *parent = nullptr);
    ~sim3();

private:
    Ui::sim3Class ui;
};

