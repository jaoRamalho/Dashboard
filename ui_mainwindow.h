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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *processSearchEdit;
    QTableWidget *processTable;
    QFrame *frame;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ProcessButton;
    QPushButton *ProcessButton_2;
    QPushButton *ProcessButton_4;
    QPushButton *ProcessButton_3;
    QFrame *frame_2;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QFrame *FrameIconProcess_2;
    QLabel *generaltitle;
    QTableView *GeneralDataView;
    QFrame *frame_3;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QFrame *FrameIconProcess_3;
    QLabel *processname;
    QTableView *ProcessDataViewA;
    QTableView *ProcessDataViewB;
    QTableView *ProcessDataViewC;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1080, 720);
        MainWindow->setMinimumSize(QSize(1080, 720));
        MainWindow->setMaximumSize(QSize(1080, 720));
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: #151515;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setAutoFillBackground(false);
        frame_4 = new QFrame(centralwidget);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(0, 10, 540, 650));
        frame_4->setMinimumSize(QSize(540, 650));
        frame_4->setMaximumSize(QSize(540, 650));
        frame_4->setStyleSheet(QString::fromUtf8("background-color: #252525;\n"
"border-radius: 16px;\n"
""));
        frame_4->setFrameShape(QFrame::NoFrame);
        verticalLayoutWidget = new QWidget(frame_4);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 30, 501, 511));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        processSearchEdit = new QLineEdit(verticalLayoutWidget);
        processSearchEdit->setObjectName(QString::fromUtf8("processSearchEdit"));

        verticalLayout->addWidget(processSearchEdit);

        processTable = new QTableWidget(verticalLayoutWidget);
        processTable->setObjectName(QString::fromUtf8("processTable"));
        processTable->setMaximumSize(QSize(16777215, 481));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush);
        QBrush brush2(QColor(255, 255, 220, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush2);
        QBrush brush3(QColor(36, 31, 49, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush4);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        processTable->setPalette(palette);

        verticalLayout->addWidget(processTable);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(560, 10, 510, 50));
        frame->setMinimumSize(QSize(0, 0));
        frame->setMaximumSize(QSize(510, 50));
        frame->setStyleSheet(QString::fromUtf8("background-color: #252525;\n"
"border-radius: 16px;"));
        frame->setFrameShape(QFrame::NoFrame);
        horizontalLayoutWidget = new QWidget(frame);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 459, 32));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ProcessButton = new QPushButton(horizontalLayoutWidget);
        ProcessButton->setObjectName(QString::fromUtf8("ProcessButton"));
        ProcessButton->setMinimumSize(QSize(100, 30));
        ProcessButton->setMaximumSize(QSize(100, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        ProcessButton->setFont(font);
        ProcessButton->setAutoFillBackground(false);
        ProcessButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(ProcessButton);

        ProcessButton_2 = new QPushButton(horizontalLayoutWidget);
        ProcessButton_2->setObjectName(QString::fromUtf8("ProcessButton_2"));
        ProcessButton_2->setMinimumSize(QSize(160, 30));
        ProcessButton_2->setMaximumSize(QSize(160, 30));
        ProcessButton_2->setFont(font);
        ProcessButton_2->setAutoFillBackground(false);
        ProcessButton_2->setStyleSheet(QString::fromUtf8("background-color: #151515;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(ProcessButton_2);

        ProcessButton_4 = new QPushButton(horizontalLayoutWidget);
        ProcessButton_4->setObjectName(QString::fromUtf8("ProcessButton_4"));
        ProcessButton_4->setMinimumSize(QSize(0, 0));
        ProcessButton_4->setMaximumSize(QSize(100, 30));
        ProcessButton_4->setFont(font);
        ProcessButton_4->setAutoFillBackground(false);
        ProcessButton_4->setStyleSheet(QString::fromUtf8("background-color: #151515;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(ProcessButton_4);

        ProcessButton_3 = new QPushButton(horizontalLayoutWidget);
        ProcessButton_3->setObjectName(QString::fromUtf8("ProcessButton_3"));
        ProcessButton_3->setMinimumSize(QSize(0, 0));
        ProcessButton_3->setMaximumSize(QSize(100, 30));
        ProcessButton_3->setFont(font);
        ProcessButton_3->setAutoFillBackground(false);
        ProcessButton_3->setStyleSheet(QString::fromUtf8("background-color: #151515;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(ProcessButton_3);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(560, 70, 501, 181));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #252525;\n"
"border-radius: 16px;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_2 = new QWidget(frame_2);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 10, 311, 62));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        FrameIconProcess_2 = new QFrame(horizontalLayoutWidget_2);
        FrameIconProcess_2->setObjectName(QString::fromUtf8("FrameIconProcess_2"));
        FrameIconProcess_2->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FrameIconProcess_2->sizePolicy().hasHeightForWidth());
        FrameIconProcess_2->setSizePolicy(sizePolicy1);
        FrameIconProcess_2->setMinimumSize(QSize(40, 40));
        FrameIconProcess_2->setMaximumSize(QSize(40, 40));
        FrameIconProcess_2->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"border-radius: 16px;"));
        FrameIconProcess_2->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(FrameIconProcess_2);

        generaltitle = new QLabel(horizontalLayoutWidget_2);
        generaltitle->setObjectName(QString::fromUtf8("generaltitle"));
        generaltitle->setMinimumSize(QSize(0, 0));
        generaltitle->setMaximumSize(QSize(250, 40));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Noto Sans Carian"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        generaltitle->setFont(font1);
        generaltitle->setStyleSheet(QString::fromUtf8("color: white;"));

        horizontalLayout_2->addWidget(generaltitle);

        GeneralDataView = new QTableView(frame_2);
        GeneralDataView->setObjectName(QString::fromUtf8("GeneralDataView"));
        GeneralDataView->setGeometry(QRect(20, 100, 451, 61));
        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(560, 270, 501, 391));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: #252525;\n"
"border-radius: 16px;"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayoutWidget_3 = new QWidget(frame_3);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 10, 311, 62));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        FrameIconProcess_3 = new QFrame(horizontalLayoutWidget_3);
        FrameIconProcess_3->setObjectName(QString::fromUtf8("FrameIconProcess_3"));
        FrameIconProcess_3->setEnabled(false);
        sizePolicy1.setHeightForWidth(FrameIconProcess_3->sizePolicy().hasHeightForWidth());
        FrameIconProcess_3->setSizePolicy(sizePolicy1);
        FrameIconProcess_3->setMinimumSize(QSize(40, 40));
        FrameIconProcess_3->setMaximumSize(QSize(40, 40));
        FrameIconProcess_3->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"border-radius: 16px;"));
        FrameIconProcess_3->setFrameShape(QFrame::NoFrame);

        horizontalLayout_3->addWidget(FrameIconProcess_3);

        processname = new QLabel(horizontalLayoutWidget_3);
        processname->setObjectName(QString::fromUtf8("processname"));
        processname->setMinimumSize(QSize(0, 0));
        processname->setMaximumSize(QSize(250, 40));
        processname->setFont(font1);
        processname->setStyleSheet(QString::fromUtf8("color: white;"));

        horizontalLayout_3->addWidget(processname);

        ProcessDataViewA = new QTableView(frame_3);
        ProcessDataViewA->setObjectName(QString::fromUtf8("ProcessDataViewA"));
        ProcessDataViewA->setGeometry(QRect(20, 100, 451, 61));
        ProcessDataViewB = new QTableView(frame_3);
        ProcessDataViewB->setObjectName(QString::fromUtf8("ProcessDataViewB"));
        ProcessDataViewB->setGeometry(QRect(20, 190, 451, 61));
        ProcessDataViewC = new QTableView(frame_3);
        ProcessDataViewC->setObjectName(QString::fromUtf8("ProcessDataViewC"));
        ProcessDataViewC->setGeometry(QRect(30, 290, 451, 61));
        MainWindow->setCentralWidget(centralwidget);
        frame_2->raise();
        frame_4->raise();
        frame->raise();
        frame_3->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1080, 24));
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
        ProcessButton->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        ProcessButton_2->setText(QCoreApplication::translate("MainWindow", "Performance", nullptr));
        ProcessButton_4->setText(QCoreApplication::translate("MainWindow", "Memory", nullptr));
        ProcessButton_3->setText(QCoreApplication::translate("MainWindow", "Files", nullptr));
        generaltitle->setText(QCoreApplication::translate("MainWindow", "General data ", nullptr));
        processname->setText(QCoreApplication::translate("MainWindow", "Process data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
