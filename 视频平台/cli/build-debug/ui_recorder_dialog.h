/********************************************************************************
** Form generated from reading UI file 'recorder_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDER_DIALOG_H
#define UI_RECORDER_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Recorder_Dialog
{
public:
    QWidget *widget;
    QWidget *wig_show;
    QLabel *lb_showimage;
    QGroupBox *gb_car;
    QComboBox *cbx_set;
    QGroupBox *cb_music_2;
    QComboBox *cbx_muset;
    QCheckBox *cb_carm;
    QCheckBox *cb_table;
    QCheckBox *cb_music;
    QPushButton *pb_start;
    QPushButton *pb_end;
    QPushButton *pb_set;
    QLabel *lb_url;
    QLineEdit *le_url;

    void setupUi(QDialog *Recorder_Dialog)
    {
        if (Recorder_Dialog->objectName().isEmpty())
            Recorder_Dialog->setObjectName(QString::fromUtf8("Recorder_Dialog"));
        Recorder_Dialog->resize(800, 600);
        widget = new QWidget(Recorder_Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 30, 751, 551));
        wig_show = new QWidget(widget);
        wig_show->setObjectName(QString::fromUtf8("wig_show"));
        wig_show->setGeometry(QRect(0, 0, 611, 451));
        wig_show->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        lb_showimage = new QLabel(wig_show);
        lb_showimage->setObjectName(QString::fromUtf8("lb_showimage"));
        lb_showimage->setGeometry(QRect(60, 100, 481, 281));
        gb_car = new QGroupBox(widget);
        gb_car->setObjectName(QString::fromUtf8("gb_car"));
        gb_car->setGeometry(QRect(620, 20, 120, 80));
        cbx_set = new QComboBox(gb_car);
        cbx_set->addItem(QString());
        cbx_set->setObjectName(QString::fromUtf8("cbx_set"));
        cbx_set->setGeometry(QRect(10, 40, 87, 22));
        cb_music_2 = new QGroupBox(widget);
        cb_music_2->setObjectName(QString::fromUtf8("cb_music_2"));
        cb_music_2->setGeometry(QRect(620, 130, 120, 80));
        cbx_muset = new QComboBox(cb_music_2);
        cbx_muset->addItem(QString());
        cbx_muset->setObjectName(QString::fromUtf8("cbx_muset"));
        cbx_muset->setGeometry(QRect(10, 30, 87, 22));
        cb_carm = new QCheckBox(widget);
        cb_carm->setObjectName(QString::fromUtf8("cb_carm"));
        cb_carm->setGeometry(QRect(630, 240, 91, 19));
        cb_carm->setChecked(true);
        cb_table = new QCheckBox(widget);
        cb_table->setObjectName(QString::fromUtf8("cb_table"));
        cb_table->setGeometry(QRect(630, 280, 91, 19));
        cb_table->setChecked(true);
        cb_music = new QCheckBox(widget);
        cb_music->setObjectName(QString::fromUtf8("cb_music"));
        cb_music->setGeometry(QRect(620, 320, 91, 19));
        cb_music->setChecked(true);
        pb_start = new QPushButton(widget);
        pb_start->setObjectName(QString::fromUtf8("pb_start"));
        pb_start->setGeometry(QRect(630, 370, 91, 28));
        pb_end = new QPushButton(widget);
        pb_end->setObjectName(QString::fromUtf8("pb_end"));
        pb_end->setGeometry(QRect(630, 420, 93, 28));
        pb_set = new QPushButton(widget);
        pb_set->setObjectName(QString::fromUtf8("pb_set"));
        pb_set->setGeometry(QRect(630, 480, 93, 28));
        lb_url = new QLabel(widget);
        lb_url->setObjectName(QString::fromUtf8("lb_url"));
        lb_url->setGeometry(QRect(10, 490, 71, 16));
        le_url = new QLineEdit(widget);
        le_url->setObjectName(QString::fromUtf8("le_url"));
        le_url->setGeometry(QRect(120, 490, 461, 21));

        retranslateUi(Recorder_Dialog);

        QMetaObject::connectSlotsByName(Recorder_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Recorder_Dialog)
    {
        Recorder_Dialog->setWindowTitle(QApplication::translate("Recorder_Dialog", "Recorder_Dialog", nullptr));
        lb_showimage->setText(QString());
        gb_car->setTitle(QApplication::translate("Recorder_Dialog", "\346\221\204\345\203\217\345\244\264", nullptr));
        cbx_set->setItemText(0, QApplication::translate("Recorder_Dialog", "\351\273\230\350\256\244\350\256\276\345\244\207", nullptr));

        cb_music_2->setTitle(QApplication::translate("Recorder_Dialog", "\351\237\263\351\242\221\350\256\276\345\244\207", nullptr));
        cbx_muset->setItemText(0, QApplication::translate("Recorder_Dialog", "\351\273\230\350\256\244\350\256\276\345\244\207", nullptr));

        cb_carm->setText(QApplication::translate("Recorder_Dialog", "\346\221\204\345\203\217\345\244\264", nullptr));
        cb_table->setText(QApplication::translate("Recorder_Dialog", "\346\241\214\351\235\242\350\256\276\345\244\207", nullptr));
        cb_music->setText(QApplication::translate("Recorder_Dialog", "\351\237\263\351\242\221\350\256\276\345\244\207", nullptr));
        pb_start->setText(QApplication::translate("Recorder_Dialog", "\345\274\200\345\247\213", nullptr));
        pb_end->setText(QApplication::translate("Recorder_Dialog", "\347\273\223\346\235\237", nullptr));
        pb_set->setText(QApplication::translate("Recorder_Dialog", "\350\256\276\347\275\256\347\233\264\346\222\255\345\234\260\345\235\200", nullptr));
        lb_url->setText(QApplication::translate("Recorder_Dialog", "URL", nullptr));
        le_url->setText(QApplication::translate("Recorder_Dialog", "E:\\video\\test.flv", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Recorder_Dialog: public Ui_Recorder_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDER_DIALOG_H
