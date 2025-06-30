#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "include/DataProvider.hpp"
#include "include/SystemCallProcesses.hpp"
#include "include/SystemCallMemory.hpp"
#include "include/MyMutex.hpp"
#include <QStringListModel> // Adicionado para corrigir o erro de QStringListModel

#include <QTableWidgetItem>
#include <iostream>
#include <QLineEdit>

#include <QDesktopServices>
#include <QUrl>
#include <QDebug>
#include "include/SystemCallDisk.hpp"




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

QStandardItemModel* fileTreeModel = nullptr;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::MainWindow), 
    activeButton(FlagButton::ButtonFiles),
    activeButtonChar(FlagButton::ButtonA) // Inicializa activeButtonChar com Button
{
    ui->setupUi(this);

    // Conexões dos botões e sinais
    connect(DataProvider::getInstance(), &DataProvider::processListUpdated, this, &MainWindow::onProcessListUpdated);
    connect(DataProvider::getInstance(), &DataProvider::cpuListUpdated, this, &MainWindow::onCPUListUpdated);
    connect(DataProvider::getInstance(), &DataProvider::memoryListUpdated, this, &MainWindow::onMemoryListUpdated);
    connect(DataProvider::getInstance(), &DataProvider::diskListUpdated, this, &MainWindow::onDiskListUpdated);
    connect(ui->PartitionsButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonPartitions);
    connect(ui->ProcessButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonProcess);
    connect(ui->PerformanceButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonPerformace);
    connect(ui->MemoryButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonMemory);
    connect(ui->FilesButton, &QPushButton::clicked, this, &MainWindow::onClickedButtonFiles);
    connect(ui->processTable, &QTableWidget::cellClicked, this, &MainWindow::onProcessTableRowClicked);
    connect(ui->ButtonA, &QPushButton::clicked, this, &MainWindow::onClikedButtonA);
    connect(ui->ButtonB, &QPushButton::clicked, this, &MainWindow::onClikedButtonB);
    connect(ui->ButtonC, &QPushButton::clicked, this, &MainWindow::onClikedButtonC);
    // === Inicializa TreeView de Arquivos ===
    fileTreeView = new QTreeView(this);
    fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    fileTreeView->setModel(fileSystemModel);
    fileTreeView->setRootIndex(fileSystemModel->index(QDir::rootPath()));

    ui->stackedWidgetMain->setCurrentIndex(0); // inicia com a página de tabela de processos
    //ui->GeneralDataView->hide();
    // Adiciona a árvore de arquivos ao layout do frame
    if (ui->frameContent->layout()) {
        ui->frameContent->layout()->addWidget(fileTreeView);
    }

    // Conexão para clique na árvore
    connect(fileTreeView, &QTreeView::clicked, this, [=](const QModelIndex &index) {
        QString path = fileSystemModel->filePath(index);
        qDebug() << "Arquivo ou diretório clicado:" << path;
        // Aqui você pode fazer algo como abrir uma nova visualização, etc.
    });
    
    if (!ui->frameContent->layout()) {
        QVBoxLayout* layout = new QVBoxLayout(ui->frameContent);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);
        ui->frameContent->setLayout(layout);
    }

    ui->frameContent->layout()->addWidget(fileTreeView);
}
void MainWindow::onClikedButtonA() {
    ui->ProcessDataViewA->clear();
    activeButtonChar = FlagButton::ButtonA; // Atualiza activeButtonChar
    ui->ButtonA->setChecked(true);
    ui->ButtonB->setChecked(false);
    ui->ButtonC->setChecked(false);
    ui->stackedWidgetMaster->setCurrentIndex(0);
    setActiveButton(ui->ButtonA);
}
void MainWindow::onClikedButtonB() {
    ui->ProcessDataViewA->clear();
    activeButtonChar = FlagButton::ButtonB; // Atualiza activeButtonChar
    ui->ButtonB->setChecked(true);
    ui->ButtonA->setChecked(false);
    ui->ButtonC->setChecked(false);
    ui->stackedWidgetMaster->setCurrentIndex(1);
    setActiveButton(ui->ButtonB);
    // Solicita atualização das partições ao clicar no Botão B, se estiver na aba Files
    if (ui->FilesButton->isChecked()) {
        SystemCallDisk::getInstance()->updateDiskPartitions();
        const std::vector<InfoBase*>& diskData = SystemCallDisk::getInstance()->getInfo();
        std::vector<PartitionInfo> partitions;
        for (InfoBase* base : diskData) {
            if (PartitionInfo* p = dynamic_cast<PartitionInfo*>(base)) {
                partitions.push_back(*p);
            }
        }
        onDiskListUpdated(partitions);
    }
}

