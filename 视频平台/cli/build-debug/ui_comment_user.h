/********************************************************************************
** Form generated from reading UI file 'comment_user.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_USER_H
#define UI_COMMENT_USER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_comment_user
{
public:
    QLabel *lb_Name;
    QLabel *lb_comment;
    QLabel *lb_time;

    void setupUi(QWidget *comment_user)
    {
        if (comment_user->objectName().isEmpty())
            comment_user->setObjectName(QString::fromUtf8("comment_user"));
        comment_user->resize(630, 90);
        comment_user->setMinimumSize(QSize(630, 90));
        comment_user->setMaximumSize(QSize(630, 90));
        lb_Name = new QLabel(comment_user);
        lb_Name->setObjectName(QString::fromUtf8("lb_Name"));
        lb_Name->setGeometry(QRect(10, 0, 81, 31));
        lb_comment = new QLabel(comment_user);
        lb_comment->setObjectName(QString::fromUtf8("lb_comment"));
        lb_comment->setGeometry(QRect(20, 30, 411, 31));
        lb_time = new QLabel(comment_user);
        lb_time->setObjectName(QString::fromUtf8("lb_time"));
        lb_time->setGeometry(QRect(20, 60, 281, 31));

        retranslateUi(comment_user);

        QMetaObject::connectSlotsByName(comment_user);
    } // setupUi

    void retranslateUi(QWidget *comment_user)
    {
        comment_user->setWindowTitle(QApplication::translate("comment_user", "Form", nullptr));
        lb_Name->setText(QApplication::translate("comment_user", "\350\257\204\350\256\272\344\272\272", nullptr));
        lb_comment->setText(QApplication::translate("comment_user", "\350\257\204\350\256\272", nullptr));
        lb_time->setText(QApplication::translate("comment_user", "\346\227\266\351\227\264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comment_user: public Ui_comment_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_USER_H
