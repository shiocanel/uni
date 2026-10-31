#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_sim8_tasks.h"

class sim8_tasks : public QMainWindow
{
    Q_OBJECT

public:
    sim8_tasks(QWidget *parent = nullptr);
    ~sim8_tasks();

private:
    Ui::sim8_tasksClass ui;
};