void MainWindow::onClikedButtonC() {
    // se estiver em processos e pressionar c
    // ui->stackedWidgetMaster->setCurrentIndex(1);
    ui->ProcessDataViewA->clear();
    activeButtonChar = FlagButton::ButtonC; // Atualiza activeButtonChar
    ui->ButtonC->setChecked(true);
    ui->ButtonA->setChecked(false);
    ui->ButtonB->setChecked(false);
    ui->stackedWidgetMaster->setCurrentIndex(1);
    setActiveButton(ui->ButtonC);
}

void MainWindow::showTableView() {
    if (processTableWidget) processTableWidget->show();
    if (fileTreeView) fileTreeView->hide();
}

void MainWindow::showFileTreeView(const QString& path) {
    if (!fileSystemModel || !fileTreeView) return;

    QModelIndex index = fileSystemModel->index(path);
    fileTreeView->setRootIndex(index);

    fileTreeView->show();
    if (processTableWidget) processTableWidget->hide();
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::onProcessTableRowClicked(int row) {
    std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de processos
    if (row < 0 || row >= ui->processTable->rowCount() || !update || activeButton != FlagButton::ButtonProcess) {
        return; // Verifica se a linha é válida
    }

    QTableWidgetItem* item = ui->processTable->item(row, 0); // Obtém o item da coluna PID
    if (item) {
        QString pid = item->text();

        // Obtém o vetor de ProcessInfo por valor
        std::vector<InfoBase*> baseCopy = SystemCallProcesses::getInstance()->getInfo();
        
        // Obtém o vetor de InfoBase* e converte para ProcessInfo*
        std::vector<ProcessInfo> copy;
        for (InfoBase* base : baseCopy) {
            if (ProcessInfo* process = dynamic_cast<ProcessInfo*>(base)) {
                copy.push_back(*process); // Adiciona ao vetor apenas se for ProcessInfo*
            }
        }

        for (auto& process : copy) {
            if (QString::fromStdString(process.pid) == pid) {
                if (activeButtonChar == FlagButton::ButtonB) {
                    // Limpa a tabela de detalhes
                    if (process.threads.empty()) {
                        std::cout << "Nenhuma thread encontrada para o processo com PID: " << process.pid << std::endl;
                        return; // Se não houver threads, não faz nada
                    }
                    QStringList headers = {"TID", "Nome", "User", "Memory (KB)", "Switch Context Involuntary", "Switch Context Voluntary", "State"};
                    clearTableWidget(ui->ProcessDataViewA); // Limpa a tabela antes de preencher
                    ui->ProcessDataViewA->clearContents();
                    ui->ProcessDataViewA->clear();
                    ui->ProcessDataViewA->setRowCount(process.threads.size());
                    ui->ProcessDataViewA->setColumnCount(7); // Exemplo: PID, Nome
                    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);
                    for (size_t i = 0; i < process.threads.size(); ++i) {
                        const TreadsInfo& thread = process.threads[i];
                        ui->ProcessDataViewA->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(thread.tid)));
                        ui->ProcessDataViewA->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(thread.name)));
                        ui->ProcessDataViewA->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(thread.user)));
                        ui->ProcessDataViewA->setItem(i, 3, new QTableWidgetItem(QString::number(thread.memory)));
                        ui->ProcessDataViewA->setItem(i, 4, new QTableWidgetItem(QString::number(thread.swichContextInvoluntary)));
                        ui->ProcessDataViewA->setItem(i, 5, new QTableWidgetItem(QString::number(thread.swichContextVoluntary)));
                        ui->ProcessDataViewA->setItem(i, 6, new QTableWidgetItem(QString::fromStdString(thread.state)));
                    }
                    // Preencher labels a partir do índice 12 com informações do processo
                    QStringList titles = {
                        "PID", "Nome", "Usuário", "Memória (KB)", "N° Threads",
                        "Trocas Involuntárias", "Trocas Voluntárias", "Estado",
                        "Stack Size (KB)", "Heap Size (KB)"
                    };

                    QStringList values = {
                        QString::fromStdString(process.pid),
                        QString::fromStdString(process.name),
                        QString::fromStdString(process.user),
                        QString::number(process.memory),
                        QString::number(process.threads.size()),
                        QString::number(process.swichContextInvoluntary),
                        QString::number(process.swichContextVoluntary),
                        QString::fromStdString(process.state),
                        QString::number(process.stackSize),
                        QString::number(process.heapSize)
                    };

                    for (int i = 0; i < titles.size(); ++i) {
                        QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i + 12));
                        QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i + 12));
                        
                        if (titleLabel && valueLabel) {
                            titleLabel->setText(titles[i]);
                            valueLabel->setText(values[i]);

                            titleLabel->adjustSize();
                            valueLabel->adjustSize();
                        }
                    }

                    break; // Encerra o loop após encontrar o processo
                } else if (activeButtonChar == FlagButton::ButtonC) {
                    std::cout << "Exibindo informações dos recursos do processo com PID: " << process.pid << std::endl;
                    // Exibir informações dos recursos do processo
                    const Recursos recursos = process.recursos;
                    int nFiles = recursos.arquivos.size();
                    int nSockets = recursos.sockets.size();
                    int totalRows = nFiles + nSockets;
                    QStringList headers = {"Tipo", "Caminho/Endereço Local", "Endereço Remoto", "Estado", "ID Lock Kernel", "Tipo Lock", "Faixa inicio", "Faixa Fim", "Acesso", "Modo"};
                    clearTableWidget(ui->ProcessDataViewA); // Limpa a tabela antes de preencher
                    ui->ProcessDataViewA->clearContents();
                    ui->ProcessDataViewA->clear();
                    ui->ProcessDataViewA->setRowCount(totalRows);
                    ui->ProcessDataViewA->setColumnCount(10);
                    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);
                    int row = 0;
                    // Arquivos abertos
                    for (const ArquivoAberto& arq : recursos.arquivos) {
                        ui->ProcessDataViewA->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(arq.tipo)));
                        ui->ProcessDataViewA->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(arq.caminho)));
                        ui->ProcessDataViewA->setItem(row, 2, new QTableWidgetItem("-"));
                        ui->ProcessDataViewA->setItem(row, 3, new QTableWidgetItem("-"));
                        ui->ProcessDataViewA->setItem(row, 4, new QTableWidgetItem(QString::number(process.fileLock.id)));
                        ui->ProcessDataViewA->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(process.fileLock.tipo)));
                        ui->ProcessDataViewA->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(process.fileLock.faixaInicio)));
                        ui->ProcessDataViewA->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(process.fileLock.faixaFim)));
                        ui->ProcessDataViewA->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(process.fileLock.acesso)));
                        ui->ProcessDataViewA->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(process.fileLock.modo))); 
                        ++row;
                    }
                    // Sockets
                    for (const SocketInfo& sock : recursos.sockets) {
                        ui->ProcessDataViewA->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sock.tipo)));
                        ui->ProcessDataViewA->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(sock.localAddress)));
                        ui->ProcessDataViewA->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(sock.remoteAddress)));
                        ui->ProcessDataViewA->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(sock.state)));
                        ++row;
                    }
                }
            }
        }
    }
}

