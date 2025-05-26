#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/DataProvider.hpp"

#include <QTableWidgetItem>
#include <iostream>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(DataProvider::getInstance(), &DataProvider::processListUpdated, this, &MainWindow::onProcessListUpdated);
    connect(DataProvider::getInstance(), &DataProvider::cpuListUpdated, this, &MainWindow::onCPUListUpdated);
    connect(DataProvider::getInstance(), &DataProvider::memoryListUpdated, this, &MainWindow::onMemoryListUpdated);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onProcessListUpdated(const std::vector<ProcessInfo*>& list) {


}

void MainWindow::onMemoryListUpdated(const std::vector<MemoryInfo*>& list) {


}

void MainWindow::onCPUListUpdated(const std::vector<CPUInfo*>& list) {


}