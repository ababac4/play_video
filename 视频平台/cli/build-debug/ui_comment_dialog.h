/********************************************************************************
** Form generated from reading UI file 'comment_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_DIALOG_H
#define UI_COMMENT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Comment_Dialog
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *qwg_comment;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *Comment_Dialog)
    {
        if (Comment_Dialog->objectName().isEmpty())
            Comment_Dialog->setObjectName(QString::fromUtf8("Comment_Dialog"));
        Comment_Dialog->resize(666, 421);
        scrollArea = new QScrollArea(Comment_Dialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 671, 421));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 669, 419));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        qwg_comment = new QWidget(scrollAreaWidgetContents);
        qwg_comment->setObjectName(QString::fromUtf8("qwg_comment"));

        verticalLayout->addWidget(qwg_comment);

        verticalSpacer = new QSpacerItem(20, 417, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(Comment_Dialog);

        QMetaObject::connectSlotsByName(Comment_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Comment_Dialog)
    {
        Comment_Dialog->setWindowTitle(QApplication::translate("Comment_Dialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Comment_Dialog: public Ui_Comment_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_DIALOG_H
