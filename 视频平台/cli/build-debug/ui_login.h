/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QPushButton *pb_local_play;
    QPushButton *pb_recorder;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(789, 544);
        pb_local_play = new QPushButton(login);
        pb_local_play->setObjectName(QString::fromUtf8("pb_local_play"));
        pb_local_play->setGeometry(QRect(660, 60, 101, 41));
        pb_recorder = new QPushButton(login);
        pb_recorder->setObjectName(QString::fromUtf8("pb_recorder"));
        pb_recorder->setGeometry(QRect(660, 120, 101, 41));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QApplication::translate("login", "Form", nullptr));
        pb_local_play->setText(QApplication::translate("login", "\346\234\254\345\234\260\346\222\255\346\224\276\350\247\206\351\242\221", nullptr));
        pb_recorder->setText(QApplication::translate("login", "\345\275\225\345\210\266\350\247\206\351\242\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
