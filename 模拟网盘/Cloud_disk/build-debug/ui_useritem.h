/********************************************************************************
** Form generated from reading UI file 'useritem.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERITEM_H
#define UI_USERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_useritem
{
public:
    QPushButton *pb_icon;
    QLabel *lb_feeling;
    QLabel *lb_name;

    void setupUi(QDialog *useritem)
    {
        if (useritem->objectName().isEmpty())
            useritem->setObjectName(QString::fromUtf8("useritem"));
        useritem->resize(280, 71);
        useritem->setMinimumSize(QSize(280, 71));
        useritem->setMaximumSize(QSize(280, 71));
        pb_icon = new QPushButton(useritem);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(0, 10, 51, 51));
        pb_icon->setIconSize(QSize(51, 51));
        lb_feeling = new QLabel(useritem);
        lb_feeling->setObjectName(QString::fromUtf8("lb_feeling"));
        lb_feeling->setGeometry(QRect(60, 40, 72, 21));
        lb_name = new QLabel(useritem);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setGeometry(QRect(60, 10, 72, 15));

        retranslateUi(useritem);

        QMetaObject::connectSlotsByName(useritem);
    } // setupUi

    void retranslateUi(QDialog *useritem)
    {
        useritem->setWindowTitle(QApplication::translate("useritem", "Dialog", nullptr));
        pb_icon->setText(QString());
        lb_feeling->setText(QApplication::translate("useritem", "\346\211\223", nullptr));
        lb_name->setText(QApplication::translate("useritem", "\347\216\213\345\205\211\350\200\200", nullptr));
    } // retranslateUi

};

namespace Ui {
    class useritem: public Ui_useritem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERITEM_H
