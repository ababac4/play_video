/********************************************************************************
** Form generated from reading UI file 'play_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAY_DIALOG_H
#define UI_PLAY_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Play_Dialog
{
public:
    QWidget *wd_content;
    QHBoxLayout *horizontalLayout;
    QLabel *play_lable;
    QSlider *time_slider;
    QLabel *cur_time;
    QLabel *end_time;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pl_button;
    QPushButton *pb_resume;
    QPushButton *pb_pause;
    QPushButton *pb_stop;
    QPushButton *pb_url;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Play_Dialog)
    {
        if (Play_Dialog->objectName().isEmpty())
            Play_Dialog->setObjectName(QString::fromUtf8("Play_Dialog"));
        Play_Dialog->resize(799, 600);
        wd_content = new QWidget(Play_Dialog);
        wd_content->setObjectName(QString::fromUtf8("wd_content"));
        wd_content->setGeometry(QRect(10, 10, 761, 451));
        wd_content->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        horizontalLayout = new QHBoxLayout(wd_content);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        play_lable = new QLabel(wd_content);
        play_lable->setObjectName(QString::fromUtf8("play_lable"));
        play_lable->setMinimumSize(QSize(300, 300));

        horizontalLayout->addWidget(play_lable);

        time_slider = new QSlider(Play_Dialog);
        time_slider->setObjectName(QString::fromUtf8("time_slider"));
        time_slider->setGeometry(QRect(90, 480, 621, 31));
        time_slider->setOrientation(Qt::Horizontal);
        cur_time = new QLabel(Play_Dialog);
        cur_time->setObjectName(QString::fromUtf8("cur_time"));
        cur_time->setGeometry(QRect(10, 480, 81, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(11);
        cur_time->setFont(font);
        end_time = new QLabel(Play_Dialog);
        end_time->setObjectName(QString::fromUtf8("end_time"));
        end_time->setGeometry(QRect(720, 480, 81, 21));
        end_time->setFont(font);
        widget = new QWidget(Play_Dialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 510, 751, 71));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pl_button = new QPushButton(widget);
        pl_button->setObjectName(QString::fromUtf8("pl_button"));

        horizontalLayout_2->addWidget(pl_button);

        pb_resume = new QPushButton(widget);
        pb_resume->setObjectName(QString::fromUtf8("pb_resume"));

        horizontalLayout_2->addWidget(pb_resume);

        pb_pause = new QPushButton(widget);
        pb_pause->setObjectName(QString::fromUtf8("pb_pause"));

        horizontalLayout_2->addWidget(pb_pause);

        pb_stop = new QPushButton(widget);
        pb_stop->setObjectName(QString::fromUtf8("pb_stop"));

        horizontalLayout_2->addWidget(pb_stop);

        pb_url = new QPushButton(widget);
        pb_url->setObjectName(QString::fromUtf8("pb_url"));

        horizontalLayout_2->addWidget(pb_url);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        retranslateUi(Play_Dialog);

        QMetaObject::connectSlotsByName(Play_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Play_Dialog)
    {
        Play_Dialog->setWindowTitle(QApplication::translate("Play_Dialog", "Play_Dialog", nullptr));
        play_lable->setText(QString());
        cur_time->setText(QApplication::translate("Play_Dialog", "00:00:00", nullptr));
        end_time->setText(QApplication::translate("Play_Dialog", "03:00:00", nullptr));
        pl_button->setText(QApplication::translate("Play_Dialog", "\346\211\223\345\274\200", nullptr));
        pb_resume->setText(QApplication::translate("Play_Dialog", "\346\222\255\346\224\276/\346\201\242\345\244\215", nullptr));
        pb_pause->setText(QApplication::translate("Play_Dialog", "\346\232\202\345\201\234", nullptr));
        pb_stop->setText(QApplication::translate("Play_Dialog", "\345\201\234\346\255\242", nullptr));
        pb_url->setText(QApplication::translate("Play_Dialog", "URL", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Play_Dialog: public Ui_Play_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAY_DIALOG_H
