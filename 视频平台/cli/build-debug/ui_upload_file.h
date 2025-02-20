/********************************************************************************
** Form generated from reading UI file 'upload_file.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPLOAD_FILE_H
#define UI_UPLOAD_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_upload_file
{
public:
    QPushButton *pb_find;
    QLineEdit *le_file;
    QProgressBar *pgb_set;
    QPushButton *pb_upload;
    QCheckBox *cb_food;
    QCheckBox *cb_music;
    QCheckBox *cb_cartoon;
    QCheckBox *cb_game;
    QCheckBox *cb_life;
    QPushButton *pb_clear;

    void setupUi(QDialog *upload_file)
    {
        if (upload_file->objectName().isEmpty())
            upload_file->setObjectName(QString::fromUtf8("upload_file"));
        upload_file->resize(593, 446);
        pb_find = new QPushButton(upload_file);
        pb_find->setObjectName(QString::fromUtf8("pb_find"));
        pb_find->setGeometry(QRect(450, 60, 101, 31));
        le_file = new QLineEdit(upload_file);
        le_file->setObjectName(QString::fromUtf8("le_file"));
        le_file->setGeometry(QRect(80, 60, 351, 31));
        le_file->setReadOnly(true);
        pgb_set = new QProgressBar(upload_file);
        pgb_set->setObjectName(QString::fromUtf8("pgb_set"));
        pgb_set->setGeometry(QRect(90, 350, 371, 31));
        pgb_set->setValue(0);
        pb_upload = new QPushButton(upload_file);
        pb_upload->setObjectName(QString::fromUtf8("pb_upload"));
        pb_upload->setGeometry(QRect(470, 350, 101, 31));
        cb_food = new QCheckBox(upload_file);
        cb_food->setObjectName(QString::fromUtf8("cb_food"));
        cb_food->setGeometry(QRect(470, 140, 91, 19));
        cb_music = new QCheckBox(upload_file);
        cb_music->setObjectName(QString::fromUtf8("cb_music"));
        cb_music->setGeometry(QRect(470, 180, 91, 19));
        cb_cartoon = new QCheckBox(upload_file);
        cb_cartoon->setObjectName(QString::fromUtf8("cb_cartoon"));
        cb_cartoon->setGeometry(QRect(470, 220, 91, 19));
        cb_game = new QCheckBox(upload_file);
        cb_game->setObjectName(QString::fromUtf8("cb_game"));
        cb_game->setGeometry(QRect(470, 260, 91, 19));
        cb_life = new QCheckBox(upload_file);
        cb_life->setObjectName(QString::fromUtf8("cb_life"));
        cb_life->setGeometry(QRect(470, 300, 91, 19));
        pb_clear = new QPushButton(upload_file);
        pb_clear->setObjectName(QString::fromUtf8("pb_clear"));
        pb_clear->setGeometry(QRect(470, 400, 101, 31));

        retranslateUi(upload_file);

        QMetaObject::connectSlotsByName(upload_file);
    } // setupUi

    void retranslateUi(QDialog *upload_file)
    {
        upload_file->setWindowTitle(QApplication::translate("upload_file", "Dialog", nullptr));
        pb_find->setText(QApplication::translate("upload_file", "\346\265\217\350\247\210\346\226\207\344\273\266", nullptr));
        pb_upload->setText(QApplication::translate("upload_file", "\345\274\200\345\247\213\344\270\212\344\274\240", nullptr));
        cb_food->setText(QApplication::translate("upload_file", "\347\276\216\351\243\237", nullptr));
        cb_music->setText(QApplication::translate("upload_file", "\351\237\263\344\271\220", nullptr));
        cb_cartoon->setText(QApplication::translate("upload_file", "\345\212\250\346\274\253", nullptr));
        cb_game->setText(QApplication::translate("upload_file", "\346\270\270\346\210\217", nullptr));
        cb_life->setText(QApplication::translate("upload_file", "\347\224\237\346\264\273", nullptr));
        pb_clear->setText(QApplication::translate("upload_file", "\346\270\205\347\251\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class upload_file: public Ui_upload_file {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPLOAD_FILE_H