void MainWindow::onClickedButtonProcess() {
    //std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de processos
    setActiveButton(ui->ProcessButton);
    ui->ProcessDataViewA->clear();
    activeButton = FlagButton::ButtonProcess; // Define o botão ativo como Process
    desativeButtons();
    ui->ProcessButton->setChecked(true);
    ui->stackedWidgetMain->setCurrentIndex(0);
    fileTreeView->hide();
    clearAllTexts();
    ui->titleA->setText("Process Information");
    ui->ButtonA->setText("General");
    ui->ButtonB->setText("Threads");
    ui->ButtonC->setText("Resources");

    ui->inforTitle12->setText("Student 1");
    ui->inforTitle13->setText("Student 2");
    ui->inforTitle14->setText("Teacher");
    ui->inforTitle15->setText("Course");

    ui->infor12->setText("Robson B.");
    ui->infor13->setText("Joao R.");
    ui->infor14->setText("Aurelio");
    ui->infor15->setText("Op. Sistems");

    SystemCallProcesses::getInstance()->updateProcesses();
    const std::vector<InfoBase*>& raw = SystemCallProcesses::getInstance()->getInfo();
    std::vector<ProcessInfo> processes;
    for (InfoBase* base : raw) {
        if (ProcessInfo* process = dynamic_cast<ProcessInfo*>(base)) {
            processes.push_back(*process);
        }
    }
    onProcessListUpdated(processes);
}

void MainWindow::onClickedButtonMemory() {
    setActiveButton(ui->MemoryButton);
    clearAllTexts();
    activeButton = FlagButton::ButtonMemory; // Define o botão ativo como Memory
    ui->ProcessDataViewA->clear();
    desativeButtons();
    ui->MemoryButton->setChecked(true);
    ui->stackedWidgetMain->setCurrentIndex(0);
    fileTreeView->hide();

    SystemCallMemory::getInstance()->updateMemory();
    const std::vector<InfoBase*>& raw = SystemCallMemory::getInstance()->getInfo();
    std::vector<MemoryInfo> memoryList;
    for (InfoBase* base : raw) {
        if (MemoryInfo* memory = dynamic_cast<MemoryInfo*>(base)) {
            memoryList.push_back(*memory); 
        }
    }
    onMemoryListUpdated(memoryList);
}

