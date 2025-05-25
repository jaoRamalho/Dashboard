#include "include/mainwindow.h"
#include "include/ThreadManager.hpp"
#include "include/DataProvider.hpp"
#include "include/SystemCall.hpp"
#include "include/SystemCallProcesses.hpp"
#include "include/SystemCallMemory.hpp"
#include "include/ProcessInfo.h"
#include "include/MyObject.hpp"
#include "include/ProcessInfo.h"
#include "include/SystemCallCPU.hpp"



#include <QMetaType>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>


int main(int argc, char *argv[])
{
    qRegisterMetaType<std::vector<InfoBase*>>("std::vector<InfoBase*>");
    qRegisterMetaType<std::vector<ProcessInfo*>>("std::vector<ProcessInfo*>");
    qRegisterMetaType<std::vector<CPUInfo*>>("std::vector<CPUInfo*>");
    qRegisterMetaType<std::vector<MemoryInfo*>>("std::vector<MemoryInfo*>");
    QApplication a(argc, argv);

    
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "dashboard_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    
    
    ThreadManager* threadManager = new ThreadManager();
    SystemCallMemory* sysCallMemory = SystemCallMemory::getInstance();
    SystemCallProcesses* sysCallProcesses = SystemCallProcesses::getInstance();
    SystemCallCPU* sysCallCPU = SystemCallCPU::getInstance();
    DataProvider* dataProvider = DataProvider::getInstance();


    threadManager->startNewThread(sysCallMemory);
    threadManager->startNewThread(sysCallProcesses);
    threadManager->startNewThread(sysCallCPU);
    threadManager->startNewThread(dataProvider);

    MainWindow w;
    w.show();
    a.exec();
    std::cout << "Main window closed" << std::endl;
    std::cout << "Stopping threads..." << std::endl;

    sysCallCPU->stop();
    sysCallMemory->stop();
    sysCallProcesses->stop();
    dataProvider->stop();
    threadManager->stopAll();
    return 0;
}
