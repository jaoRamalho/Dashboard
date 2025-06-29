#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/DataProvider.hpp"
#include "include/SystemCallProcesses.hpp"
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
    connect(ui->ProcessButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonProcess);
    connect(ui->PerformanceButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonPerformace);
    connect(ui->MemoryButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonMemory);
    connect(ui->FilesButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonFiles);
    connect(ui->processTable, &QTableWidget::cellClicked, this, &MainWindow::onProcessTableRowClicked);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onProcessTableRowClicked(int row) {
    std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de processos
    
    if (row < 0 || row >= ui->processTable->rowCount() || !update) {
        return; // Verifica se a linha é válida
    }

    QTableWidgetItem* item = ui->processTable->item(row, 0); // Obtém o item da coluna PID
    if (item) {
        QString pid = item->text();

        std::vector<InfoBase*> baseCopy = SystemCallProcesses::getInstance()->getInfo();
        
        // Obtém o vetor de InfoBase* e converte para ProcessInfo*
        std::vector<ProcessInfo*> copy;
        for (InfoBase* base : baseCopy) {
            if (ProcessInfo* process = dynamic_cast<ProcessInfo*>(base)) {
                copy.push_back(process); // Adiciona ao vetor apenas se for ProcessInfo*
            }
        }

        for (auto& process : copy) {
            if (!process) {
                std::cout << "Processo nulo encontrado, pulando..." << std::endl;
                continue; // Verifica se o ponteiro é válido
            }

            if (QString::fromStdString(process->pid) == pid) {
                // Limpa a tabela de detalhes
                if (process->threads.empty()) {
                    std::cout << "Nenhuma thread encontrada para o processo com PID: " << process->pid << std::endl;
                    return; // Se não houver threads, não faz nada
                }
                QStringList headers = {"TID", "Nome", "User", "Memory (KB)", "Switch Context Involuntary", "Switch Context Voluntary", "State"};
                ui->ProcessDataViewA->clearContents();
                ui->ProcessDataViewA->clear();
                ui->ProcessDataViewA->setRowCount(process->threads.size());
                ui->ProcessDataViewA->setColumnCount(7); // Exemplo: PID, Nome
                ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);

                for (size_t i = 0; i < process->threads.size(); ++i) {
                    const TreadsInfo& thread = process->threads[i];
                    ui->ProcessDataViewA->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(thread.tid)));
                    ui->ProcessDataViewA->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(thread.name)));
                    ui->ProcessDataViewA->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(thread.user)));
                    ui->ProcessDataViewA->setItem(i, 3, new QTableWidgetItem(QString::number(thread.memory)));
                    ui->ProcessDataViewA->setItem(i, 4, new QTableWidgetItem(QString::number(thread.swichContextInvoluntary)));
                    ui->ProcessDataViewA->setItem(i, 5, new QTableWidgetItem(QString::number(thread.swichContextVoluntary)));
                    ui->ProcessDataViewA->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(thread.state)));
                }

                break; // Encerra o loop após encontrar o processo
            }
        }
    }
}

void clearTableWidget(QTableWidget* table) {
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int col = 0; col < table->columnCount(); ++col) {
            QTableWidgetItem* item = table->takeItem(row, col);
            delete item; // Libera a memória do item
            item = nullptr; // Define o ponteiro como nulo
        }
    }
    table->clearContents(); // Limpa o conteúdo da tabela
}

void MainWindow::onClickedButtonProcess() {
    ui->ProcessDataViewA->clear();
    ui->ProcessButton->setChecked(true);
    ui->MemoryButton->setChecked(false);
    ui->PerformanceButton->setChecked(false);
    ui->FilesButton->setChecked(false);
}

void MainWindow::onClickedButtonMemory() {
    ui->ProcessDataViewA->clear();
    ui->MemoryButton->setChecked(true);
    ui->ProcessButton->setChecked(false);
    ui->PerformanceButton->setChecked(false);
    ui->FilesButton->setChecked(false);

}

void MainWindow::onClickedButtonPerformace() {
    ui->ProcessDataViewA->clear();
    ui->PerformanceButton->setChecked(true);
    ui->ProcessButton->setChecked(false);
    ui->MemoryButton->setChecked(false);
    ui->FilesButton->setChecked(false);
}