void MainWindow::onClickedButtonPerformace() {
    setActiveButton(ui->PerformanceButton);
    activeButton = FlagButton::ButtonPerformance; // Define o botão ativo como Performance
    ui->ProcessDataViewA->clear();
    desativeButtons();
    ui->PerformanceButton->setChecked(true);
    ui->stackedWidgetMain->setCurrentIndex(0);
    fileTreeView->hide();
    clearAllTexts();
}

void MainWindow::onClickedButtonFiles() {
    clearAllTexts();
    activeButton = FlagButton::ButtonFiles; // Define o botão ativo como Files
    ui->ButtonA->setText("Void");
    ui->ButtonB->setText("Partitions");
    ui->ButtonC->setText("Students");

    ui->inforTitle12->setText("Student 1");
    ui->inforTitle13->setText("Student 2");
    ui->inforTitle14->setText("Teacher");
    ui->inforTitle15->setText("Course");

    ui->infor12->setText("Robson B.");
    ui->infor13->setText("Joao R.");
    ui->infor14->setText("Aurelio");
    ui->infor15->setText("Op. Sistems");

    setActiveButton(ui->FilesButton);
    // Marcar o botão como ativo e desmarcar os outros
    desativeButtons();
    ui->FilesButton->setChecked(true);
    ui->stackedWidgetMain->setCurrentIndex(1); // muda a pagina que aparece na stack para a árvore de arquivos
    if (fileTreeView) {
        fileTreeView->show();
    }
    // Garantir que está no layout correto (caso ainda não tenha sido adicionado)
    if (ui->frameContent->layout() && !fileTreeView->parent()) {
        ui->frameContent->layout()->addWidget(fileTreeView);
    }
}

void MainWindow::updateGeneralDataPartitions(const std::vector<PartitionInfo> list) {
    if (list.empty()) return;

    ui->stackedWidgetMaster->setCurrentIndex(0);
    clearTableWidget(ui->processTable);
    ui->processTable->clearContents();
    ui->processTable->clear();
    ui->processTable->setRowCount(list.size());
    ui->processTable->setColumnCount(7);

    QStringList headers = {
        "Dispositivo", "Ponto de Montagem", "Tipo de FS",
        "Tamanho Total (MB)", "Usado (MB)", "Disponível (MB)", "Uso (%)"
    };
    ui->processTable->setHorizontalHeaderLabels(headers);

    // Variáveis agregadas
    quint64 totalDiskBytes = 0;
    quint64 usedDiskBytes = 0;
    quint64 availableDiskBytes = 0;
    double totalUsagePercentage = 0.0;

    QString largestPartitionDevice;
    quint64 largestPartitionSize = 0;

    QString rootFsType;
    double rootUsage = -1;

    for (size_t row = 0; row < list.size(); ++row) {
        const PartitionInfo& p = list[row];

        quint64 total = p.totalSize;
        quint64 used = p.usedSize;
        quint64 available = p.availableSize;

        std::cout << "D: " << p.device << std::endl;
        if (p.device == "/dev/nvme0n1" || p.device == "/dev/nvmme0n1p1" || p.device == "/dev/nvmme0n1p2" ||
        p.device == "/dev/nvmme0n1p3" || p.device == "/dev/nvmme0n1p4" || p.device == "/dev/nvmme0n1p5") {
            totalDiskBytes += total;
        }
        usedDiskBytes += used;
        availableDiskBytes += available;
        totalUsagePercentage += p.usagePercentage;

        if (total > largestPartitionSize) {
            largestPartitionSize = total;
            largestPartitionDevice = QString::fromStdString(p.device);
        }

        if (p.mountPoint == "/") {
            rootFsType = QString::fromStdString(p.filesystemType);
            rootUsage = p.usagePercentage;
        }

        ui->processTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.device)));
        ui->processTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.mountPoint)));
        ui->processTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.filesystemType)));
        ui->processTable->setItem(row, 3, new QTableWidgetItem(QString::number(total / 1024 / 1024)));
        ui->processTable->setItem(row, 4, new QTableWidgetItem(QString::number(used / 1024 / 1024)));
        ui->processTable->setItem(row, 5, new QTableWidgetItem(QString::number(available / 1024 / 1024)));
        ui->processTable->setItem(row, 6, new QTableWidgetItem(QString::number(p.usagePercentage, 'f', 2) + "%"));
    }

    int n = static_cast<int>(list.size());
    double avgUsage = n > 0 ? totalUsagePercentage / n : 0.0;

    // Labels de 0 a 11
    QStringList titles = {
        "Partições",
        "Disco Total (GB)",
        "Usado (GB)",
        "Livre (GB)",
        "Uso Médio (%)",
        "Maior Partição",
        "Maior (GB)",
        "FS Raiz",
        "Uso Raiz (%)",
        "", "", ""
    };

    QStringList values;
    values << QString::number(list.size())
           << QString::number(totalDiskBytes / 1024.0 / 1024.0 / 1024.0, 'f', 2)
           << QString::number(usedDiskBytes / 1024.0 / 1024.0 / 1024.0, 'f', 2)
           << QString::number(availableDiskBytes / 1024.0 / 1024.0 / 1024.0, 'f', 2)
           << QString::number(avgUsage, 'f', 2) + "%"
           << largestPartitionDevice
           << QString::number(largestPartitionSize / 1024.0 / 1024.0 / 1024.0, 'f', 2)
           << (rootFsType.isEmpty() ? "-" : rootFsType)
           << (rootUsage >= 0 ? QString::number(rootUsage, 'f', 2) + "%" : "-")
           << "", "", "";

    for (int i = 0; i < titles.size(); ++i) {
        QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i));
        QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i));
        if (titleLabel && valueLabel) {
            titleLabel->setText(titles[i]);
            valueLabel->setText(values.value(i, "-"));
            titleLabel->adjustSize();
            valueLabel->adjustSize();
        }
    }
}


