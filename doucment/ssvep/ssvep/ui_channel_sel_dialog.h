/********************************************************************************
** Form generated from reading UI file 'channel_sel_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANNEL_SEL_DIALOG_H
#define UI_CHANNEL_SEL_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_channel_sel_dialog
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_15;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_8;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_16;
    QLabel *label;

    void setupUi(QDialog *channel_sel_dialog)
    {
        if (channel_sel_dialog->objectName().isEmpty())
            channel_sel_dialog->setObjectName(QString::fromUtf8("channel_sel_dialog"));
        channel_sel_dialog->resize(547, 366);
        pushButton = new QPushButton(channel_sel_dialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(400, 280, 80, 28));
        layoutWidget = new QWidget(channel_sel_dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 70, 173, 230));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        checkBox_1 = new QCheckBox(layoutWidget);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setChecked(true);

        verticalLayout->addWidget(checkBox_1);

        checkBox_3 = new QCheckBox(layoutWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setChecked(true);

        verticalLayout->addWidget(checkBox_3);

        checkBox_5 = new QCheckBox(layoutWidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setChecked(true);

        verticalLayout->addWidget(checkBox_5);

        checkBox_7 = new QCheckBox(layoutWidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setChecked(true);

        verticalLayout->addWidget(checkBox_7);

        checkBox_9 = new QCheckBox(layoutWidget);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setChecked(true);

        verticalLayout->addWidget(checkBox_9);

        checkBox_11 = new QCheckBox(layoutWidget);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setChecked(true);

        verticalLayout->addWidget(checkBox_11);

        checkBox_13 = new QCheckBox(layoutWidget);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));
        checkBox_13->setChecked(true);

        verticalLayout->addWidget(checkBox_13);

        checkBox_15 = new QCheckBox(layoutWidget);
        checkBox_15->setObjectName(QString::fromUtf8("checkBox_15"));
        checkBox_15->setChecked(true);

        verticalLayout->addWidget(checkBox_15);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setChecked(true);

        verticalLayout_2->addWidget(checkBox_2);

        checkBox_4 = new QCheckBox(layoutWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setChecked(true);

        verticalLayout_2->addWidget(checkBox_4);

        checkBox_6 = new QCheckBox(layoutWidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setChecked(true);

        verticalLayout_2->addWidget(checkBox_6);

        checkBox_8 = new QCheckBox(layoutWidget);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setChecked(true);

        verticalLayout_2->addWidget(checkBox_8);

        checkBox_10 = new QCheckBox(layoutWidget);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setChecked(true);

        verticalLayout_2->addWidget(checkBox_10);

        checkBox_12 = new QCheckBox(layoutWidget);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setChecked(true);

        verticalLayout_2->addWidget(checkBox_12);

        checkBox_14 = new QCheckBox(layoutWidget);
        checkBox_14->setObjectName(QString::fromUtf8("checkBox_14"));
        checkBox_14->setChecked(true);

        verticalLayout_2->addWidget(checkBox_14);

        checkBox_16 = new QCheckBox(layoutWidget);
        checkBox_16->setObjectName(QString::fromUtf8("checkBox_16"));
        checkBox_16->setChecked(true);

        verticalLayout_2->addWidget(checkBox_16);


        horizontalLayout->addLayout(verticalLayout_2);

        label = new QLabel(channel_sel_dialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 40, 261, 31));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        retranslateUi(channel_sel_dialog);

        QMetaObject::connectSlotsByName(channel_sel_dialog);
    } // setupUi

    void retranslateUi(QDialog *channel_sel_dialog)
    {
        channel_sel_dialog->setWindowTitle(QApplication::translate("channel_sel_dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("channel_sel_dialog", "OK", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("channel_sel_dialog", "channel1", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("channel_sel_dialog", "channel3", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("channel_sel_dialog", "channel5", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("channel_sel_dialog", "channel7", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("channel_sel_dialog", "channel9", 0, QApplication::UnicodeUTF8));
        checkBox_11->setText(QApplication::translate("channel_sel_dialog", "channel11", 0, QApplication::UnicodeUTF8));
        checkBox_13->setText(QApplication::translate("channel_sel_dialog", "channel13", 0, QApplication::UnicodeUTF8));
        checkBox_15->setText(QApplication::translate("channel_sel_dialog", "channel15", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("channel_sel_dialog", "channel2", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("channel_sel_dialog", "channel4", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("channel_sel_dialog", "channel6", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("channel_sel_dialog", "channel8", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("channel_sel_dialog", "channel10", 0, QApplication::UnicodeUTF8));
        checkBox_12->setText(QApplication::translate("channel_sel_dialog", "channel12", 0, QApplication::UnicodeUTF8));
        checkBox_14->setText(QApplication::translate("channel_sel_dialog", "channel14", 0, QApplication::UnicodeUTF8));
        checkBox_16->setText(QApplication::translate("channel_sel_dialog", "channel16", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("channel_sel_dialog", "Please select the needed channels", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class channel_sel_dialog: public Ui_channel_sel_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANNEL_SEL_DIALOG_H
