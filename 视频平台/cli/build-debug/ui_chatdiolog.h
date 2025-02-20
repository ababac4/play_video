/********************************************************************************
** Form generated from reading UI file 'chatdiolog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIOLOG_H
#define UI_CHATDIOLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_chatdiolog
{
public:
    QGroupBox *groupBox;
    QPushButton *pb_tool3;
    QPushButton *pb_tool2;
    QPushButton *pb_tool1;
    QPushButton *pb_send;
    QTextBrowser *td_chat;
    QTextEdit *te_chat;

    void setupUi(QDialog *chatdiolog)
    {
        if (chatdiolog->objectName().isEmpty())
            chatdiolog->setObjectName(QString::fromUtf8("chatdiolog"));
        chatdiolog->resize(643, 493);
        groupBox = new QGroupBox(chatdiolog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 310, 131, 41));
        pb_tool3 = new QPushButton(groupBox);
        pb_tool3->setObjectName(QString::fromUtf8("pb_tool3"));
        pb_tool3->setGeometry(QRect(0, 0, 40, 40));
        pb_tool2 = new QPushButton(groupBox);
        pb_tool2->setObjectName(QString::fromUtf8("pb_tool2"));
        pb_tool2->setGeometry(QRect(40, 0, 40, 40));
        pb_tool1 = new QPushButton(groupBox);
        pb_tool1->setObjectName(QString::fromUtf8("pb_tool1"));
        pb_tool1->setGeometry(QRect(80, 0, 41, 40));
        pb_send = new QPushButton(chatdiolog);
        pb_send->setObjectName(QString::fromUtf8("pb_send"));
        pb_send->setGeometry(QRect(550, 440, 51, 28));
        td_chat = new QTextBrowser(chatdiolog);
        td_chat->setObjectName(QString::fromUtf8("td_chat"));
        td_chat->setGeometry(QRect(20, 10, 591, 291));
        te_chat = new QTextEdit(chatdiolog);
        te_chat->setObjectName(QString::fromUtf8("te_chat"));
        te_chat->setGeometry(QRect(20, 350, 581, 87));

        retranslateUi(chatdiolog);

        QMetaObject::connectSlotsByName(chatdiolog);
    } // setupUi

    void retranslateUi(QDialog *chatdiolog)
    {
        chatdiolog->setWindowTitle(QApplication::translate("chatdiolog", "Dialog", nullptr));
        groupBox->setTitle(QString());
        pb_tool3->setText(QString());
        pb_tool2->setText(QString());
        pb_tool1->setText(QString());
        pb_send->setText(QApplication::translate("chatdiolog", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatdiolog: public Ui_chatdiolog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIOLOG_H