void MainWindow::onClickedButtonPartitions() {
    //std::lock_guard<std::mutex> lock(globalMutex); // Protege o acesso à lista de partições
    clearAllTexts();
    activeButton = FlagButton::ButtonPartitions; // Define o botão ativo como Partitions
    desativeButtons();
    ui->PartitionsButton->setChecked(true);
    setActiveButton(ui->PartitionsButton);
    ui->stackedWidgetMain->setCurrentIndex(0);
    fileTreeView->hide();
    ui->titleA->setText("Partitions Information");
    SystemCallDisk::getInstance()->updateDiskPartitions();
    const std::vector<InfoBase*>& raw = SystemCallDisk::getInstance()->getInfo();
    std::vector<PartitionInfo> partitions;
    for (InfoBase* base : raw) {
        if (PartitionInfo* part = dynamic_cast<PartitionInfo*>(base)) {
            partitions.push_back(*part);
        }
    }
    updateGeneralDataPartitions(partitions);
}

   
void MainWindow::updateGeneralDataProcess(const std::vector<ProcessInfo> list) {
    // if (list.empty() || activeButton != FlagButton::ButtonProcess) {
    //     return; // Se a lista estiver vazia, não faz nada
    // }

    // update = false; // Reseta a flag de atualização

    // int qtdTotalProcessos = list.size();
    
    // int qtdTotalThreads = 0;
    // for (auto &process : list) {
    //     qtdTotalThreads += process.n_threads; // Soma o número de threads de cada processo
    // }

    // unsigned long totalMemory = 0;
    // for (const auto &process : list) {
    //     totalMemory += process.memory; // Soma a memória de cada processo
    // }
    
    // clearTableWidget(ui->GeneralDataView); // Limpa a tabela antes de adicionar novos dados
    // ui->GeneralDataView->clearContents();
    // ui->GeneralDataView->clear(); // Limpa a tabela antes de adicionar novos dados
    // ui->GeneralDataView->setRowCount(1);
    // ui->GeneralDataView->setColumnCount(3); // Duas colunas: Descrição e Valor
    // QStringList headers = {"Total Processes", "Total Threads", "Total Memory (MB)"};
    // ui->GeneralDataView->setHorizontalHeaderLabels(headers);
    // ui->GeneralDataView->setItem(0, 0, new QTableWidgetItem(QString::number(qtdTotalProcessos)));
    // ui->GeneralDataView->setItem(0, 1, new QTableWidgetItem(QString::number(qtdTotalThreads)));
    // ui->GeneralDataView->setItem(0, 2, new QTableWidgetItem(QString::number(totalMemory / 1024))); // Convertendo para MB
    // ui->GeneralDataView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::updateGeneralDataMemory(const std::vector<MemoryInfo> list) {
    if (list.empty() || activeButton != FlagButton::ButtonMemory) {
        return; // Se a lista estiver vazia, não faz nada
    }

}

