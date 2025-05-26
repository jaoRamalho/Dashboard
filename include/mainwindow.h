#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <mutex>
#include "include/ProcessInfo.h"



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
    std::mutex processMutex; 
    

private slots:
    void onProcessListUpdated(const std::vector<ProcessInfo*>);
    void onMemoryListUpdated(const std::vector<MemoryInfo*>);
    void onCPUListUpdated(const std::vector<CPUInfo*>);
    void updateGeneralDataProcess(const std::vector<ProcessInfo*>);
    void updateGeneralDataMemory(const std::vector<MemoryInfo*>);
    void updateGeneralDataCPU(const std::vector<CPUInfo*>);

    void onClickedButtonProcess();
    void onClickedButtonMemory();
    void onClickedButtonPerformace();
    void onClickedButtonFiles();
    
    void onProcessTableRowClicked(int row);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
