/********************************************************************************
** Form generated from reading UI file 'history_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORY_DIALOG_H
#define UI_HISTORY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_history_dialog
{
public:
    QLabel *lb_title;
    QPushButton *pb_history1;
    QPushButton *pb_history1_2;
    QPushButton *pb_history1_3;
    QPushButton *pb_history1_4;
    QPushButton *pb_history1_5;
    QPushButton *pb_history1_6;
    QPushButton *pb_upgrad;

    void setupUi(QDialog *history_dialog)
    {
        if (history_dialog->objectName().isEmpty())
            history_dialog->setObjectName(QString::fromUtf8("history_dialog"));
        history_dialog->resize(624, 305);
        lb_title = new QLabel(history_dialog);
        lb_title->setObjectName(QString::fromUtf8("lb_title"));
        lb_title->setGeometry(QRect(250, 10, 71, 51));
        pb_history1 = new QPushButton(history_dialog);
        pb_history1->setObjectName(QString::fromUtf8("pb_history1"));
        pb_history1->setGeometry(QRect(40, 70, 150, 50));
        pb_history1_2 = new QPushButton(history_dialog);
        pb_history1_2->setObjectName(QString::fromUtf8("pb_history1_2"));
        pb_history1_2->setGeometry(QRect(210, 70, 150, 50));
        pb_history1_3 = new QPushButton(history_dialog);
        pb_history1_3->setObjectName(QString::fromUtf8("pb_history1_3"));
        pb_history1_3->setGeometry(QRect(390, 70, 150, 50));
        pb_history1_4 = new QPushButton(history_dialog);
        pb_history1_4->setObjectName(QString::fromUtf8("pb_history1_4"));
        pb_history1_4->setGeometry(QRect(40, 150, 150, 50));
        pb_history1_5 = new QPushButton(history_dialog);
        pb_history1_5->setObjectName(QString::fromUtf8("pb_history1_5"));
        pb_history1_5->setGeometry(QRect(210, 150, 150, 50));
        pb_history1_6 = new QPushButton(history_dialog);
        pb_history1_6->setObjectName(QString::fromUtf8("pb_history1_6"));
        pb_history1_6->setGeometry(QRect(390, 150, 150, 50));
        pb_upgrad = new QPushButton(history_dialog);
        pb_upgrad->setObjectName(QString::fromUtf8("pb_upgrad"));
        pb_upgrad->setGeometry(QRect(420, 20, 71, 28));

        retranslateUi(history_dialog);

        QMetaObject::connectSlotsByName(history_dialog);
    } // setupUi

    void retranslateUi(QDialog *history_dialog)
    {
        history_dialog->setWindowTitle(QApplication::translate("history_dialog", "Dialog", nullptr));
        lb_title->setText(QApplication::translate("history_dialog", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        pb_history1->setText(QString());
        pb_history1_2->setText(QString());
        pb_history1_3->setText(QString());
        pb_history1_4->setText(QString());
        pb_history1_5->setText(QString());
        pb_history1_6->setText(QString());
        pb_upgrad->setText(QApplication::translate("history_dialog", "\346\233\264\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class history_dialog: public Ui_history_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORY_DIALOG_H