void MainWindow::onProcessListUpdated(const std::vector<ProcessInfo> list) {
    if (list.empty() || activeButton != FlagButton::ButtonProcess ) {
        return;
    }


    // === Cálculo de métricas ===
    int totalProcessos = list.size();
    int totalThreads = 0;
    unsigned long totalMemoriaKB = 0;
    unsigned long totalHeapKB = 0;
    unsigned long totalStackKB = 0;
    unsigned long totalCtxVoluntary = 0;
    unsigned long totalCtxInvoluntary = 0;

    for (const auto& proc : list) {
        totalThreads += proc.threads.size();
        totalMemoriaKB += proc.memory;
        totalHeapKB += proc.heapSize;
        totalStackKB += proc.stackSize;
        totalCtxVoluntary += proc.swichContextVoluntary;
        totalCtxInvoluntary += proc.swichContextInvoluntary;
    }

    // === Dados agregados nos labels ===
    QStringList titles = {
        "Total de Processos",
        "Total de Threads",
        "Memória Total (MB)",
        "Total Heap (KB)",
        "Total Stack (KB)",
        "Context Switch Voluntary",
        "Context Switch Involuntary"
    };

    QStringList values = {
        QString::number(totalProcessos),
        QString::number(totalThreads),
        QString::number(totalMemoriaKB / 1024), // em MB
        QString::number(totalHeapKB),
        QString::number(totalStackKB),
        QString::number(totalCtxVoluntary),
        QString::number(totalCtxInvoluntary)
    };

    for (int i = 0; i < titles.size(); ++i) {
        QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i));
        QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i));

        if (titleLabel && valueLabel) {
            titleLabel->setText(titles[i]);
            valueLabel->setText(values[i]);
        }
    }

    // === Atualização da tabela (mantida do seu código) ===
    clearTableWidget(ui->processTable);
    ui->processTable->clearContents();
    ui->processTable->clear();
    ui->processTable->setRowCount(list.size());
    update = true;

    ui->processTable->setColumnCount(10);
    QStringList headers = {
        "PID", "Nome", "Usuário", "Memória(KB)", "N Threads",
        "Switch Context Involuntary", "Switch Context Voluntary",
        "State", "Stack Size (KB)", "Heap Size (KB)"
    };
    ui->processTable->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) {
        const ProcessInfo& p = list[row];
        ui->processTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.pid)));
        ui->processTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.name)));
        ui->processTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.user)));
        ui->processTable->setItem(row, 3, new QTableWidgetItem(QString::number(p.memory)));
        ui->processTable->setItem(row, 4, new QTableWidgetItem(QString::number(p.threads.size())));
        ui->processTable->setItem(row, 5, new QTableWidgetItem(QString::number(p.swichContextInvoluntary)));
        ui->processTable->setItem(row, 6, new QTableWidgetItem(QString::number(p.swichContextVoluntary)));
        ui->processTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(p.state)));
        ui->processTable->setItem(row, 8, new QTableWidgetItem(QString::number(p.stackSize)));
        ui->processTable->setItem(row, 9, new QTableWidgetItem(QString::number(p.heapSize)));
    }
    for (int i = 0; i < titles.size(); ++i) {
    QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i));
    QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i));

        if (titleLabel && valueLabel) {
            titleLabel->setText(titles[i]);
            titleLabel->adjustSize();

            valueLabel->setText(values[i]);
            valueLabel->adjustSize();
        }
    }


}


void MainWindow::updateGeneralDataCPU(const std::vector<CPUInfo> list) {
    if (list.empty() || !ui->PerformanceButton->isChecked()) {
        return; // Se a lista estiver vazia, não faz nada
    }
}

void MainWindow::onMemoryListUpdated(const std::vector<MemoryInfo> list) {
    if (list.empty() || activeButton != FlagButton::ButtonMemory) {
        return;
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

    clearTableWidget(ui->ProcessDataViewA);
    ui->ProcessDataViewA->clearContents();
    ui->ProcessDataViewA->clear();
    ui->ProcessDataViewA->setRowCount(1);
    ui->ProcessDataViewA->setColumnCount(5);
    QStringList headers = {"Total (MB)", "Free (MB)", "Used (MB)", "Buffers (MB)", "Cached (MB)"};
    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);

    ui->ProcessDataViewA->setItem(0, 0, new QTableWidgetItem(QString::number(totalMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 1, new QTableWidgetItem(QString::number(freeMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 2, new QTableWidgetItem(QString::number(usedMemory / 1024)));
    ui->ProcessDataViewA->setItem(0, 3, new QTableWidgetItem(QString::number(buffers / 1024)));
    ui->ProcessDataViewA->setItem(0, 4, new QTableWidgetItem(QString::number(cached / 1024)));

    // Estatísticas resumidas nos labels
    float usedPercent = 100.0f * usedMemory / totalMemory;
    float freePercent = 100.0f * freeMemory / totalMemory;
    float buffCachePercent = 100.0f * (buffers + cached) / totalMemory;

    QStringList titles = {
        "Memória Total (MB)",
        "Memória Livre (MB)",
        "Memória Usada (MB)",
        "Buffers (MB)",
        "Cached (MB)",
        "Uso (%)",
        "Livre (%)",
        "Buffers + Cache (%)"
    };

    QStringList values = {
        QString::number(totalMemory / 1024),
        QString::number(freeMemory / 1024),
        QString::number(usedMemory / 1024),
        QString::number(buffers / 1024),
        QString::number(cached / 1024),
        QString::number(usedPercent, 'f', 2) + "%",
        QString::number(freePercent, 'f', 2) + "%",
        QString::number(buffCachePercent, 'f', 2) + "%"
    };

    for (int i = 0; i < titles.size(); ++i) {
        QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i));
        QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i));
        if (titleLabel && valueLabel) {
            titleLabel->setText(titles[i]);
            valueLabel->setText(values[i]);
            titleLabel->adjustSize();
            valueLabel->adjustSize();
        }
    }
}


