#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim6_melodii.h"

class sim6_melodii : public QMainWindow
{
    Q_OBJECT

public:
    sim6_melodii(QWidget *parent = nullptr);
    ~sim6_melodii();

private:
    Ui::sim6_melodiiClass ui;
};

