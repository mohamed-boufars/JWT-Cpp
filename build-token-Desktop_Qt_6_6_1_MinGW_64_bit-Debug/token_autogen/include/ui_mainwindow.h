/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *TokenTextEdit;
    QTextEdit *headerTextEdit;
    QTextEdit *PayloadTextEdit;
    QTextEdit *SIgnatureTextEdit;
    QLabel *HeaderLabel;
    QLabel *PayloadLabel;
    QLabel *SignatureLabel;
    QLabel *EncodedLabel;
    QLabel *DecodedLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(807, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        TokenTextEdit = new QTextEdit(centralwidget);
        TokenTextEdit->setObjectName("TokenTextEdit");
        TokenTextEdit->setGeometry(QRect(5, 90, 390, 461));
        headerTextEdit = new QTextEdit(centralwidget);
        headerTextEdit->setObjectName("headerTextEdit");
        headerTextEdit->setGeometry(QRect(400, 130, 391, 111));
        PayloadTextEdit = new QTextEdit(centralwidget);
        PayloadTextEdit->setObjectName("PayloadTextEdit");
        PayloadTextEdit->setGeometry(QRect(400, 270, 391, 121));
        SIgnatureTextEdit = new QTextEdit(centralwidget);
        SIgnatureTextEdit->setObjectName("SIgnatureTextEdit");
        SIgnatureTextEdit->setGeometry(QRect(400, 420, 391, 131));
        HeaderLabel = new QLabel(centralwidget);
        HeaderLabel->setObjectName("HeaderLabel");
        HeaderLabel->setGeometry(QRect(400, 100, 391, 21));
        PayloadLabel = new QLabel(centralwidget);
        PayloadLabel->setObjectName("PayloadLabel");
        PayloadLabel->setGeometry(QRect(400, 250, 391, 16));
        SignatureLabel = new QLabel(centralwidget);
        SignatureLabel->setObjectName("SignatureLabel");
        SignatureLabel->setGeometry(QRect(400, 400, 391, 16));
        EncodedLabel = new QLabel(centralwidget);
        EncodedLabel->setObjectName("EncodedLabel");
        EncodedLabel->setGeometry(QRect(4, 40, 100, 75));
        DecodedLabel = new QLabel(centralwidget);
        DecodedLabel->setObjectName("DecodedLabel");
        DecodedLabel->setGeometry(QRect(400, 40, 100, 75));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 807, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        HeaderLabel->setText(QCoreApplication::translate("MainWindow", "HEADER: ALGORITHM & TOKEN TYPE", nullptr));
        PayloadLabel->setText(QCoreApplication::translate("MainWindow", "PAYLOAD: DATA", nullptr));
        SignatureLabel->setText(QCoreApplication::translate("MainWindow", "VERIFY SIGNATURE", nullptr));
        EncodedLabel->setText(QCoreApplication::translate("MainWindow", "Encoded", nullptr));
        DecodedLabel->setText(QCoreApplication::translate("MainWindow", "Decoded", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
