#ifndef NOVA_JANELA_H
#define NOVA_JANELA_H
#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/DataProvider.hpp"
#include <QTableWidgetItem>
#include <iostream>
#include <QLineEdit>
#include <QDialog>

namespace Ui {
class moreinforswindow;
}

class moreinforswindow : public QDialog
{
    Q_OBJECT

public:
    explicit moreinforswindow(QWidget *parent = nullptr);
    ~moreinforswindow();

private:
    Ui::moreinforswindow *ui;
};

#endif // NOVA_JANELA_H
