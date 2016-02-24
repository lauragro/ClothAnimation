/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <openglwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    OpenGLWidget *openGLWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLCDNumber *lcd_mass;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_7;
    QLCDNumber *lcd_spring_constant;
    QLabel *label_4;
    QLCDNumber *lcd_rest_length;
    QLabel *label_3;
    QLabel *label_5;
    QLabel *label_8;
    QLCDNumber *lcd_damping_constant;
    QDoubleSpinBox *box1;
    QDoubleSpinBox *box3;
    QDoubleSpinBox *box2;
    QDoubleSpinBox *box4;
    QLabel *label;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1107, 676);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        openGLWidget = new OpenGLWidget(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(20, 20, 801, 601));
        QFont font;
        font.setPointSize(16);
        openGLWidget->setFont(font);
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(850, 70, 251, 421));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);
        label_2->setWordWrap(true);

        gridLayout->addWidget(label_2, 4, 1, 1, 1);

        lcd_mass = new QLCDNumber(gridLayoutWidget);
        lcd_mass->setObjectName(QStringLiteral("lcd_mass"));
        lcd_mass->setFrameShape(QFrame::NoFrame);
        lcd_mass->setDigitCount(4);
        lcd_mass->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcd_mass, 3, 3, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font);

        gridLayout->addWidget(label_9, 4, 4, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 1, 4, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 2, 4, 1, 1);

        lcd_spring_constant = new QLCDNumber(gridLayoutWidget);
        lcd_spring_constant->setObjectName(QStringLiteral("lcd_spring_constant"));
        lcd_spring_constant->setFrameShape(QFrame::NoFrame);
        lcd_spring_constant->setDigitCount(4);
        lcd_spring_constant->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcd_spring_constant, 4, 3, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);
        label_4->setWordWrap(true);

        gridLayout->addWidget(label_4, 2, 1, 1, 1);

        lcd_rest_length = new QLCDNumber(gridLayoutWidget);
        lcd_rest_length->setObjectName(QStringLiteral("lcd_rest_length"));
        lcd_rest_length->setFrameShape(QFrame::NoFrame);
        lcd_rest_length->setSmallDecimalPoint(false);
        lcd_rest_length->setDigitCount(4);
        lcd_rest_length->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcd_rest_length, 2, 3, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);
        label_3->setWordWrap(true);

        gridLayout->addWidget(label_3, 3, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);
        label_5->setWordWrap(true);

        gridLayout->addWidget(label_5, 1, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setFont(font);

        gridLayout->addWidget(label_8, 3, 4, 1, 1);

        lcd_damping_constant = new QLCDNumber(gridLayoutWidget);
        lcd_damping_constant->setObjectName(QStringLiteral("lcd_damping_constant"));
        lcd_damping_constant->setFrameShape(QFrame::NoFrame);
        lcd_damping_constant->setDigitCount(4);
        lcd_damping_constant->setSegmentStyle(QLCDNumber::Flat);

        gridLayout->addWidget(lcd_damping_constant, 1, 3, 1, 1);

        box1 = new QDoubleSpinBox(gridLayoutWidget);
        box1->setObjectName(QStringLiteral("box1"));

        gridLayout->addWidget(box1, 1, 2, 1, 1);

        box3 = new QDoubleSpinBox(gridLayoutWidget);
        box3->setObjectName(QStringLiteral("box3"));

        gridLayout->addWidget(box3, 3, 2, 1, 1);

        box2 = new QDoubleSpinBox(gridLayoutWidget);
        box2->setObjectName(QStringLiteral("box2"));

        gridLayout->addWidget(box2, 2, 2, 1, 1);

        box4 = new QDoubleSpinBox(gridLayoutWidget);
        box4->setObjectName(QStringLiteral("box4"));

        gridLayout->addWidget(box4, 4, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(880, 20, 201, 61));
        QFont font1;
        font1.setPointSize(24);
        label->setFont(font1);
        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(880, 530, 201, 91));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        button1 = new QPushButton(gridLayoutWidget_2);
        button1->setObjectName(QStringLiteral("button1"));
        button1->setFont(font);

        gridLayout_2->addWidget(button1, 0, 0, 1, 1);

        button2 = new QPushButton(gridLayoutWidget_2);
        button2->setObjectName(QStringLiteral("button2"));
        button2->setFont(font);

        gridLayout_2->addWidget(button2, 0, 1, 1, 1);

        button3 = new QPushButton(gridLayoutWidget_2);
        button3->setObjectName(QStringLiteral("button3"));
        button3->setFont(font);

        gridLayout_2->addWidget(button3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1107, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(button1, SIGNAL(clicked()), openGLWidget, SLOT(button_go()));
        QObject::connect(button2, SIGNAL(clicked()), openGLWidget, SLOT(button_stop()));
        QObject::connect(button3, SIGNAL(clicked()), openGLWidget, SLOT(button_reset()));
        QObject::connect(box1, SIGNAL(valueChanged(double)), MainWindow, SLOT(box_dampingConstant(double)));
        QObject::connect(box2, SIGNAL(valueChanged(double)), MainWindow, SLOT(box_restLength(double)));
        QObject::connect(box3, SIGNAL(valueChanged(double)), MainWindow, SLOT(box_mass(double)));
        QObject::connect(box4, SIGNAL(valueChanged(double)), MainWindow, SLOT(box_springConstant(double)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple Spring-Mass System", 0));
        label_2->setText(QApplication::translate("MainWindow", "Spring constant", 0));
        label_9->setText(QApplication::translate("MainWindow", "N/m", 0));
        label_6->setText(QApplication::translate("MainWindow", "N/m", 0));
        label_7->setText(QApplication::translate("MainWindow", "m", 0));
        label_4->setText(QApplication::translate("MainWindow", "Rest length", 0));
        label_3->setText(QApplication::translate("MainWindow", "Mass", 0));
        label_5->setText(QApplication::translate("MainWindow", "Damping constant", 0));
        label_8->setText(QApplication::translate("MainWindow", "kg", 0));
        label->setText(QApplication::translate("MainWindow", "Spring details", 0));
        button1->setText(QApplication::translate("MainWindow", "Go", 0));
        button2->setText(QApplication::translate("MainWindow", "Stop", 0));
        button3->setText(QApplication::translate("MainWindow", "Reset", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
