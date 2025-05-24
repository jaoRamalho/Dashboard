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
    connect(ui->processSearchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onProcessListUpdated(const std::vector<ProcessInfo>& list) {
    std::cout << "Process list updated with " << list.size() << " processes." << std::endl;
    allProcesses = list; // Armazena a lista completa para filtragem
 
    QString filter = ui->processSearchEdit->text();
    std::vector<ProcessInfo> filtered;

    if (!filter.isEmpty()) {
        for (const auto& p : allProcesses) {
            if (QString::fromStdString(p.name).contains(filter, Qt::CaseInsensitive)) {
                filtered.push_back(p);
            }
        }
    } else {
        filtered = allProcesses;
    }
 
    ui->processTable->setRowCount(static_cast<int>(filtered.size()));
    ui->processTable->setColumnCount(6);
    QStringList headers = {"PID", "Nome", "Usuário", "Memória (KB)", "Numero de Threads", "Threads ID"};
    ui->processTable->setHorizontalHeaderLabels(headers);

    for (int row = 0; row < static_cast<int>(filtered.size()); ++row) {
        
        const ProcessInfo& p = filtered[row];
        ui->processTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.pid)));
        ui->processTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.name)));
        ui->processTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.user)));
        ui->processTable->setItem(row, 3, new QTableWidgetItem(QString::number(p.memory)));
        ui->processTable->setItem(row, 4, new QTableWidgetItem(QString::number(p.n_threads)));
        // Junta os threads em uma string só
        QString threads = QString::fromStdString(
            std::accumulate(
                p.threadsID.begin(), p.threadsID.end(), std::string(),
                [](const std::string& a, const std::string& b) {
                    return a.empty() ? b : a + ", " + b;
                }
            )
        );
        ui->processTable->setItem(row, 5, new QTableWidgetItem(threads));
    }
}

void MainWindow::onSearchTextChanged() {
    // Armazene a lista completa em um membro, por exemplo: this->allProcesses
    onProcessListUpdated(allProcesses);
}