void MainWindow::onCPUListUpdated(const std::vector<CPUInfo> list) {
    if (list.empty() || activeButton != FlagButton::ButtonPerformance) {
        return;
    }

    clearTableWidget(ui->ProcessDataViewA);
    ui->ProcessDataViewA->clearContents();
    ui->ProcessDataViewA->clear();
    ui->ProcessDataViewA->setRowCount(list.size());
    ui->ProcessDataViewA->setColumnCount(5);

    QStringList headers = {"CPU", "Modelo", "Número do Modelo", "Tempo de Inatividade (%)", "MHz"};
    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);

    float totalIdlePercent = 0.0f;
    float totalUsagePercent = 0.0f;

    for (size_t row = 0; row < list.size(); ++row) {
        const CPUInfo& c = list[row];
        ui->ProcessDataViewA->setItem(row, 0, new QTableWidgetItem(QString::number(c.cpu)));
        ui->ProcessDataViewA->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(c.modelName)));
        ui->ProcessDataViewA->setItem(row, 2, new QTableWidgetItem(QString::number(c.modelNumber)));
        ui->ProcessDataViewA->setItem(row, 3, new QTableWidgetItem(QString::number(c.idleTime, 'f', 2)));
        ui->ProcessDataViewA->setItem(row, 4, new QTableWidgetItem(QString::number(c.cpuMhz)));

        float usagePercent = 100.0f - c.idleTime;
        totalIdlePercent += c.idleTime;
        totalUsagePercent += usagePercent;
    }

    // Média do uso de CPU
    float averageUsage = totalUsagePercent / list.size();

    // Preenche os labels (0 a 11) com métricas relevantes
    QStringList titles = {
        "CPUs Detectadas",
        "Modelo da CPU 0",
        "Número do Modelo da CPU 0",
        "Frequência CPU 0 (MHz)",
        "Uso CPU 0 (%)",
        "Uso CPU 1 (%)",
        "Uso CPU 2 (%)",
        "Uso CPU 3 (%)",
        "Uso CPU 4 (%)",
        "Uso CPU 5 (%)",
        "Uso CPU 6 (%)",
        "Média de Uso (%)"
    };

    QStringList values;
    values << QString::number(list.size());

    if (!list.empty()) {
        const CPUInfo& c0 = list[0];
        values << QString::fromStdString(c0.modelName)
               << QString::number(c0.modelNumber)
               << QString::number(c0.cpuMhz)
               << QString::number(100.0f - c0.idleTime, 'f', 2) + "%";
    }

    // Adiciona uso das CPUs seguintes (até o label 10)
    for (size_t i = 1; i <= 6; ++i) {
        if (i < list.size()) {
            float usage = 100.0f - list[i].idleTime;
            values << QString::number(usage, 'f', 2) + "%";
        } else {
            values << "-";
        }
    }

    // Label 11: média de uso
    values << QString::number(averageUsage, 'f', 2) + "%";

    // Aplicando nos labels
    for (int i = 0; i < titles.size(); ++i) {
        QLabel* titleLabel = findChild<QLabel*>("inforTitle" + QString::number(i));
        QLabel* valueLabel = findChild<QLabel*>("infor" + QString::number(i));
        if (titleLabel && valueLabel) {
            titleLabel->setText(titles[i]);
            valueLabel->setText(values.value(i, "-"));
            titleLabel->adjustSize();
            valueLabel->adjustSize();
        }
    }
}


