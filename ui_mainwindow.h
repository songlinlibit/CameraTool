/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "camerabutton.h"
#include "previewlabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    CameraButton *pushButton;
    CameraButton *pushButton_2;
    QGroupBox *groupBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    previewLabel *preview_2;
    previewLabel *preview_1;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QLabel *label;
    QSlider *horizontalSlider;
    QComboBox *comboBox;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QComboBox *comboBox_5;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QLabel *label_2;
    QSlider *horizontalSlider_2;
    QLabel *label_4;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit;
    QComboBox *comboBox_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox_3;
    QLabel *label_5;
    QPushButton *pushButton_13;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1114, 703);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new CameraButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 80, 111, 51));
        pushButton_2 = new CameraButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 150, 111, 51));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(170, 60, 351, 611));
        verticalLayoutWidget = new QWidget(groupBox);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 20, 351, 591));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        preview_2 = new previewLabel(verticalLayoutWidget);
        preview_2->setObjectName(QString::fromUtf8("preview_2"));

        verticalLayout->addWidget(preview_2);

        preview_1 = new previewLabel(verticalLayoutWidget);
        preview_1->setObjectName(QString::fromUtf8("preview_1"));

        verticalLayout->addWidget(preview_1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(660, 50, 371, 291));
        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 70, 92, 29));
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(10, 30, 92, 29));
        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(10, 110, 92, 29));
        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(10, 160, 92, 29));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 40, 69, 20));
        horizontalSlider = new QSlider(groupBox_2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(170, 40, 160, 18));
        horizontalSlider->setOrientation(Qt::Horizontal);
        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(170, 120, 151, 31));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 120, 69, 20));
        lineEdit_2 = new QLineEdit(groupBox_2);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 70, 161, 31));
        comboBox_5 = new QComboBox(groupBox_2);
        comboBox_5->setObjectName(QString::fromUtf8("comboBox_5"));
        comboBox_5->setGeometry(QRect(170, 170, 151, 31));
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(660, 370, 371, 291));
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(10, 80, 92, 29));
        pushButton_10 = new QPushButton(groupBox_3);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(10, 40, 92, 29));
        pushButton_11 = new QPushButton(groupBox_3);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(10, 120, 92, 29));
        pushButton_12 = new QPushButton(groupBox_3);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(10, 160, 92, 29));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(110, 40, 69, 20));
        horizontalSlider_2 = new QSlider(groupBox_3);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(160, 40, 160, 18));
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(110, 130, 69, 20));
        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(160, 130, 151, 31));
        lineEdit = new QLineEdit(groupBox_3);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(160, 70, 161, 27));
        comboBox_4 = new QComboBox(groupBox_3);
        comboBox_4->setObjectName(QString::fromUtf8("comboBox_4"));
        comboBox_4->setGeometry(QRect(160, 170, 151, 31));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(530, 70, 92, 29));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(530, 340, 92, 29));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(150, 20, 341, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        comboBox_3 = new QComboBox(layoutWidget);
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));

        horizontalLayout->addWidget(comboBox_3);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 20, 101, 29));
        pushButton_13 = new QPushButton(centralwidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(20, 250, 101, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1114, 17));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\2721", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\2722", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\351\242\204\350\247\210", nullptr));
        preview_2->setText(QString());
        preview_1->setText(QString());
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\2721\350\256\276\347\275\256", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\346\215\225\350\216\267", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\270\247\347\216\207", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256BPS", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\346\233\235\345\205\211\345\272\246\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "features", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\2722\350\256\276\347\275\256", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\346\224\276\345\244\247", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\346\215\225\350\216\267", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\270\247\347\216\207", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256BPS", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\233\235\345\205\211\345\272\246\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "features", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\212\223\345\217\226\347\233\270\346\234\2721", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\212\223\345\217\226\347\233\270\346\234\2722", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\263\273\347\273\237\346\243\200\346\265\213\345\210\260\347\232\204\347\233\270\346\234\272\357\274\232", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MainWindow", "test", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
