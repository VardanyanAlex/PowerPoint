/********************************************************************************
** Form generated from reading UI file 'powerpoint.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POWERPOINT_H
#define UI_POWERPOINT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PowerPointClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PowerPointClass)
    {
        if (PowerPointClass->objectName().isEmpty())
            PowerPointClass->setObjectName(QString::fromUtf8("PowerPointClass"));
        PowerPointClass->resize(600, 400);
        menuBar = new QMenuBar(PowerPointClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        PowerPointClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PowerPointClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PowerPointClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PowerPointClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PowerPointClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PowerPointClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PowerPointClass->setStatusBar(statusBar);

        retranslateUi(PowerPointClass);

        QMetaObject::connectSlotsByName(PowerPointClass);
    } // setupUi

    void retranslateUi(QMainWindow *PowerPointClass)
    {
        PowerPointClass->setWindowTitle(QCoreApplication::translate("PowerPointClass", "PowerPoint", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PowerPointClass: public Ui_PowerPointClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POWERPOINT_H