void MainWindow::onDiskListUpdated(const std::vector<PartitionInfo> list) {
    if (list.empty() || activeButton != FlagButton::ButtonPartitions) {
        return; // Se a lista estiver vazia ou aba de disco não estiver ativa, não faz nada
    }

    clearTableWidget(ui->ProcessDataViewA); // Limpa a tabela antes de adicionar novos dados
    ui->ProcessDataViewA->clearContents();
    ui->ProcessDataViewA->clear();
    ui->ProcessDataViewA->setRowCount(list.size());
    ui->ProcessDataViewA->setColumnCount(7);

    QStringList headers = {
        "Dispositivo", "Ponto de Montagem", "Tipo de FS",
        "Tamanho Total (MB)", "Usado (MB)", "Disponível (MB)", "Uso (%)"
    };
    ui->ProcessDataViewA->setHorizontalHeaderLabels(headers);

    for (size_t row = 0; row < list.size(); ++row) {
        const PartitionInfo& p = list[row];
        ui->ProcessDataViewA->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p.device)));
        ui->ProcessDataViewA->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p.mountPoint)));
        ui->ProcessDataViewA->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p.filesystemType)));
        ui->ProcessDataViewA->setItem(row, 3, new QTableWidgetItem(QString::number(p.totalSize / 1024 / 1024)));
        ui->ProcessDataViewA->setItem(row, 4, new QTableWidgetItem(QString::number(p.usedSize / 1024 / 1024)));
        ui->ProcessDataViewA->setItem(row, 5, new QTableWidgetItem(QString::number(p.availableSize / 1024 / 1024)));
        ui->ProcessDataViewA->setItem(row, 6, new QTableWidgetItem(QString::number(p.usagePercentage, 'f', 2) + "%"));
    }
    update = true;
}

void MainWindow::setActiveButton(QPushButton* active) {
    QList<QPushButton*> buttons = {
        ui->ProcessButton,
        ui->PerformanceButton,
        ui->MemoryButton,
        ui->FilesButton,
        ui->ButtonA,
        ui->ButtonB,
        ui->ButtonC,
        ui->PartitionsButton
    };

    for (QPushButton* button : buttons) {
        if (button == active || button->isChecked()) {
            button->setStyleSheet("background-color: #F15025; color: white;");
        } else {
            button->setStyleSheet("background-color: #D1D1D1; color: gray;");
        }
    }
}

void MainWindow::desativeButtons(){
    QList<QPushButton*> buttons = {
        ui->ProcessButton,
        ui->PerformanceButton,
        ui->MemoryButton,
        ui->FilesButton,
        ui->ButtonA,
        ui->ButtonB,
        ui->ButtonC,
        ui->PartitionsButton
    };

    for (QPushButton* button : buttons) {
        button->setChecked(false);
        button->setStyleSheet("background-color: #D1D1D1; color: gray;");
    }
}

void MainWindow::clearAllTexts() {
    ui->titleA->setText("");

    ui->inforTitle0->setText("");
    ui->inforTitle1->setText("");
    ui->inforTitle2->setText("");
    ui->inforTitle3->setText("");
    ui->inforTitle4->setText("");
    ui->inforTitle5->setText("");
    ui->inforTitle6->setText("");
    ui->inforTitle7->setText("");
    ui->inforTitle8->setText("");
    ui->inforTitle9->setText("");
    ui->inforTitle10->setText("");
    ui->inforTitle11->setText("");
    ui->inforTitle12->setText("");
    ui->inforTitle13->setText("");
    ui->inforTitle14->setText("");
    ui->inforTitle15->setText("");
    ui->inforTitle16->setText("");
    ui->inforTitle17->setText("");
    ui->inforTitle18->setText("");
    ui->inforTitle19->setText("");
    ui->inforTitle20->setText("");
    ui->inforTitle21->setText("");
    ui->inforTitle22->setText("");
    ui->inforTitle23->setText("");
    ui->inforTitle102->setText("");
    ui->inforTitle103->setText("");
    ui->inforTitle104->setText("");
    ui->inforTitle105->setText("");

    ui->infor0->setText("");
    ui->infor1->setText("");
    ui->infor2->setText("");
    ui->infor3->setText("");
    ui->infor4->setText("");
    ui->infor5->setText("");
    ui->infor6->setText("");
    ui->infor7->setText("");
    ui->infor8->setText("");
    ui->infor9->setText("");
    ui->infor10->setText("");
    ui->infor11->setText("");
    ui->infor12->setText("");
    ui->infor13->setText("");
    ui->infor14->setText("");
    ui->infor15->setText("");
    ui->infor16->setText("");
    ui->infor17->setText("");
    ui->infor18->setText("");
    ui->infor19->setText("");
    ui->infor20->setText("");
    ui->infor21->setText("");
    ui->infor22->setText("");
    ui->infor23->setText("");
    ui->infor102->setText("");
    ui->infor103->setText("");
    ui->infor104->setText("");
    ui->infor105->setText("");
}