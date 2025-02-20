/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *pb_file;
    QPushButton *pb_tram;
    QPushButton *pb_share;
    QPushButton *pb_star;
    QPushButton *pb_recyle;
    QSpacerItem *verticalSpacer;
    QPushButton *pb_name;
    QWidget *wg_content;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *sw_page;
    QWidget *qwg_file;
    QVBoxLayout *verticalLayout_3;
    QWidget *wg_tool;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_pre;
    QPushButton *pb_next;
    QLabel *lb_find;
    QSpacerItem *horizontalSpacer;
    QPushButton *pb_find;
    QPushButton *pb_addfile;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *twg_content;
    QWidget *qwg_tram;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget;
    QWidget *wg_upload;
    QVBoxLayout *verticalLayout_6;
    QTableWidget *twg_upload;
    QWidget *wg_download;
    QVBoxLayout *verticalLayout_7;
    QTableWidget *twg_download;
    QWidget *wg_finish;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *twg_finish;
    QWidget *qwg_share;
    QVBoxLayout *verticalLayout_9;
    QTabWidget *twg_share;
    QWidget *tw_share;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *twg_myshare_file;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(1084, 620);
        horizontalLayout = new QHBoxLayout(LoginDialog);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(LoginDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(321, 0));
        widget->setMaximumSize(QSize(321, 16777215));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(225, 225, 225);"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pb_file = new QPushButton(widget);
        pb_file->setObjectName(QString::fromUtf8("pb_file"));
        pb_file->setMinimumSize(QSize(0, 50));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/file.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_file->setIcon(icon);
        pb_file->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(pb_file);

        pb_tram = new QPushButton(widget);
        pb_tram->setObjectName(QString::fromUtf8("pb_tram"));
        pb_tram->setMinimumSize(QSize(0, 50));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/transmit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tram->setIcon(icon1);
        pb_tram->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(pb_tram);

        pb_share = new QPushButton(widget);
        pb_share->setObjectName(QString::fromUtf8("pb_share"));
        pb_share->setMinimumSize(QSize(0, 50));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/share.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_share->setIcon(icon2);
        pb_share->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(pb_share);

        pb_star = new QPushButton(widget);
        pb_star->setObjectName(QString::fromUtf8("pb_star"));
        pb_star->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(pb_star);

        pb_recyle = new QPushButton(widget);
        pb_recyle->setObjectName(QString::fromUtf8("pb_recyle"));
        pb_recyle->setMinimumSize(QSize(199, 50));
        pb_recyle->setMaximumSize(QSize(16777215, 50));

        verticalLayout->addWidget(pb_recyle);

        verticalSpacer = new QSpacerItem(20, 258, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pb_name = new QPushButton(widget);
        pb_name->setObjectName(QString::fromUtf8("pb_name"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/face/btn_avatar_a54.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_name->setIcon(icon3);
        pb_name->setIconSize(QSize(36, 36));
        pb_name->setFlat(true);

        verticalLayout->addWidget(pb_name);


        horizontalLayout->addWidget(widget);

        wg_content = new QWidget(LoginDialog);
        wg_content->setObjectName(QString::fromUtf8("wg_content"));
        verticalLayout_2 = new QVBoxLayout(wg_content);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        sw_page = new QStackedWidget(wg_content);
        sw_page->setObjectName(QString::fromUtf8("sw_page"));
        qwg_file = new QWidget();
        qwg_file->setObjectName(QString::fromUtf8("qwg_file"));
        verticalLayout_3 = new QVBoxLayout(qwg_file);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        wg_tool = new QWidget(qwg_file);
        wg_tool->setObjectName(QString::fromUtf8("wg_tool"));
        wg_tool->setMinimumSize(QSize(741, 52));
        wg_tool->setMaximumSize(QSize(741, 52));
        horizontalLayout_2 = new QHBoxLayout(wg_tool);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pb_pre = new QPushButton(wg_tool);
        pb_pre->setObjectName(QString::fromUtf8("pb_pre"));
        pb_pre->setMinimumSize(QSize(30, 30));
        pb_pre->setAutoDefault(true);
        pb_pre->setFlat(true);

        horizontalLayout_2->addWidget(pb_pre);

        pb_next = new QPushButton(wg_tool);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setMinimumSize(QSize(30, 30));
        pb_next->setAutoDefault(true);
        pb_next->setFlat(true);

        horizontalLayout_2->addWidget(pb_next);

        lb_find = new QLabel(wg_tool);
        lb_find->setObjectName(QString::fromUtf8("lb_find"));
        lb_find->setMinimumSize(QSize(361, 29));

        horizontalLayout_2->addWidget(lb_find);

        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pb_find = new QPushButton(wg_tool);
        pb_find->setObjectName(QString::fromUtf8("pb_find"));
        pb_find->setMinimumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_find->setIcon(icon4);
        pb_find->setAutoDefault(true);
        pb_find->setFlat(true);

        horizontalLayout_2->addWidget(pb_find);

        pb_addfile = new QPushButton(wg_tool);
        pb_addfile->setObjectName(QString::fromUtf8("pb_addfile"));
        pb_addfile->setMinimumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/addFile.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_addfile->setIcon(icon5);
        pb_addfile->setAutoDefault(true);
        pb_addfile->setFlat(true);

        horizontalLayout_2->addWidget(pb_addfile);


        verticalLayout_3->addWidget(wg_tool);

        widget_4 = new QWidget(qwg_file);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        verticalLayout_4 = new QVBoxLayout(widget_4);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        twg_content = new QTableWidget(widget_4);
        if (twg_content->columnCount() < 3)
            twg_content->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twg_content->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twg_content->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        twg_content->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        twg_content->setObjectName(QString::fromUtf8("twg_content"));
        twg_content->setMinimumSize(QSize(731, 531));
        twg_content->setContextMenuPolicy(Qt::CustomContextMenu);
        twg_content->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twg_content->setSelectionBehavior(QAbstractItemView::SelectRows);
        twg_content->horizontalHeader()->setDefaultSectionSize(200);
        twg_content->horizontalHeader()->setStretchLastSection(true);
        twg_content->verticalHeader()->setVisible(false);

        verticalLayout_4->addWidget(twg_content);


        verticalLayout_3->addWidget(widget_4);

        sw_page->addWidget(qwg_file);
        qwg_tram = new QWidget();
        qwg_tram->setObjectName(QString::fromUtf8("qwg_tram"));
        verticalLayout_5 = new QVBoxLayout(qwg_tram);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabWidget = new QTabWidget(qwg_tram);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        wg_upload = new QWidget();
        wg_upload->setObjectName(QString::fromUtf8("wg_upload"));
        verticalLayout_6 = new QVBoxLayout(wg_upload);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        twg_upload = new QTableWidget(wg_upload);
        if (twg_upload->columnCount() < 6)
            twg_upload->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(3, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(4, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        twg_upload->setHorizontalHeaderItem(5, __qtablewidgetitem8);
        twg_upload->setObjectName(QString::fromUtf8("twg_upload"));
        twg_upload->setContextMenuPolicy(Qt::CustomContextMenu);
        twg_upload->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twg_upload->setSelectionBehavior(QAbstractItemView::SelectRows);
        twg_upload->horizontalHeader()->setDefaultSectionSize(120);
        twg_upload->horizontalHeader()->setStretchLastSection(true);
        twg_upload->verticalHeader()->setVisible(false);

        verticalLayout_6->addWidget(twg_upload);

        tabWidget->addTab(wg_upload, QString());
        wg_download = new QWidget();
        wg_download->setObjectName(QString::fromUtf8("wg_download"));
        verticalLayout_7 = new QVBoxLayout(wg_download);
        verticalLayout_7->setSpacing(0);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 0, 0, 0);
        twg_download = new QTableWidget(wg_download);
        if (twg_download->columnCount() < 6)
            twg_download->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        twg_download->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        twg_download->setObjectName(QString::fromUtf8("twg_download"));
        twg_download->setContextMenuPolicy(Qt::CustomContextMenu);
        twg_download->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twg_download->setSelectionBehavior(QAbstractItemView::SelectRows);
        twg_download->horizontalHeader()->setDefaultSectionSize(120);
        twg_download->horizontalHeader()->setStretchLastSection(true);
        twg_download->verticalHeader()->setVisible(false);

        verticalLayout_7->addWidget(twg_download);

        tabWidget->addTab(wg_download, QString());
        wg_finish = new QWidget();
        wg_finish->setObjectName(QString::fromUtf8("wg_finish"));
        verticalLayout_8 = new QVBoxLayout(wg_finish);
        verticalLayout_8->setSpacing(0);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        twg_finish = new QTableWidget(wg_finish);
        if (twg_finish->columnCount() < 4)
            twg_finish->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        twg_finish->setHorizontalHeaderItem(0, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        twg_finish->setHorizontalHeaderItem(1, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        twg_finish->setHorizontalHeaderItem(2, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        twg_finish->setHorizontalHeaderItem(3, __qtablewidgetitem18);
        twg_finish->setObjectName(QString::fromUtf8("twg_finish"));
        twg_finish->setContextMenuPolicy(Qt::CustomContextMenu);
        twg_finish->setMidLineWidth(2);
        twg_finish->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twg_finish->setDragDropMode(QAbstractItemView::NoDragDrop);
        twg_finish->setSelectionBehavior(QAbstractItemView::SelectRows);
        twg_finish->horizontalHeader()->setDefaultSectionSize(180);
        twg_finish->horizontalHeader()->setStretchLastSection(true);
        twg_finish->verticalHeader()->setVisible(false);

        verticalLayout_8->addWidget(twg_finish);

        tabWidget->addTab(wg_finish, QString());

        verticalLayout_5->addWidget(tabWidget);

        sw_page->addWidget(qwg_tram);
        qwg_share = new QWidget();
        qwg_share->setObjectName(QString::fromUtf8("qwg_share"));
        verticalLayout_9 = new QVBoxLayout(qwg_share);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        twg_share = new QTabWidget(qwg_share);
        twg_share->setObjectName(QString::fromUtf8("twg_share"));
        tw_share = new QWidget();
        tw_share->setObjectName(QString::fromUtf8("tw_share"));
        verticalLayout_10 = new QVBoxLayout(tw_share);
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(0, 0, 0, 0);
        twg_myshare_file = new QTableWidget(tw_share);
        if (twg_myshare_file->columnCount() < 4)
            twg_myshare_file->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        twg_myshare_file->setHorizontalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        twg_myshare_file->setHorizontalHeaderItem(1, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        twg_myshare_file->setHorizontalHeaderItem(2, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        twg_myshare_file->setHorizontalHeaderItem(3, __qtablewidgetitem22);
        twg_myshare_file->setObjectName(QString::fromUtf8("twg_myshare_file"));
        twg_myshare_file->setEditTriggers(QAbstractItemView::NoEditTriggers);
        twg_myshare_file->setSelectionBehavior(QAbstractItemView::SelectRows);
        twg_myshare_file->horizontalHeader()->setDefaultSectionSize(150);
        twg_myshare_file->horizontalHeader()->setStretchLastSection(true);
        twg_myshare_file->verticalHeader()->setVisible(false);

        verticalLayout_10->addWidget(twg_myshare_file);

        twg_share->addTab(tw_share, QString());

        verticalLayout_9->addWidget(twg_share);

        sw_page->addWidget(qwg_share);

        verticalLayout_2->addWidget(sw_page);


        horizontalLayout->addWidget(wg_content);


        retranslateUi(LoginDialog);

        sw_page->setCurrentIndex(2);
        tabWidget->setCurrentIndex(2);
        twg_share->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", nullptr));
        pb_file->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        pb_tram->setText(QApplication::translate("LoginDialog", "\344\274\240\350\276\223", nullptr));
        pb_share->setText(QApplication::translate("LoginDialog", "\345\210\206\344\272\253", nullptr));
        pb_star->setText(QApplication::translate("LoginDialog", "\346\224\266\350\227\217", nullptr));
        pb_recyle->setText(QApplication::translate("LoginDialog", "\345\233\236\346\224\266\347\253\231", nullptr));
        pb_name->setText(QApplication::translate("LoginDialog", "name", nullptr));
        pb_pre->setText(QApplication::translate("LoginDialog", "<", nullptr));
        pb_next->setText(QApplication::translate("LoginDialog", ">", nullptr));
        lb_find->setText(QApplication::translate("LoginDialog", "/", nullptr));
        pb_find->setText(QString());
        pb_addfile->setText(QString());
        QTableWidgetItem *___qtablewidgetitem = twg_content->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twg_content->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("LoginDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = twg_content->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("LoginDialog", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = twg_upload->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = twg_upload->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QApplication::translate("LoginDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = twg_upload->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QApplication::translate("LoginDialog", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = twg_upload->horizontalHeaderItem(3);
        ___qtablewidgetitem6->setText(QApplication::translate("LoginDialog", "\351\200\237\347\216\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = twg_upload->horizontalHeaderItem(4);
        ___qtablewidgetitem7->setText(QApplication::translate("LoginDialog", "\350\277\233\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wg_upload), QApplication::translate("LoginDialog", "\344\270\212\344\274\240\344\270\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = twg_download->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = twg_download->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QApplication::translate("LoginDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = twg_download->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QApplication::translate("LoginDialog", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = twg_download->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QApplication::translate("LoginDialog", "\351\200\237\347\216\207", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = twg_download->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QApplication::translate("LoginDialog", "\350\277\233\345\272\246", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wg_download), QApplication::translate("LoginDialog", "\344\270\213\350\275\275\344\270\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = twg_finish->horizontalHeaderItem(0);
        ___qtablewidgetitem13->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = twg_finish->horizontalHeaderItem(1);
        ___qtablewidgetitem14->setText(QApplication::translate("LoginDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = twg_finish->horizontalHeaderItem(2);
        ___qtablewidgetitem15->setText(QApplication::translate("LoginDialog", "\346\227\266\351\227\264", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wg_finish), QApplication::translate("LoginDialog", "  \345\267\262\345\256\214\346\210\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = twg_myshare_file->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QApplication::translate("LoginDialog", "\346\226\207\344\273\266", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = twg_myshare_file->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QApplication::translate("LoginDialog", "\345\244\247\345\260\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = twg_myshare_file->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QApplication::translate("LoginDialog", "\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = twg_myshare_file->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QApplication::translate("LoginDialog", "\345\210\206\344\272\253\351\223\276\346\216\245", nullptr));
        twg_share->setTabText(twg_share->indexOf(tw_share), QApplication::translate("LoginDialog", " \346\210\221\347\232\204\345\210\206\344\272\253", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