void MainWindow::onClickedButtonFiles() {
    ui->ProcessDataViewA->clear();
    ui->FilesButton->setChecked(true);
    ui->ProcessButton->setChecked(false);
    ui->MemoryButton->setChecked(false);
    ui->PerformanceButton->setChecked(false);
}


   
void MainWindow::updateGeneralDataProcess(const std::vector<ProcessInfo> list) {
    if (list.empty() || !ui->ProcessButton->isChecked() ) {
        return; // Se a lista estiver vazia, não faz nada
    }

    update = false; // Reseta a flag de atualização

    int qtdTotalProcessos = list.size();
    
    int qtdTotalThreads = 0;
    for (auto &process : list) {
        qtdTotalThreads += process.n_threads; // Soma o número de threads de cada processo
    }

    unsigned long totalMemory = 0;
    for (const auto &process : list) {
        totalMemory += process.memory; // Soma a memória de cada processo
    }

    clearTableWidget(ui->GeneralDataView); // Limpa a tabela antes de adicionar novos dados
    ui->GeneralDataView->clearContents();
    ui->GeneralDataView->clear(); // Limpa a tabela antes de adicionar novos dados
    ui->GeneralDataView->setRowCount(1);
    ui->GeneralDataView->setColumnCount(3); // Duas colunas: Descrição e Valor
    QStringList headers = {"Total Processes", "Total Threads", "Total Memory (MB)"};
    ui->GeneralDataView->setHorizontalHeaderLabels(headers);
    ui->GeneralDataView->setItem(0, 0, new QTableWidgetItem(QString::number(qtdTotalProcessos)));
    ui->GeneralDataView->setItem(0, 1, new QTableWidgetItem(QString::number(qtdTotalThreads)));
    ui->GeneralDataView->setItem(0, 2, new QTableWidgetItem(QString::number(totalMemory / 1024))); // Convertendo para MB
    ui->GeneralDataView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::updateGeneralDataMemory(const std::vector<MemoryInfo> list) {
    if (list.empty() || !ui->MemoryButton->isChecked()) {
        return; // Se a lista estiver vazia, não faz nada
    }

}

void MainWindow::onProcessListUpdated(const std::vector<ProcessInfo> list) {
    if(list.empty()) { 
        return; 
    } 
    
    clearTableWidget(ui->processTable); // Limpa a tabela antes de adicionar novos dados
    ui->processTable->clearContents();
    ui->processTable->clear();
    ui->processTable->setRowCount(list.size());
    updateGeneralDataProcess(list); // Atualiza os dados gerais dos processos
    
    update = true;

    ui->processTable->setColumnCount(10); // Exemplo: PID, Nome, Usuário, Memória
    QStringList headers = {"PID", "Nome", "Usuário", "Memória(KB)", "N Threads", "Switch Context Involuntary", "Switch Context Voluntary", "State", "Stack Size (KB)", "Heap Size (KB)"};
    ui->processTable->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) { // Alterado int para size_t
        const ProcessInfo p = list[row];
        ui->processTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.pid)));
        ui->processTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.name)));
        ui->processTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.user)));
        ui->processTable->setItem(row, 3, new QTableWidgetItem(QString::number(p.memory)));  
        ui->processTable->setItem(row, 4, new QTableWidgetItem(QString::number(p.threads.size()))); // Número de threads
        ui->processTable->setItem(row, 5, new QTableWidgetItem(QString::number(p.swichContextInvoluntary)));
        ui->processTable->setItem(row, 6, new QTableWidgetItem(QString::number(p.swichContextVoluntary)));
        ui->processTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(p.state)));
        ui->processTable->setItem(row, 8, new QTableWidgetItem(QString::number(p.stackSize))); // Tamanho da pilha
        ui->processTable->setItem(row, 9, new QTableWidgetItem(QString::number(p.heapSize))); // Tamanho do heap
    }   
}

void MainWindow::updateGeneralDataCPU(const std::vector<CPUInfo> list) {
    if (list.empty() || !ui->PerformanceButton->isChecked()) {
        return; // Se a lista estiver vazia, não faz nada
    }
}

void MainWindow::onMemoryListUpdated(const std::vector<MemoryInfo> list) {
    if (list.empty() || !ui->MemoryButton->isChecked()) {
        return; // Se a lista estiver vazia, não faz nada
    }
    
    unsigned long totalMemory = 0;
    unsigned long freeMemory = 0;
    unsigned long usedMemory = 0;
    unsigned long buffers = 0;
    unsigned long cached = 0;

    for (const auto &mem : list) {
        totalMemory += mem.total;
        freeMemory += mem.free;
        usedMemory += mem.used;
        buffers += mem.buffers;
        cached += mem.cached;
    }

    clearTableWidget(ui->ProcessDataViewA); // Limpa a tabela antes de adicionar novos dados
    ui->GeneralDataView->clearContents();
    ui->ProcessDataViewA->clear();
    ui->ProcessDataViewA->setRowCount(1);
    ui->ProcessDataViewA->setColumnCount(5); // Total, Free, Used, Buffers, Cached
    QStringList headers = {"Total (MB)", "Free (MB)", "Used (MB)", "Buffers (MB)", "Cached (MB)"};
    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);
    
    ui->ProcessDataViewA->setItem(0, 0, new QTableWidgetItem(QString::number(totalMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 1, new QTableWidgetItem(QString::number(freeMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 2, new QTableWidgetItem(QString::number(usedMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 3, new QTableWidgetItem(QString::number(buffers / 1024)));
    ui->ProcessDataViewA->setItem(0, 4, new QTableWidgetItem(QString::number(cached / 1024)));
}

void MainWindow::onCPUListUpdated(const std::vector<CPUInfo> list) {
    if(list.empty() || !ui->PerformanceButton->isChecked()) {
        return; // Se a lista estiver vazia, não faz nada
    }

    clearTableWidget(ui->ProcessDataViewA); // Limpa a tabela antes de adicionar novos dados
    ui->ProcessDataViewA->clearContents();
    ui->ProcessDataViewA->clear();
    ui->ProcessDataViewA->setRowCount(list.size());
    ui->ProcessDataViewA->setColumnCount(5); // Exemplo: CPU, Modelo, Número do Modelo, Tempo de Inatividade, MHz
    QStringList headers = {"CPU", "Modelo", "Número do Modelo", "Tempo de Inatividade (%)", "MHz"};
    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);
    for (size_t row = 0; row < list.size(); ++row) { // Alterado int para size_t
        const CPUInfo c = list[row];
        ui->ProcessDataViewA->setItem(row, 0, new QTableWidgetItem(QString::number(c.cpu)));
        ui->ProcessDataViewA->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.modelName)));
        ui->ProcessDataViewA->setItem(row, 2, new QTableWidgetItem(QString::number(c.modelNumber)));
        ui->ProcessDataViewA->setItem(row, 3, new QTableWidgetItem(QString::number(c.idleTime)));
        ui->ProcessDataViewA->setItem(row, 4, new QTableWidgetItem(QString::number(c.cpuMhz)));
    }
}