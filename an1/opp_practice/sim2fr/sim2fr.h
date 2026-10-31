#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim2fr.h"

class sim2fr : public QMainWindow
{
    Q_OBJECT

public:
    sim2fr(QWidget *parent = nullptr);
    ~sim2fr();

private:
    Ui::sim2frClass ui;
};

