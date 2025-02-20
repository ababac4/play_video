/********************************************************************************
** Form generated from reading UI file 'comment.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_H
#define UI_COMMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_comment
{
public:
    QPushButton *pb_publish;
    QPushButton *pb_clear;
    QLineEdit *le_comment;

    void setupUi(QDialog *comment)
    {
        if (comment->objectName().isEmpty())
            comment->setObjectName(QString::fromUtf8("comment"));
        comment->resize(644, 120);
        pb_publish = new QPushButton(comment);
        pb_publish->setObjectName(QString::fromUtf8("pb_publish"));
        pb_publish->setGeometry(QRect(510, 10, 93, 28));
        pb_clear = new QPushButton(comment);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(510, 60, 93, 28));
        le_comment = new QLineEdit(comment);
        le_comment->setObjectName(QString::fromUtf8("le_comment"));
        le_comment->setGeometry(QRect(50, 20, 431, 41));

        retranslateUi(comment);

        QMetaObject::connectSlotsByName(comment);
    } // setupUi

    void retranslateUi(QDialog *comment)
    {
        comment->setWindowTitle(QApplication::translate("comment", "Dialog", nullptr));
        pb_publish->setText(QApplication::translate("comment", "\345\217\221\345\270\203", nullptr));
        pb_clear->setText(QApplication::translate("comment", "\346\270\205\351\231\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comment: public Ui_comment {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_H
