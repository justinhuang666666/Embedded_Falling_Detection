/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtQuickWidgets/QQuickWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"
#include "qvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGroupBox *groupBox_3;
    QCustomPlot *customplot3_2;
    QCustomPlot *customplot2_2;
    QCustomPlot *customplot1_2;
    QPushButton *pushButton_7;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QGroupBox *groupBox_2;
    QSpinBox *spinBox_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QLabel *label_23;
    QComboBox *comboBox_13;
    QLabel *label_24;
    QComboBox *comboBox_14;
    QLabel *label_25;
    QComboBox *comboBox_15;
    QLabel *label_26;
    QComboBox *comboBox_16;
    QLabel *label_27;
    QComboBox *comboBox_17;
    QLabel *label_28;
    QComboBox *comboBox_18;
    QLabel *label_29;
    QLabel *label_30;
    QGroupBox *groupBox_5;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_9;
    QLabel *label_31;
    QLabel *label_32;
    QGroupBox *groupBox_6;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QLabel *label_33;
    QSpinBox *spinBox_4;
    QTextEdit *textEdit_2;
    QPushButton *pushButton_12;
    QLabel *label_34;
    QLineEdit *lineEdit_3;
    QLabel *label_35;
    QLineEdit *lineEdit_4;
    QGroupBox *groupBox;
    QQuickWidget *quickWidget;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_13;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *frame;
    QVideoWidget *widget;
    QComboBox *comboBox;
    QLabel *label_2;
    QPushButton *cancelbutton;
    QSpinBox *spinBox;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1409, 718);
        groupBox_3 = new QGroupBox(Widget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(280, 0, 341, 701));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy);
        customplot3_2 = new QCustomPlot(groupBox_3);
        customplot3_2->setObjectName(QString::fromUtf8("customplot3_2"));
        customplot3_2->setGeometry(QRect(10, 440, 321, 221));
        sizePolicy.setHeightForWidth(customplot3_2->sizePolicy().hasHeightForWidth());
        customplot3_2->setSizePolicy(sizePolicy);
        customplot2_2 = new QCustomPlot(groupBox_3);
        customplot2_2->setObjectName(QString::fromUtf8("customplot2_2"));
        customplot2_2->setGeometry(QRect(10, 220, 321, 211));
        sizePolicy.setHeightForWidth(customplot2_2->sizePolicy().hasHeightForWidth());
        customplot2_2->setSizePolicy(sizePolicy);
        customplot1_2 = new QCustomPlot(groupBox_3);
        customplot1_2->setObjectName(QString::fromUtf8("customplot1_2"));
        customplot1_2->setGeometry(QRect(10, 20, 321, 191));
        sizePolicy.setHeightForWidth(customplot1_2->sizePolicy().hasHeightForWidth());
        customplot1_2->setSizePolicy(sizePolicy);
        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(9, 666, 93, 29));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy1);
        pushButton_8 = new QPushButton(groupBox_3);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(125, 666, 93, 29));
        sizePolicy1.setHeightForWidth(pushButton_8->sizePolicy().hasHeightForWidth());
        pushButton_8->setSizePolicy(sizePolicy1);
        pushButton_9 = new QPushButton(groupBox_3);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(240, 666, 93, 29));
        sizePolicy1.setHeightForWidth(pushButton_9->sizePolicy().hasHeightForWidth());
        pushButton_9->setSizePolicy(sizePolicy1);
        groupBox_2 = new QGroupBox(Widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 261, 701));
        sizePolicy.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy);
        spinBox_3 = new QSpinBox(groupBox_2);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(173, 640, 71, 25));
        sizePolicy1.setHeightForWidth(spinBox_3->sizePolicy().hasHeightForWidth());
        spinBox_3->setSizePolicy(sizePolicy1);
        scrollArea_2 = new QScrollArea(groupBox_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(15, 20, 231, 261));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(scrollArea_2->sizePolicy().hasHeightForWidth());
        scrollArea_2->setSizePolicy(sizePolicy2);
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 229, 259));
        label_23 = new QLabel(scrollAreaWidgetContents_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(10, 20, 91, 20));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);
        comboBox_13 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_13->setObjectName(QString::fromUtf8("comboBox_13"));
        comboBox_13->setGeometry(QRect(130, 20, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_13->sizePolicy().hasHeightForWidth());
        comboBox_13->setSizePolicy(sizePolicy1);
        label_24 = new QLabel(scrollAreaWidgetContents_3);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(10, 57, 71, 20));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);
        comboBox_14 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->addItem(QString());
        comboBox_14->setObjectName(QString::fromUtf8("comboBox_14"));
        comboBox_14->setGeometry(QRect(130, 57, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_14->sizePolicy().hasHeightForWidth());
        comboBox_14->setSizePolicy(sizePolicy1);
        label_25 = new QLabel(scrollAreaWidgetContents_3);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(10, 95, 63, 20));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);
        comboBox_15 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->addItem(QString());
        comboBox_15->setObjectName(QString::fromUtf8("comboBox_15"));
        comboBox_15->setGeometry(QRect(130, 95, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_15->sizePolicy().hasHeightForWidth());
        comboBox_15->setSizePolicy(sizePolicy1);
        label_26 = new QLabel(scrollAreaWidgetContents_3);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(10, 133, 63, 20));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);
        comboBox_16 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_16->addItem(QString());
        comboBox_16->addItem(QString());
        comboBox_16->addItem(QString());
        comboBox_16->setObjectName(QString::fromUtf8("comboBox_16"));
        comboBox_16->setGeometry(QRect(130, 133, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_16->sizePolicy().hasHeightForWidth());
        comboBox_16->setSizePolicy(sizePolicy1);
        label_27 = new QLabel(scrollAreaWidgetContents_3);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(10, 171, 63, 20));
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);
        comboBox_17 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_17->addItem(QString());
        comboBox_17->addItem(QString());
        comboBox_17->addItem(QString());
        comboBox_17->setObjectName(QString::fromUtf8("comboBox_17"));
        comboBox_17->setGeometry(QRect(130, 171, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_17->sizePolicy().hasHeightForWidth());
        comboBox_17->setSizePolicy(sizePolicy1);
        label_28 = new QLabel(scrollAreaWidgetContents_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(10, 320, 63, 20));
        comboBox_18 = new QComboBox(scrollAreaWidgetContents_3);
        comboBox_18->addItem(QString());
        comboBox_18->addItem(QString());
        comboBox_18->addItem(QString());
        comboBox_18->setObjectName(QString::fromUtf8("comboBox_18"));
        comboBox_18->setGeometry(QRect(130, 209, 80, 26));
        sizePolicy1.setHeightForWidth(comboBox_18->sizePolicy().hasHeightForWidth());
        comboBox_18->setSizePolicy(sizePolicy1);
        label_29 = new QLabel(scrollAreaWidgetContents_3);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 209, 91, 20));
        sizePolicy.setHeightForWidth(label_29->sizePolicy().hasHeightForWidth());
        label_29->setSizePolicy(sizePolicy);
        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        label_30 = new QLabel(groupBox_2);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(132, 601, 41, 20));
        sizePolicy.setHeightForWidth(label_30->sizePolicy().hasHeightForWidth());
        label_30->setSizePolicy(sizePolicy);
        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(15, 290, 231, 121));
        sizePolicy.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy);
        checkBox_7 = new QCheckBox(groupBox_5);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setGeometry(QRect(17, 30, 91, 24));
        sizePolicy1.setHeightForWidth(checkBox_7->sizePolicy().hasHeightForWidth());
        checkBox_7->setSizePolicy(sizePolicy1);
        checkBox_8 = new QCheckBox(groupBox_5);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setGeometry(QRect(17, 60, 91, 24));
        sizePolicy1.setHeightForWidth(checkBox_8->sizePolicy().hasHeightForWidth());
        checkBox_8->setSizePolicy(sizePolicy1);
        checkBox_9 = new QCheckBox(groupBox_5);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setGeometry(QRect(17, 90, 91, 24));
        sizePolicy1.setHeightForWidth(checkBox_9->sizePolicy().hasHeightForWidth());
        checkBox_9->setSizePolicy(sizePolicy1);
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(97, 62, 111, 20));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_32 = new QLabel(groupBox_5);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(100, 92, 63, 20));
        groupBox_6 = new QGroupBox(groupBox_5);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(97, 92, 61, 20));
        sizePolicy.setHeightForWidth(groupBox_6->sizePolicy().hasHeightForWidth());
        groupBox_6->setSizePolicy(sizePolicy);
        pushButton_10 = new QPushButton(groupBox_5);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(100, 30, 93, 29));
        sizePolicy1.setHeightForWidth(pushButton_10->sizePolicy().hasHeightForWidth());
        pushButton_10->setSizePolicy(sizePolicy1);
        pushButton_11 = new QPushButton(groupBox_2);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(145, 551, 101, 29));
        sizePolicy1.setHeightForWidth(pushButton_11->sizePolicy().hasHeightForWidth());
        pushButton_11->setSizePolicy(sizePolicy1);
        label_33 = new QLabel(groupBox_2);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(16, 641, 31, 20));
        sizePolicy.setHeightForWidth(label_33->sizePolicy().hasHeightForWidth());
        label_33->setSizePolicy(sizePolicy);
        spinBox_4 = new QSpinBox(groupBox_2);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(56, 641, 71, 25));
        sizePolicy1.setHeightForWidth(spinBox_4->sizePolicy().hasHeightForWidth());
        spinBox_4->setSizePolicy(sizePolicy1);
        spinBox_4->setMaximum(1000000);
        textEdit_2 = new QTextEdit(groupBox_2);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(15, 417, 231, 131));
        sizePolicy2.setHeightForWidth(textEdit_2->sizePolicy().hasHeightForWidth());
        textEdit_2->setSizePolicy(sizePolicy2);
        pushButton_12 = new QPushButton(groupBox_2);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(15, 551, 101, 29));
        sizePolicy1.setHeightForWidth(pushButton_12->sizePolicy().hasHeightForWidth());
        pushButton_12->setSizePolicy(sizePolicy1);
        label_34 = new QLabel(groupBox_2);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(134, 641, 31, 20));
        sizePolicy.setHeightForWidth(label_34->sizePolicy().hasHeightForWidth());
        label_34->setSizePolicy(sizePolicy);
        lineEdit_3 = new QLineEdit(groupBox_2);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(55, 601, 71, 25));
        sizePolicy1.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy1);
        label_35 = new QLabel(groupBox_2);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(16, 601, 41, 20));
        sizePolicy.setHeightForWidth(label_35->sizePolicy().hasHeightForWidth());
        label_35->setSizePolicy(sizePolicy);
        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(173, 600, 71, 25));
        sizePolicy1.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy1);
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1006, 0, 401, 701));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        quickWidget = new QQuickWidget(groupBox);
        quickWidget->setObjectName(QString::fromUtf8("quickWidget"));
        quickWidget->setGeometry(QRect(15, 30, 371, 661));
        sizePolicy.setHeightForWidth(quickWidget->sizePolicy().hasHeightForWidth());
        quickWidget->setSizePolicy(sizePolicy);
        quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
        groupBox_4 = new QGroupBox(Widget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(628, 0, 371, 701));
        sizePolicy.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy);
        pushButton_13 = new QPushButton(groupBox_4);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(30, 652, 301, 41));
        sizePolicy1.setHeightForWidth(pushButton_13->sizePolicy().hasHeightForWidth());
        pushButton_13->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        pushButton_13->setFont(font);
        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 560, 31, 41));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label->setFont(font1);
        pushButton = new QPushButton(groupBox_4);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 605, 301, 41));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 360, 301, 81));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        pushButton_2->setFont(font2);
        frame = new QFrame(groupBox_4);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(12, 20, 341, 321));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        widget = new QVideoWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(15, 15, 311, 291));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        comboBox = new QComboBox(groupBox_4);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(100, 520, 231, 31));
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 514, 71, 41));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font1);
        cancelbutton = new QPushButton(groupBox_4);
        cancelbutton->setObjectName(QString::fromUtf8("cancelbutton"));
        cancelbutton->setGeometry(QRect(30, 450, 301, 41));
        sizePolicy1.setHeightForWidth(cancelbutton->sizePolicy().hasHeightForWidth());
        cancelbutton->setSizePolicy(sizePolicy1);
        cancelbutton->setFont(font);
        spinBox = new QSpinBox(groupBox_4);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(100, 570, 231, 25));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Widget", "RealTime Plot", nullptr));
        pushButton_7->setText(QCoreApplication::translate("Widget", "START", nullptr));
        pushButton_8->setText(QCoreApplication::translate("Widget", "STOP", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Widget", "CLEAR", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Widget", "Setup", nullptr));
        label_23->setText(QCoreApplication::translate("Widget", "Port Number", nullptr));
        label_24->setText(QCoreApplication::translate("Widget", "Baud Rate", nullptr));
        comboBox_14->setItemText(0, QCoreApplication::translate("Widget", "2400", nullptr));
        comboBox_14->setItemText(1, QCoreApplication::translate("Widget", "4800", nullptr));
        comboBox_14->setItemText(2, QCoreApplication::translate("Widget", "9600", nullptr));
        comboBox_14->setItemText(3, QCoreApplication::translate("Widget", "19200", nullptr));
        comboBox_14->setItemText(4, QCoreApplication::translate("Widget", "115200", nullptr));

        label_25->setText(QCoreApplication::translate("Widget", "Data Bit", nullptr));
        comboBox_15->setItemText(0, QCoreApplication::translate("Widget", "5", nullptr));
        comboBox_15->setItemText(1, QCoreApplication::translate("Widget", "6", nullptr));
        comboBox_15->setItemText(2, QCoreApplication::translate("Widget", "7", nullptr));
        comboBox_15->setItemText(3, QCoreApplication::translate("Widget", "8", nullptr));

        label_26->setText(QCoreApplication::translate("Widget", "Parity Bit", nullptr));
        comboBox_16->setItemText(0, QCoreApplication::translate("Widget", "Even", nullptr));
        comboBox_16->setItemText(1, QCoreApplication::translate("Widget", "Odd", nullptr));
        comboBox_16->setItemText(2, QCoreApplication::translate("Widget", "None", nullptr));

        label_27->setText(QCoreApplication::translate("Widget", "Stop Bit", nullptr));
        comboBox_17->setItemText(0, QCoreApplication::translate("Widget", "1", nullptr));
        comboBox_17->setItemText(1, QCoreApplication::translate("Widget", "1.5", nullptr));
        comboBox_17->setItemText(2, QCoreApplication::translate("Widget", "2", nullptr));

        label_28->setText(QString());
        comboBox_18->setItemText(0, QCoreApplication::translate("Widget", "None", nullptr));
        comboBox_18->setItemText(1, QCoreApplication::translate("Widget", "Hardware Control", nullptr));
        comboBox_18->setItemText(2, QCoreApplication::translate("Widget", "Software Control", nullptr));

        label_29->setText(QCoreApplication::translate("Widget", "Flow Control", nullptr));
        label_30->setText(QCoreApplication::translate("Widget", "Topic", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("Widget", "Receiving data:", nullptr));
        checkBox_7->setText(QCoreApplication::translate("Widget", "ASCII", nullptr));
        checkBox_8->setText(QCoreApplication::translate("Widget", "HEX", nullptr));
        checkBox_9->setText(QCoreApplication::translate("Widget", "STOP", nullptr));
        label_31->setText(QCoreApplication::translate("Widget", "Receiving Bytes:", nullptr));
        label_32->setText(QCoreApplication::translate("Widget", "0", nullptr));
        groupBox_6->setTitle(QString());
        pushButton_10->setText(QCoreApplication::translate("Widget", "Clear", nullptr));
        pushButton_11->setText(QCoreApplication::translate("Widget", "Open Internet", nullptr));
        label_33->setText(QCoreApplication::translate("Widget", "Port", nullptr));
        pushButton_12->setText(QCoreApplication::translate("Widget", "Open Serial", nullptr));
        label_34->setText(QCoreApplication::translate("Widget", "QoS", nullptr));
        label_35->setText(QCoreApplication::translate("Widget", "Host", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Widget", "Map", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("Widget", "Falling Detection", nullptr));
        pushButton_13->setText(QCoreApplication::translate("Widget", "SEND", nullptr));
        label->setText(QCoreApplication::translate("Widget", "ID", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "MAP", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Widget", "ADL", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "OLD PEOPLE", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "MOTOCYCLE", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "SKYING", nullptr));

        label_2->setText(QCoreApplication::translate("Widget", "MODE", nullptr));
        cancelbutton->setText(QCoreApplication::translate("Widget", "CANCEL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
