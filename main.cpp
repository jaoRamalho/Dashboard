#include "include/mainwindow.h"
#include "include/Dashboard.hpp"


#include <QMetaType>
#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <iostream>

int main(int argc, char *argv[])
{
    qRegisterMetaType<std::vector<InfoBase*>>("std::vector<InfoBase*>");
    qRegisterMetaType<std::vector<ProcessInfo>>("std::vector<ProcessInfo>");
    qRegisterMetaType<std::vector<CPUInfo>>("std::vector<CPUInfo>");
    qRegisterMetaType<std::vector<MemoryInfo>>("std::vector<MemoryInfo>");
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
    
    Dashboard* dashboard = new Dashboard();
    dashboard->start();
    MainWindow w;
    w.show();
    int r = a.exec();
    dashboard->stop();

    delete dashboard; // Libera a memória alocada
    
    return r;
}
