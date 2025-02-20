/********************************************************************************
** Form generated from reading UI file 'friendlist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLIST_H
#define UI_FRIENDLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_friendlist
{
public:
    QPushButton *pb_tool3;
    QPushButton *pb_tool4;
    QPushButton *pb_icon;
    QTabWidget *tabWidget;
    QWidget *page_message;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QWidget *wid_list_2;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_friend;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QWidget *wid_list;
    QSpacerItem *verticalSpacer;
    QWidget *page_space;
    QPushButton *pb_tool2;
    QLineEdit *le_feeling;
    QLabel *lb_icon;
    QPushButton *pb_tool1;

    void setupUi(QDialog *friendlist)
    {
        if (friendlist->objectName().isEmpty())
            friendlist->setObjectName(QString::fromUtf8("friendlist"));
        friendlist->resize(400, 611);
        pb_tool3 = new QPushButton(friendlist);
        pb_tool3->setObjectName(QString::fromUtf8("pb_tool3"));
        pb_tool3->setGeometry(QRect(250, 570, 40, 40));
        pb_tool4 = new QPushButton(friendlist);
        pb_tool4->setObjectName(QString::fromUtf8("pb_tool4"));
        pb_tool4->setGeometry(QRect(300, 570, 40, 40));
        pb_icon = new QPushButton(friendlist);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(10, 20, 70, 70));
        pb_icon->setIconSize(QSize(70, 70));
        tabWidget = new QTabWidget(friendlist);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(20, 110, 341, 452));
        page_message = new QWidget();
        page_message->setObjectName(QString::fromUtf8("page_message"));
        verticalLayout = new QVBoxLayout(page_message);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        scrollArea_2 = new QScrollArea(page_message);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 333, 422));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        wid_list_2 = new QWidget(scrollAreaWidgetContents_3);
        wid_list_2->setObjectName(QString::fromUtf8("wid_list_2"));

        verticalLayout_3->addWidget(wid_list_2);

        verticalSpacer_2 = new QSpacerItem(20, 377, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);

        verticalLayout->addWidget(scrollArea_2);

        tabWidget->addTab(page_message, QString());
        page_friend = new QWidget();
        page_friend->setObjectName(QString::fromUtf8("page_friend"));
        scrollArea = new QScrollArea(page_friend);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 311, 421));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 309, 419));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        wid_list = new QWidget(scrollAreaWidgetContents);
        wid_list->setObjectName(QString::fromUtf8("wid_list"));

        verticalLayout_2->addWidget(wid_list);

        verticalSpacer = new QSpacerItem(20, 377, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(page_friend, QString());
        page_space = new QWidget();
        page_space->setObjectName(QString::fromUtf8("page_space"));
        tabWidget->addTab(page_space, QString());
        pb_tool2 = new QPushButton(friendlist);
        pb_tool2->setObjectName(QString::fromUtf8("pb_tool2"));
        pb_tool2->setGeometry(QRect(199, 570, 41, 40));
        le_feeling = new QLineEdit(friendlist);
        le_feeling->setObjectName(QString::fromUtf8("le_feeling"));
        le_feeling->setGeometry(QRect(80, 50, 261, 35));
        lb_icon = new QLabel(friendlist);
        lb_icon->setObjectName(QString::fromUtf8("lb_icon"));
        lb_icon->setGeometry(QRect(90, 10, 261, 35));
        pb_tool1 = new QPushButton(friendlist);
        pb_tool1->setObjectName(QString::fromUtf8("pb_tool1"));
        pb_tool1->setGeometry(QRect(30, 570, 40, 40));

        retranslateUi(friendlist);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(friendlist);
    } // setupUi

    void retranslateUi(QDialog *friendlist)
    {
        friendlist->setWindowTitle(QApplication::translate("friendlist", "Dialog", nullptr));
        pb_tool3->setText(QApplication::translate("friendlist", "PushButton", nullptr));
        pb_tool4->setText(QApplication::translate("friendlist", "PushButton", nullptr));
        pb_icon->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(page_message), QApplication::translate("friendlist", "\346\266\210\346\201\257  ", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(page_friend), QApplication::translate("friendlist", " \350\201\224\347\263\273\344\272\272", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(page_space), QApplication::translate("friendlist", " \347\251\272\351\227\264", nullptr));
        pb_tool2->setText(QApplication::translate("friendlist", "\345\245\275\345\217\213", nullptr));
        le_feeling->setText(QApplication::translate("friendlist", "ababac4", nullptr));
        lb_icon->setText(QApplication::translate("friendlist", "hello", nullptr));
        pb_tool1->setText(QApplication::translate("friendlist", "\346\267\273\345\212\240", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendlist: public Ui_friendlist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLIST_H
