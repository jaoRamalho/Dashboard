/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
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
        centralwidget->setStyleSheet(QString::fromUtf8("background-color : #252525;"));
        processesView = new QTableWidget(centralwidget);
        if (processesView->columnCount() < 2)
            processesView->setColumnCount(2);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Mono"));
        font.setBold(true);
        font.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        __qtablewidgetitem->setBackground(QColor(36, 31, 49));
        __qtablewidgetitem->setForeground(brush);
        processesView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        processesView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (processesView->rowCount() < 4)
            processesView->setRowCount(4);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setBackground(QColor(36, 31, 49));
        __qtablewidgetitem2->setForeground(brush);
        processesView->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        processesView->setVerticalHeaderItem(1, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        processesView->setVerticalHeaderItem(2, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        processesView->setVerticalHeaderItem(3, __qtablewidgetitem5);
        QBrush brush1(QColor(36, 31, 49, 255));
        brush1.setStyle(Qt::SolidPattern);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        __qtablewidgetitem6->setBackground(brush1);
        __qtablewidgetitem6->setForeground(brush1);
        processesView->setItem(0, 0, __qtablewidgetitem6);
        processesView->setObjectName(QString::fromUtf8("processesView"));
        processesView->setGeometry(QRect(20, 50, 651, 611));
        processesView->setMaximumSize(QSize(16777215, 16777215));
        processesView->setStyleSheet(QString::fromUtf8("QTableWidget {\n"
"    background-color: black;\n"
"	foreground-color:white;\n"
"    color: white;\n"
"    gridline-color: black;\n"
"	alternate-background-color: #252525;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"        background-color: black;\n"
"        color: white;\n"
"        font-weight: bold;\n"
"        border: 1px solid black;\n"
"        padding: 4px;\n"
"    }"));
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
        QTableWidgetItem *___qtablewidgetitem = processesView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "teste col", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = processesView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "bbb", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = processesView->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "teste row", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = processesView->verticalHeaderItem(1);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "ccc", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = processesView->verticalHeaderItem(2);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "New Row", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = processesView->verticalHeaderItem(3);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "fff", nullptr));

        const bool __sortingEnabled = processesView->isSortingEnabled();
        processesView->setSortingEnabled(false);
        processesView->setSortingEnabled(__sortingEnabled);

        processSearchEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
