#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim7_produse.h"

class sim7_produse : public QMainWindow
{
    Q_OBJECT

public:
    sim7_produse(QWidget *parent = nullptr);
    ~sim7_produse();

private:
    Ui::sim7_produseClass ui;
};

