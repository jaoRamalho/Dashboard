/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableWidget *processesView;
    QLineEdit *processSearchEdit;
    QTableWidget *threadsView;
    QTableWidget *cpuView;
    QTableWidget *memoryView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1228, 719);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setAutoFillBackground(false);
        processesView = new QTableWidget(centralwidget);
        processesView->setObjectName(QString::fromUtf8("processesView"));
        processesView->setGeometry(QRect(20, 50, 651, 611));
        processesView->setMaximumSize(QSize(16777215, 16777215));
        processSearchEdit = new QLineEdit(centralwidget);
        processSearchEdit->setObjectName(QString::fromUtf8("processSearchEdit"));
        processSearchEdit->setGeometry(QRect(20, 10, 651, 31));
        threadsView = new QTableWidget(centralwidget);
        threadsView->setObjectName(QString::fromUtf8("threadsView"));
        threadsView->setGeometry(QRect(680, 10, 531, 291));
        threadsView->setMaximumSize(QSize(16777215, 481));
        cpuView = new QTableWidget(centralwidget);
        cpuView->setObjectName(QString::fromUtf8("cpuView"));
        cpuView->setGeometry(QRect(680, 310, 531, 141));
        cpuView->setMaximumSize(QSize(16777215, 481));
        memoryView = new QTableWidget(centralwidget);
        memoryView->setObjectName(QString::fromUtf8("memoryView"));
        memoryView->setGeometry(QRect(680, 460, 531, 201));
        memoryView->setMaximumSize(QSize(16777215, 481));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1228, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        processSearchEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
