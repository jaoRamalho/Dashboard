#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/DataProvider.hpp"
#include <QStringListModel> // Adicionado para corrigir o erro de QStringListModel

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
    ui->processesView->clear();
    ui->processesView->setRowCount(list.size());
    ui->processesView->setColumnCount(4); // Exemplo: PID, Nome, Usuário, Memória
    QStringList headers = {"PID", "Nome", "Usuário", "Memória"};
    ui->processesView->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) { // Alterado int para size_t
        const ProcessInfo* p = list[row];
        ui->processesView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->pid)));
        ui->processesView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->name)));
        ui->processesView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->user)));
        ui->processesView->setItem(row, 3, new QTableWidgetItem(QString::number(p->memory)));
        
    }
}

void MainWindow::onMemoryListUpdated(const std::vector<MemoryInfo*>& list) {
    ui->memoryView->clear();
    ui->memoryView->setRowCount(list.size());
    ui->memoryView->setColumnCount(5); // Total, Free, Used, Buffers, Cached
    QStringList headers = {"Total (MB)", "Free (MB)", "Used (MB)", "Buffers (MB)", "Cached (MB)"};
    ui->memoryView->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) {
        const MemoryInfo* mem = list[row];
        ui->memoryView->setItem(row, 0, new QTableWidgetItem(QString::number(mem->total / 1024)));
        ui->memoryView->setItem(row, 1, new QTableWidgetItem(QString::number(mem->free / 1024)));
        ui->memoryView->setItem(row, 2, new QTableWidgetItem(QString::number(mem->used / 1024)));
        ui->memoryView->setItem(row, 3, new QTableWidgetItem(QString::number(mem->buffers / 1024)));
        ui->memoryView->setItem(row, 4, new QTableWidgetItem(QString::number(mem->cached / 1024)));
    }
}

void MainWindow::onCPUListUpdated(const std::vector<CPUInfo*>& list) {
    ui->cpuView->clear();
    ui->cpuView->setRowCount(list.size());
    ui->cpuView->setColumnCount(5); // Columns: CPU and Frequency
    QStringList headers = {"CPU", "Frequency (MHz)", "Model Name", "Model Number", "Idle Time"};
    ui->cpuView->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) {
        const CPUInfo* cpu = list[row];
        ui->cpuView->setItem(row, 0, new QTableWidgetItem(QString("CPU %1").arg(cpu->cpu)));
        ui->cpuView->setItem(row, 1, new QTableWidgetItem(QString::number(cpu->cpuMhz)));
        ui->cpuView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(cpu->modelName)));
        ui->cpuView->setItem(row, 3, new QTableWidgetItem(QString::number(cpu->modelNumber)));
        ui->cpuView->setItem(row, 4, new QTableWidgetItem(QString::number(cpu->idleTime)));
    }
}

void MainWindow::onProcessClicked(int row, int column) {
    Q_UNUSED(column);
    if (row < 0 || row >= ui->processesView->rowCount()) return;

    QString pid = ui->processesView->item(row, 0)->text();
    const ProcessInfo* process = DataProvider::getInstance()->getProcessByPID(pid.toStdString());
    if (!process) return;

    ui->threadsView->clear();
    ui->threadsView->setRowCount(process->threads.size());
    ui->threadsView->setColumnCount(7); // TID, Name, User, Memory, Involuntary Switch, Voluntary Switch, State
    QStringList headers = {"TID", "Name", "User", "Memory (KB)", "Involuntary Switch", "Voluntary Switch", "State"};
    ui->threadsView->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < process->threads.size(); ++row) {
        const TreadsInfo& thread = process->threads[row];
        ui->threadsView->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(thread.tid)));
        ui->threadsView->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(thread.name)));
        ui->threadsView->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(thread.user)));
        ui->threadsView->setItem(row, 3, new QTableWidgetItem(QString::number(thread.memory)));
        ui->threadsView->setItem(row, 4, new QTableWidgetItem(QString::number(thread.swichContextInvoluntary)));
        ui->threadsView->setItem(row, 5, new QTableWidgetItem(QString::number(thread.swichContextVoluntary)));
        ui->threadsView->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(thread.state)));
    }
}
