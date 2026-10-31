#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim5_melodii.h"

class sim5_melodii : public QMainWindow
{
    Q_OBJECT

public:
    sim5_melodii(QWidget *parent = nullptr);
    ~sim5_melodii();

private:
    Ui::sim5_melodiiClass ui;
};

