/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *wd_login;
    QPushButton *pb_login;
    QPushButton *pb_login_clear;
    QLineEdit *le_login_phone;
    QLineEdit *le_login_pass;
    QLabel *lb_login_phone;
    QLabel *lb_login_pass;
    QWidget *wd_register;
    QPushButton *pb_register;
    QPushButton *pb_clear;
    QLineEdit *le_reg_user;
    QLabel *lb_rig_user;
    QLabel *lb_reg_phone;
    QLabel *lb_reg_pass;
    QLineEdit *le_reg_phone;
    QLineEdit *le_reg_pass;
    QLineEdit *le_reg_duan;
    QPushButton *pb_sendduan;
    QLabel *lb_reg_duanxin;
    QLabel *lb_bk;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 344);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(330, 0, 471, 591));
        wd_login = new QWidget();
        wd_login->setObjectName(QString::fromUtf8("wd_login"));
        pb_login = new QPushButton(wd_login);
        pb_login->setObjectName(QString::fromUtf8("pb_login"));
        pb_login->setGeometry(QRect(110, 200, 50, 50));
        pb_login_clear = new QPushButton(wd_login);
        pb_login_clear->setObjectName(QString::fromUtf8("pb_login_clear"));
        pb_login_clear->setGeometry(QRect(230, 200, 50, 50));
        le_login_phone = new QLineEdit(wd_login);
        le_login_phone->setObjectName(QString::fromUtf8("le_login_phone"));
        le_login_phone->setGeometry(QRect(110, 100, 171, 31));
        le_login_pass = new QLineEdit(wd_login);
        le_login_pass->setObjectName(QString::fromUtf8("le_login_pass"));
        le_login_pass->setGeometry(QRect(110, 150, 171, 31));
        le_login_pass->setEchoMode(QLineEdit::Password);
        lb_login_phone = new QLabel(wd_login);
        lb_login_phone->setObjectName(QString::fromUtf8("lb_login_phone"));
        lb_login_phone->setGeometry(QRect(40, 105, 51, 21));
        lb_login_pass = new QLabel(wd_login);
        lb_login_pass->setObjectName(QString::fromUtf8("lb_login_pass"));
        lb_login_pass->setGeometry(QRect(50, 150, 41, 31));
        tabWidget->addTab(wd_login, QString());
        wd_register = new QWidget();
        wd_register->setObjectName(QString::fromUtf8("wd_register"));
        pb_register = new QPushButton(wd_register);
        pb_register->setObjectName(QString::fromUtf8("pb_register"));
        pb_register->setGeometry(QRect(10, 240, 50, 50));
        pb_clear = new QPushButton(wd_register);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(70, 240, 50, 50));
        le_reg_user = new QLineEdit(wd_register);
        le_reg_user->setObjectName(QString::fromUtf8("le_reg_user"));
        le_reg_user->setGeometry(QRect(100, 30, 200, 31));
        lb_rig_user = new QLabel(wd_register);
        lb_rig_user->setObjectName(QString::fromUtf8("lb_rig_user"));
        lb_rig_user->setGeometry(QRect(1, 30, 81, 31));
        lb_reg_phone = new QLabel(wd_register);
        lb_reg_phone->setObjectName(QString::fromUtf8("lb_reg_phone"));
        lb_reg_phone->setGeometry(QRect(20, 80, 61, 31));
        lb_reg_pass = new QLabel(wd_register);
        lb_reg_pass->setObjectName(QString::fromUtf8("lb_reg_pass"));
        lb_reg_pass->setGeometry(QRect(30, 130, 41, 31));
        le_reg_phone = new QLineEdit(wd_register);
        le_reg_phone->setObjectName(QString::fromUtf8("le_reg_phone"));
        le_reg_phone->setGeometry(QRect(100, 80, 200, 31));
        le_reg_pass = new QLineEdit(wd_register);
        le_reg_pass->setObjectName(QString::fromUtf8("le_reg_pass"));
        le_reg_pass->setGeometry(QRect(100, 130, 200, 31));
        le_reg_pass->setEchoMode(QLineEdit::Password);
        le_reg_duan = new QLineEdit(wd_register);
        le_reg_duan->setObjectName(QString::fromUtf8("le_reg_duan"));
        le_reg_duan->setGeometry(QRect(100, 180, 200, 31));
        pb_sendduan = new QPushButton(wd_register);
        pb_sendduan->setObjectName(QString::fromUtf8("pb_sendduan"));
        pb_sendduan->setGeometry(QRect(250, 240, 50, 50));
        lb_reg_duanxin = new QLabel(wd_register);
        lb_reg_duanxin->setObjectName(QString::fromUtf8("lb_reg_duanxin"));
        lb_reg_duanxin->setGeometry(QRect(-10, 180, 81, 31));
        tabWidget->addTab(wd_register, QString());
        lb_bk = new QLabel(centralwidget);
        lb_bk->setObjectName(QString::fromUtf8("lb_bk"));
        lb_bk->setGeometry(QRect(0, 10, 321, 311));
        lb_bk->setPixmap(QPixmap(QString::fromUtf8(":/tb/baidu.png")));
        lb_bk->setScaledContents(true);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pb_login->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        pb_login_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        lb_login_phone->setText(QApplication::translate("MainWindow", " \346\211\213\346\234\272\345\217\267", nullptr));
        lb_login_pass->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wd_login), QApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        pb_register->setText(QApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        pb_clear->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272", nullptr));
        lb_rig_user->setText(QApplication::translate("MainWindow", "   \347\224\250\346\210\267\345\220\215", nullptr));
        lb_reg_phone->setText(QApplication::translate("MainWindow", " \346\211\213\346\234\272\345\217\267", nullptr));
        lb_reg_pass->setText(QApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        pb_sendduan->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        lb_reg_duanxin->setText(QApplication::translate("MainWindow", "  \347\237\255\344\277\241\351\252\214\350\257\201", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(wd_register), QApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        lb_bk->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
