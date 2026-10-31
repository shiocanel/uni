#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mata.h"

class mata : public QMainWindow
{
    Q_OBJECT

public:
    mata(QWidget *parent = nullptr);
    ~mata();

private:
    Ui::mataClass ui;
};

