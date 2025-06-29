#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mutex>
#include "include/ProcessInfo.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool update = false; // Flag para verificar se a linha da tabela foi clicada
    QTreeView* fileTreeView = nullptr;
    QTableWidget* processTableWidget = nullptr;
    QFileSystemModel* fileSystemModel = nullptr;
    void showFileTreeView(const QString& path);
    void showTableView();

private slots:
    void onProcessListUpdated(const std::vector<ProcessInfo>);
    void onMemoryListUpdated(const std::vector<MemoryInfo>);
    void onCPUListUpdated(const std::vector<CPUInfo>);
    void onDiskListUpdated(const std::vector<PartitionInfo>);
    void updateGeneralDataProcess(const std::vector<ProcessInfo>);
    void updateGeneralDataMemory(const std::vector<MemoryInfo>);
    void updateGeneralDataCPU(const std::vector<CPUInfo>);
    void updateGeneralDataPartitions(const std::vector<PartitionInfo> list);
    //void updateGeneralDataDisk(const std::vector<PartitionInfo*>);
    void onClickedButtonPartitions();
    void onClickedButtonProcess();
    void onClickedButtonMemory();
    void onClickedButtonPerformace();
    void onClickedButtonFiles();
    void desativeButtons();
    //void onClickedButtonPartitions();
    void setActiveButton(QPushButton* active);
    void clearAllTexts();
    void onClikedButtonA();
    void onClikedButtonB();
    void onClikedButtonC();

    void onProcessTableRowClicked(int row);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
