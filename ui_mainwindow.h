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
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_7;
    QFrame *frameContent;
    QStackedWidget *stackedWidgetMain;
    QWidget *pageProcessTable;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_24;
    QLineEdit *processSearchEdit;
    QTableWidget *processTable;
    QWidget *pageFileTree;
    QTreeView *treeView;
    QVBoxLayout *verticalLayout_23;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *ProcessButton;
    QPushButton *PerformanceButton;
    QPushButton *MemoryButton;
    QPushButton *FilesButton;
    QPushButton *PartitionsButton;
    QFrame *frame1;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_9;
    QLabel *titleA;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *inforTitle0;
    QLabel *infor0;
    QVBoxLayout *verticalLayout_2;
    QLabel *inforTitle1;
    QLabel *infor1;
    QVBoxLayout *verticalLayout_3;
    QLabel *inforTitle2;
    QLabel *infor2;
    QVBoxLayout *verticalLayout_4;
    QLabel *inforTitle3;
    QLabel *infor3;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_52;
    QLabel *inforTitle4;
    QLabel *infor4;
    QVBoxLayout *verticalLayout_53;
    QLabel *inforTitle5;
    QLabel *infor5;
    QVBoxLayout *verticalLayout_54;
    QLabel *inforTitle6;
    QLabel *infor6;
    QVBoxLayout *verticalLayout_55;
    QLabel *inforTitle7;
    QLabel *infor7;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *inforTitle8;
    QLabel *infor8;
    QVBoxLayout *verticalLayout_6;
    QLabel *inforTitle9;
    QLabel *infor9;
    QVBoxLayout *verticalLayout_7;
    QLabel *inforTitle10;
    QLabel *infor10;
    QVBoxLayout *verticalLayout_8;
    QLabel *inforTitle11;
    QLabel *infor11;
    QFrame *frame_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout_20;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ButtonA;
    QPushButton *ButtonB;
    QPushButton *ButtonC;
    QStackedWidget *stackedWidgetMaster;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_19;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_11;
    QLabel *inforTitle12;
    QLabel *infor12;
    QVBoxLayout *verticalLayout_12;
    QLabel *inforTitle13;
    QLabel *infor13;
    QVBoxLayout *verticalLayout_13;
    QLabel *inforTitle14;
    QLabel *infor14;
    QVBoxLayout *verticalLayout_14;
    QLabel *inforTitle15;
    QLabel *infor15;
    QHBoxLayout *horizontalLayout_15;
    QVBoxLayout *verticalLayout_56;
    QLabel *inforTitle16;
    QLabel *infor16;
    QVBoxLayout *verticalLayout_57;
    QLabel *inforTitle17;
    QLabel *infor17;
    QVBoxLayout *verticalLayout_58;
    QLabel *inforTitle18;
    QLabel *infor18;
    QVBoxLayout *verticalLayout_59;
    QLabel *inforTitle19;
    QLabel *infor19;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_15;
    QLabel *inforTitle20;
    QLabel *infor20;
    QVBoxLayout *verticalLayout_16;
    QLabel *inforTitle21;
    QLabel *infor21;
    QVBoxLayout *verticalLayout_17;
    QLabel *inforTitle22;
    QLabel *infor22;
    QVBoxLayout *verticalLayout_18;
    QLabel *inforTitle23;
    QLabel *infor23;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_21;
    QTableWidget *ProcessDataViewA;
    QFrame *frame_3;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_25;
    QTableWidget *GeneralDataView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1612, 764);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_7 = new QHBoxLayout(centralwidget);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        frameContent = new QFrame(centralwidget);
        frameContent->setObjectName(QString::fromUtf8("frameContent"));
        frameContent->setMinimumSize(QSize(470, 550));
        frameContent->setStyleSheet(QString::fromUtf8("background-color: #E1E1E1;\n"
"color : black;\n"
"border-radius: 16px;"));
        frameContent->setFrameShape(QFrame::StyledPanel);
        frameContent->setFrameShadow(QFrame::Raised);
        stackedWidgetMain = new QStackedWidget(frameContent);
        stackedWidgetMain->setObjectName(QString::fromUtf8("stackedWidgetMain"));
        stackedWidgetMain->setGeometry(QRect(10, 10, 450, 531));
        stackedWidgetMain->setMinimumSize(QSize(450, 0));
        pageProcessTable = new QWidget();
        pageProcessTable->setObjectName(QString::fromUtf8("pageProcessTable"));
        layoutWidget = new QWidget(pageProcessTable);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 451, 531));
        verticalLayout_24 = new QVBoxLayout(layoutWidget);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(0, 0, 0, 0);
        processSearchEdit = new QLineEdit(layoutWidget);
        processSearchEdit->setObjectName(QString::fromUtf8("processSearchEdit"));

        verticalLayout_24->addWidget(processSearchEdit);

        processTable = new QTableWidget(layoutWidget);
        processTable->setObjectName(QString::fromUtf8("processTable"));

        verticalLayout_24->addWidget(processTable);

        stackedWidgetMain->addWidget(pageProcessTable);
        pageFileTree = new QWidget();
        pageFileTree->setObjectName(QString::fromUtf8("pageFileTree"));
        treeView = new QTreeView(pageFileTree);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(0, 0, 451, 531));
        stackedWidgetMain->addWidget(pageFileTree);

        horizontalLayout_7->addWidget(frameContent);

        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 42));
        frame->setMaximumSize(QSize(16777215, 42));
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        ProcessButton = new QPushButton(frame);
        ProcessButton->setObjectName(QString::fromUtf8("ProcessButton"));
        ProcessButton->setMinimumSize(QSize(90, 40));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        ProcessButton->setFont(font);
        ProcessButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(ProcessButton);

        PerformanceButton = new QPushButton(frame);
        PerformanceButton->setObjectName(QString::fromUtf8("PerformanceButton"));
        PerformanceButton->setMinimumSize(QSize(120, 40));
        PerformanceButton->setFont(font);
        PerformanceButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(PerformanceButton);

        MemoryButton = new QPushButton(frame);
        MemoryButton->setObjectName(QString::fromUtf8("MemoryButton"));
        MemoryButton->setMinimumSize(QSize(80, 40));
        MemoryButton->setFont(font);
        MemoryButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(MemoryButton);

        FilesButton = new QPushButton(frame);
        FilesButton->setObjectName(QString::fromUtf8("FilesButton"));
        FilesButton->setMinimumSize(QSize(60, 40));
        FilesButton->setFont(font);
        FilesButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(FilesButton);

        PartitionsButton = new QPushButton(frame);
        PartitionsButton->setObjectName(QString::fromUtf8("PartitionsButton"));
        PartitionsButton->setMinimumSize(QSize(60, 40));
        PartitionsButton->setFont(font);
        PartitionsButton->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout->addWidget(PartitionsButton);


        verticalLayout_23->addWidget(frame);

        frame1 = new QFrame(centralwidget);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame1->sizePolicy().hasHeightForWidth());
        frame1->setSizePolicy(sizePolicy);
        frame1->setMinimumSize(QSize(0, 190));
        frame1->setStyleSheet(QString::fromUtf8("background-color: #E1E1E1;\n"
"color : black;\n"
"border-radius: 16px;"));
        frame1->setFrameShape(QFrame::StyledPanel);
        frame1->setFrameShadow(QFrame::Raised);
        layoutWidget1 = new QWidget(frame1);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 571, 192));
        verticalLayout_9 = new QVBoxLayout(layoutWidget1);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_9->setContentsMargins(0, 0, 0, 6);
        titleA = new QLabel(layoutWidget1);
        titleA->setObjectName(QString::fromUtf8("titleA"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        titleA->setFont(font1);

        verticalLayout_9->addWidget(titleA);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalLayout_2->setContentsMargins(0, -1, -1, -1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        inforTitle0 = new QLabel(layoutWidget1);
        inforTitle0->setObjectName(QString::fromUtf8("inforTitle0"));
        inforTitle0->setFont(font);

        verticalLayout->addWidget(inforTitle0);

        infor0 = new QLabel(layoutWidget1);
        infor0->setObjectName(QString::fromUtf8("infor0"));

        verticalLayout->addWidget(infor0);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        inforTitle1 = new QLabel(layoutWidget1);
        inforTitle1->setObjectName(QString::fromUtf8("inforTitle1"));
        inforTitle1->setFont(font);

        verticalLayout_2->addWidget(inforTitle1);

        infor1 = new QLabel(layoutWidget1);
        infor1->setObjectName(QString::fromUtf8("infor1"));

        verticalLayout_2->addWidget(infor1);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        inforTitle2 = new QLabel(layoutWidget1);
        inforTitle2->setObjectName(QString::fromUtf8("inforTitle2"));
        inforTitle2->setFont(font);

        verticalLayout_3->addWidget(inforTitle2);

        infor2 = new QLabel(layoutWidget1);
        infor2->setObjectName(QString::fromUtf8("infor2"));

        verticalLayout_3->addWidget(infor2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        inforTitle3 = new QLabel(layoutWidget1);
        inforTitle3->setObjectName(QString::fromUtf8("inforTitle3"));
        inforTitle3->setFont(font);

        verticalLayout_4->addWidget(inforTitle3);

        infor3 = new QLabel(layoutWidget1);
        infor3->setObjectName(QString::fromUtf8("infor3"));

        verticalLayout_4->addWidget(infor3);


        horizontalLayout_2->addLayout(verticalLayout_4);


        verticalLayout_9->addLayout(horizontalLayout_2);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(10);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setSizeConstraint(QLayout::SetMinAndMaxSize);
        horizontalLayout_14->setContentsMargins(0, -1, -1, -1);
        verticalLayout_52 = new QVBoxLayout();
        verticalLayout_52->setObjectName(QString::fromUtf8("verticalLayout_52"));
        inforTitle4 = new QLabel(layoutWidget1);
        inforTitle4->setObjectName(QString::fromUtf8("inforTitle4"));
        inforTitle4->setFont(font);

        verticalLayout_52->addWidget(inforTitle4);

        infor4 = new QLabel(layoutWidget1);
        infor4->setObjectName(QString::fromUtf8("infor4"));

        verticalLayout_52->addWidget(infor4);


        horizontalLayout_14->addLayout(verticalLayout_52);

        verticalLayout_53 = new QVBoxLayout();
        verticalLayout_53->setObjectName(QString::fromUtf8("verticalLayout_53"));
        inforTitle5 = new QLabel(layoutWidget1);
        inforTitle5->setObjectName(QString::fromUtf8("inforTitle5"));
        inforTitle5->setFont(font);

        verticalLayout_53->addWidget(inforTitle5);

        infor5 = new QLabel(layoutWidget1);
        infor5->setObjectName(QString::fromUtf8("infor5"));

        verticalLayout_53->addWidget(infor5);


        horizontalLayout_14->addLayout(verticalLayout_53);

        verticalLayout_54 = new QVBoxLayout();
        verticalLayout_54->setObjectName(QString::fromUtf8("verticalLayout_54"));
        inforTitle6 = new QLabel(layoutWidget1);
        inforTitle6->setObjectName(QString::fromUtf8("inforTitle6"));
        inforTitle6->setFont(font);

        verticalLayout_54->addWidget(inforTitle6);

        infor6 = new QLabel(layoutWidget1);
        infor6->setObjectName(QString::fromUtf8("infor6"));

        verticalLayout_54->addWidget(infor6);


        horizontalLayout_14->addLayout(verticalLayout_54);

        verticalLayout_55 = new QVBoxLayout();
        verticalLayout_55->setObjectName(QString::fromUtf8("verticalLayout_55"));
        inforTitle7 = new QLabel(layoutWidget1);
        inforTitle7->setObjectName(QString::fromUtf8("inforTitle7"));
        inforTitle7->setFont(font);

        verticalLayout_55->addWidget(inforTitle7);

        infor7 = new QLabel(layoutWidget1);
        infor7->setObjectName(QString::fromUtf8("infor7"));

        verticalLayout_55->addWidget(infor7);


        horizontalLayout_14->addLayout(verticalLayout_55);


        verticalLayout_9->addLayout(horizontalLayout_14);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        inforTitle8 = new QLabel(layoutWidget1);
        inforTitle8->setObjectName(QString::fromUtf8("inforTitle8"));
        inforTitle8->setFont(font);

        verticalLayout_5->addWidget(inforTitle8);

        infor8 = new QLabel(layoutWidget1);
        infor8->setObjectName(QString::fromUtf8("infor8"));

        verticalLayout_5->addWidget(infor8);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        inforTitle9 = new QLabel(layoutWidget1);
        inforTitle9->setObjectName(QString::fromUtf8("inforTitle9"));
        inforTitle9->setFont(font);

        verticalLayout_6->addWidget(inforTitle9);

        infor9 = new QLabel(layoutWidget1);
        infor9->setObjectName(QString::fromUtf8("infor9"));

        verticalLayout_6->addWidget(infor9);


        horizontalLayout_3->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        inforTitle10 = new QLabel(layoutWidget1);
        inforTitle10->setObjectName(QString::fromUtf8("inforTitle10"));
        inforTitle10->setFont(font);

        verticalLayout_7->addWidget(inforTitle10);

        infor10 = new QLabel(layoutWidget1);
        infor10->setObjectName(QString::fromUtf8("infor10"));

        verticalLayout_7->addWidget(infor10);


        horizontalLayout_3->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        inforTitle11 = new QLabel(layoutWidget1);
        inforTitle11->setObjectName(QString::fromUtf8("inforTitle11"));
        inforTitle11->setFont(font);

        verticalLayout_8->addWidget(inforTitle11);

        infor11 = new QLabel(layoutWidget1);
        infor11->setObjectName(QString::fromUtf8("infor11"));

        verticalLayout_8->addWidget(infor11);


        horizontalLayout_3->addLayout(verticalLayout_8);


        verticalLayout_9->addLayout(horizontalLayout_3);


        verticalLayout_23->addWidget(frame1);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(0, 230));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: #E1E1E1;\n"
"color : black;\n"
"border-radius: 16px;"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        widget = new QWidget(frame_2);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 581, 261));
        verticalLayout_20 = new QVBoxLayout(widget);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_20->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        ButtonA = new QPushButton(widget);
        ButtonA->setObjectName(QString::fromUtf8("ButtonA"));
        ButtonA->setMinimumSize(QSize(90, 40));
        ButtonA->setFont(font);
        ButtonA->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout_4->addWidget(ButtonA);

        ButtonB = new QPushButton(widget);
        ButtonB->setObjectName(QString::fromUtf8("ButtonB"));
        ButtonB->setMinimumSize(QSize(120, 40));
        ButtonB->setFont(font);
        ButtonB->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout_4->addWidget(ButtonB);

        ButtonC = new QPushButton(widget);
        ButtonC->setObjectName(QString::fromUtf8("ButtonC"));
        ButtonC->setMinimumSize(QSize(100, 40));
        ButtonC->setFont(font);
        ButtonC->setStyleSheet(QString::fromUtf8("background-color: #F15025;\n"
"color : white;\n"
"border-radius: 16px;"));

        horizontalLayout_4->addWidget(ButtonC);


        verticalLayout_20->addLayout(horizontalLayout_4);

        stackedWidgetMaster = new QStackedWidget(widget);
        stackedWidgetMaster->setObjectName(QString::fromUtf8("stackedWidgetMaster"));
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_19 = new QVBoxLayout(page_3);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        inforTitle12 = new QLabel(page_3);
        inforTitle12->setObjectName(QString::fromUtf8("inforTitle12"));
        inforTitle12->setFont(font);

        verticalLayout_11->addWidget(inforTitle12);

        infor12 = new QLabel(page_3);
        infor12->setObjectName(QString::fromUtf8("infor12"));

        verticalLayout_11->addWidget(infor12);


        horizontalLayout_5->addLayout(verticalLayout_11);

        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        inforTitle13 = new QLabel(page_3);
        inforTitle13->setObjectName(QString::fromUtf8("inforTitle13"));
        inforTitle13->setFont(font);

        verticalLayout_12->addWidget(inforTitle13);

        infor13 = new QLabel(page_3);
        infor13->setObjectName(QString::fromUtf8("infor13"));

        verticalLayout_12->addWidget(infor13);


        horizontalLayout_5->addLayout(verticalLayout_12);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        inforTitle14 = new QLabel(page_3);
        inforTitle14->setObjectName(QString::fromUtf8("inforTitle14"));
        inforTitle14->setFont(font);

        verticalLayout_13->addWidget(inforTitle14);

        infor14 = new QLabel(page_3);
        infor14->setObjectName(QString::fromUtf8("infor14"));

        verticalLayout_13->addWidget(infor14);


        horizontalLayout_5->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        inforTitle15 = new QLabel(page_3);
        inforTitle15->setObjectName(QString::fromUtf8("inforTitle15"));
        inforTitle15->setFont(font);

        verticalLayout_14->addWidget(inforTitle15);

        infor15 = new QLabel(page_3);
        infor15->setObjectName(QString::fromUtf8("infor15"));

        verticalLayout_14->addWidget(infor15);


        horizontalLayout_5->addLayout(verticalLayout_14);


        verticalLayout_10->addLayout(horizontalLayout_5);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        verticalLayout_56 = new QVBoxLayout();
        verticalLayout_56->setObjectName(QString::fromUtf8("verticalLayout_56"));
        inforTitle16 = new QLabel(page_3);
        inforTitle16->setObjectName(QString::fromUtf8("inforTitle16"));
        inforTitle16->setFont(font);

        verticalLayout_56->addWidget(inforTitle16);

        infor16 = new QLabel(page_3);
        infor16->setObjectName(QString::fromUtf8("infor16"));

        verticalLayout_56->addWidget(infor16);


        horizontalLayout_15->addLayout(verticalLayout_56);

        verticalLayout_57 = new QVBoxLayout();
        verticalLayout_57->setObjectName(QString::fromUtf8("verticalLayout_57"));
        inforTitle17 = new QLabel(page_3);
        inforTitle17->setObjectName(QString::fromUtf8("inforTitle17"));
        inforTitle17->setFont(font);

        verticalLayout_57->addWidget(inforTitle17);

        infor17 = new QLabel(page_3);
        infor17->setObjectName(QString::fromUtf8("infor17"));

        verticalLayout_57->addWidget(infor17);


        horizontalLayout_15->addLayout(verticalLayout_57);

        verticalLayout_58 = new QVBoxLayout();
        verticalLayout_58->setObjectName(QString::fromUtf8("verticalLayout_58"));
        inforTitle18 = new QLabel(page_3);
        inforTitle18->setObjectName(QString::fromUtf8("inforTitle18"));
        inforTitle18->setFont(font);

        verticalLayout_58->addWidget(inforTitle18);

        infor18 = new QLabel(page_3);
        infor18->setObjectName(QString::fromUtf8("infor18"));

        verticalLayout_58->addWidget(infor18);


        horizontalLayout_15->addLayout(verticalLayout_58);

        verticalLayout_59 = new QVBoxLayout();
        verticalLayout_59->setObjectName(QString::fromUtf8("verticalLayout_59"));
        inforTitle19 = new QLabel(page_3);
        inforTitle19->setObjectName(QString::fromUtf8("inforTitle19"));
        inforTitle19->setFont(font);

        verticalLayout_59->addWidget(inforTitle19);

        infor19 = new QLabel(page_3);
        infor19->setObjectName(QString::fromUtf8("infor19"));

        verticalLayout_59->addWidget(infor19);


        horizontalLayout_15->addLayout(verticalLayout_59);


        verticalLayout_10->addLayout(horizontalLayout_15);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        inforTitle20 = new QLabel(page_3);
        inforTitle20->setObjectName(QString::fromUtf8("inforTitle20"));
        inforTitle20->setFont(font);

        verticalLayout_15->addWidget(inforTitle20);

        infor20 = new QLabel(page_3);
        infor20->setObjectName(QString::fromUtf8("infor20"));

        verticalLayout_15->addWidget(infor20);


        horizontalLayout_6->addLayout(verticalLayout_15);

        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        inforTitle21 = new QLabel(page_3);
        inforTitle21->setObjectName(QString::fromUtf8("inforTitle21"));
        inforTitle21->setFont(font);

        verticalLayout_16->addWidget(inforTitle21);

        infor21 = new QLabel(page_3);
        infor21->setObjectName(QString::fromUtf8("infor21"));

        verticalLayout_16->addWidget(infor21);


        horizontalLayout_6->addLayout(verticalLayout_16);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        inforTitle22 = new QLabel(page_3);
        inforTitle22->setObjectName(QString::fromUtf8("inforTitle22"));
        inforTitle22->setFont(font);

        verticalLayout_17->addWidget(inforTitle22);

        infor22 = new QLabel(page_3);
        infor22->setObjectName(QString::fromUtf8("infor22"));

        verticalLayout_17->addWidget(infor22);


        horizontalLayout_6->addLayout(verticalLayout_17);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        inforTitle23 = new QLabel(page_3);
        inforTitle23->setObjectName(QString::fromUtf8("inforTitle23"));
        inforTitle23->setFont(font);

        verticalLayout_18->addWidget(inforTitle23);

        infor23 = new QLabel(page_3);
        infor23->setObjectName(QString::fromUtf8("infor23"));

        verticalLayout_18->addWidget(infor23);


        horizontalLayout_6->addLayout(verticalLayout_18);


        verticalLayout_10->addLayout(horizontalLayout_6);


        verticalLayout_19->addLayout(verticalLayout_10);

        stackedWidgetMaster->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        verticalLayout_21 = new QVBoxLayout(page_4);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        ProcessDataViewA = new QTableWidget(page_4);
        ProcessDataViewA->setObjectName(QString::fromUtf8("ProcessDataViewA"));

        verticalLayout_21->addWidget(ProcessDataViewA);

        stackedWidgetMaster->addWidget(page_4);

        verticalLayout_20->addWidget(stackedWidgetMaster);


        verticalLayout_23->addWidget(frame_2);


        horizontalLayout_7->addLayout(verticalLayout_23);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(420, 610));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        layoutWidget2 = new QWidget(frame_3);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(7, 10, 401, 591));
        verticalLayout_25 = new QVBoxLayout(layoutWidget2);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 0, 0, 0);
        GeneralDataView = new QTableWidget(layoutWidget2);
        GeneralDataView->setObjectName(QString::fromUtf8("GeneralDataView"));

        verticalLayout_25->addWidget(GeneralDataView);


        horizontalLayout_7->addWidget(frame_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1612, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidgetMain->setCurrentIndex(1);
        stackedWidgetMaster->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        ProcessButton->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        PerformanceButton->setText(QCoreApplication::translate("MainWindow", "Performance", nullptr));
        MemoryButton->setText(QCoreApplication::translate("MainWindow", "Memory", nullptr));
        FilesButton->setText(QCoreApplication::translate("MainWindow", "Files", nullptr));
        PartitionsButton->setText(QCoreApplication::translate("MainWindow", "Partitions", nullptr));
        titleA->setText(QCoreApplication::translate("MainWindow", "General Process Metrics", nullptr));
        inforTitle0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor0->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor4->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor5->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor6->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle7->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor7->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor8->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle9->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor9->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle10->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor10->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle11->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor11->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        ButtonA->setText(QCoreApplication::translate("MainWindow", "General", nullptr));
        ButtonB->setText(QCoreApplication::translate("MainWindow", "Threads", nullptr));
        ButtonC->setText(QCoreApplication::translate("MainWindow", "Resources", nullptr));
        inforTitle12->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor12->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle13->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor13->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle14->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor14->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle15->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor15->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle16->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor16->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle17->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor17->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle18->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor18->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle19->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor19->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle20->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor20->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle21->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor21->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle22->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor22->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        inforTitle23->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        infor23->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
