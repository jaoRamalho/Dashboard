#include "include/mainwindow.h"
#include "include/ThreadManager.hpp"
#include "include/DataProvider.hpp"
#include "include/SystemCall.hpp"

#include <QMetaType>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>


int main(int argc, char *argv[])
{
    qRegisterMetaType<std::vector<ProcessInfo>>("std::vector<ProcessInfo>");
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
    DataProvider* dataProvider = DataProvider::getInstance();
    SystemCall* sysCall = SystemCall::getInstance();
    
    threadManager->startNewThread("SystemCall", sysCall);
    threadManager->startNewThread("DataProvider", dataProvider);

    MainWindow w;
    w.show();
    a.exec();

    std::cout << "Stopping threads..." << std::endl;
    dataProvider->stop();
    sysCall->stop();
    threadManager->stopAll();
    return 0;
}
