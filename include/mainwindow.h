#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "include/ProcessInfo.h"

#include <vector>


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
    std::vector<ProcessInfo*> copyProcess;

private slots:
    void onProcessListUpdated(const std::vector<ProcessInfo*>&);
    void onMemoryListUpdated(const std::vector<MemoryInfo*>&);
    void onCPUListUpdated(const std::vector<CPUInfo*>&);
    void onProcessClicked(int row, int column);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
