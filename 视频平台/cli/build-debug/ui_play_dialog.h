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
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pl_button;
    QPushButton *pb_resume;
    QPushButton *pb_pause;
    QPushButton *pb_stop;
    QSpacerItem *horizontalSpacer;
    QWidget *wd_menu;
    QPushButton *pb_history;
    QPushButton *pb_upload;
    QPushButton *pb_play;
    QPushButton *pb_recorder;
    QPushButton *pb_url;
    QPushButton *pb_download;
    QPushButton *pb_comment;
    QWidget *wd_content;
    QHBoxLayout *horizontalLayout;
    QLabel *play_lable;
    QPushButton *pb_next;
    QPushButton *pb_pre;
    QLabel *end_time;
    QSlider *time_slider;
    QLabel *cur_time;
    QPushButton *pb_like;
    QLabel *lb_like;
    QPushButton *pb_recommend;
    QLabel *lb_play;
    QLabel *lb_showplay;
    QPushButton *pb_cllike;
    QPushButton *pb_icon;

    void setupUi(QDialog *Play_Dialog)
    {
        if (Play_Dialog->objectName().isEmpty())
            Play_Dialog->setObjectName(QString::fromUtf8("Play_Dialog"));
        Play_Dialog->resize(950, 583);
        layoutWidget = new QWidget(Play_Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 470, 751, 71));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pl_button = new QPushButton(layoutWidget);
        pl_button->setObjectName(QString::fromUtf8("pl_button"));

        horizontalLayout_2->addWidget(pl_button);

        pb_resume = new QPushButton(layoutWidget);
        pb_resume->setObjectName(QString::fromUtf8("pb_resume"));

        horizontalLayout_2->addWidget(pb_resume);

        pb_pause = new QPushButton(layoutWidget);
        pb_pause->setObjectName(QString::fromUtf8("pb_pause"));

        horizontalLayout_2->addWidget(pb_pause);

        pb_stop = new QPushButton(layoutWidget);
        pb_stop->setObjectName(QString::fromUtf8("pb_stop"));

        horizontalLayout_2->addWidget(pb_stop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        wd_menu = new QWidget(Play_Dialog);
        wd_menu->setObjectName(QString::fromUtf8("wd_menu"));
        wd_menu->setGeometry(QRect(0, 0, 941, 461));
        pb_history = new QPushButton(wd_menu);
        pb_history->setObjectName(QString::fromUtf8("pb_history"));
        pb_history->setGeometry(QRect(10, 250, 101, 51));
        pb_upload = new QPushButton(wd_menu);
        pb_upload->setObjectName(QString::fromUtf8("pb_upload"));
        pb_upload->setGeometry(QRect(10, 130, 101, 51));
        pb_play = new QPushButton(wd_menu);
        pb_play->setObjectName(QString::fromUtf8("pb_play"));
        pb_play->setGeometry(QRect(10, 190, 101, 51));
        pb_recorder = new QPushButton(wd_menu);
        pb_recorder->setObjectName(QString::fromUtf8("pb_recorder"));
        pb_recorder->setGeometry(QRect(10, 70, 101, 51));
        pb_url = new QPushButton(wd_menu);
        pb_url->setObjectName(QString::fromUtf8("pb_url"));
        pb_url->setGeometry(QRect(10, 10, 101, 51));
        pb_download = new QPushButton(wd_menu);
        pb_download->setObjectName(QString::fromUtf8("pb_download"));
        pb_download->setGeometry(QRect(10, 310, 101, 41));
        pb_comment = new QPushButton(wd_menu);
        pb_comment->setObjectName(QString::fromUtf8("pb_comment"));
        pb_comment->setEnabled(true);
        pb_comment->setGeometry(QRect(850, 260, 61, 41));
        wd_content = new QWidget(wd_menu);
        wd_content->setObjectName(QString::fromUtf8("wd_content"));
        wd_content->setGeometry(QRect(120, 0, 721, 391));
        wd_content->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        horizontalLayout = new QHBoxLayout(wd_content);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        play_lable = new QLabel(wd_content);
        play_lable->setObjectName(QString::fromUtf8("play_lable"));
        play_lable->setMinimumSize(QSize(300, 300));

        horizontalLayout->addWidget(play_lable);

        pb_next = new QPushButton(wd_menu);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setGeometry(QRect(850, 180, 61, 41));
        pb_pre = new QPushButton(wd_menu);
        pb_pre->setObjectName(QString::fromUtf8("pb_pre"));
        pb_pre->setGeometry(QRect(850, 220, 61, 41));
        end_time = new QLabel(wd_menu);
        end_time->setObjectName(QString::fromUtf8("end_time"));
        end_time->setGeometry(QRect(810, 400, 81, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221 Light"));
        font.setPointSize(11);
        end_time->setFont(font);
        time_slider = new QSlider(wd_menu);
        time_slider->setObjectName(QString::fromUtf8("time_slider"));
        time_slider->setGeometry(QRect(120, 400, 681, 31));
        time_slider->setOrientation(Qt::Horizontal);
        cur_time = new QLabel(wd_menu);
        cur_time->setObjectName(QString::fromUtf8("cur_time"));
        cur_time->setGeometry(QRect(20, 400, 81, 21));
        cur_time->setFont(font);
        pb_like = new QPushButton(wd_menu);
        pb_like->setObjectName(QString::fromUtf8("pb_like"));
        pb_like->setGeometry(QRect(850, 300, 61, 51));
        lb_like = new QLabel(wd_menu);
        lb_like->setObjectName(QString::fromUtf8("lb_like"));
        lb_like->setGeometry(QRect(850, 340, 51, 31));
        pb_recommend = new QPushButton(wd_menu);
        pb_recommend->setObjectName(QString::fromUtf8("pb_recommend"));
        pb_recommend->setGeometry(QRect(10, 360, 101, 41));
        lb_play = new QLabel(wd_menu);
        lb_play->setObjectName(QString::fromUtf8("lb_play"));
        lb_play->setGeometry(QRect(850, 90, 51, 41));
        lb_showplay = new QLabel(wd_menu);
        lb_showplay->setObjectName(QString::fromUtf8("lb_showplay"));
        lb_showplay->setGeometry(QRect(850, 130, 51, 41));
        pb_cllike = new QPushButton(wd_menu);
        pb_cllike->setObjectName(QString::fromUtf8("pb_cllike"));
        pb_cllike->setGeometry(QRect(850, 300, 71, 51));
        pb_icon = new QPushButton(wd_menu);
        pb_icon->setObjectName(QString::fromUtf8("pb_icon"));
        pb_icon->setGeometry(QRect(860, 10, 60, 60));
        pb_icon->setIconSize(QSize(30, 30));
        pb_icon->setAutoDefault(false);
        pb_icon->setFlat(true);

        retranslateUi(Play_Dialog);

        pb_icon->setDefault(false);


        QMetaObject::connectSlotsByName(Play_Dialog);
    } // setupUi

    void retranslateUi(QDialog *Play_Dialog)
    {
        Play_Dialog->setWindowTitle(QApplication::translate("Play_Dialog", "Play_Dialog", nullptr));
        pl_button->setText(QApplication::translate("Play_Dialog", "\346\211\223\345\274\200", nullptr));
        pb_resume->setText(QApplication::translate("Play_Dialog", "\346\222\255\346\224\276/\346\201\242\345\244\215", nullptr));
        pb_pause->setText(QApplication::translate("Play_Dialog", "\346\232\202\345\201\234", nullptr));
        pb_stop->setText(QApplication::translate("Play_Dialog", "\345\201\234\346\255\242", nullptr));
        pb_history->setText(QApplication::translate("Play_Dialog", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        pb_upload->setText(QApplication::translate("Play_Dialog", "\344\270\212\344\274\240\350\247\206\351\242\221", nullptr));
        pb_play->setText(QApplication::translate("Play_Dialog", "\346\201\242\345\244\215\346\222\255\346\224\276", nullptr));
        pb_recorder->setText(QApplication::translate("Play_Dialog", "\345\275\225\345\210\266\350\247\206\351\242\221", nullptr));
        pb_url->setText(QApplication::translate("Play_Dialog", "\346\234\254\345\234\260\346\222\255\346\224\276\350\247\206\351\242\221", nullptr));
        pb_download->setText(QApplication::translate("Play_Dialog", "\344\270\213\350\275\275", nullptr));
        pb_comment->setText(QApplication::translate("Play_Dialog", "\350\257\204\350\256\272", nullptr));
        play_lable->setText(QString());
        pb_next->setText(QApplication::translate("Play_Dialog", "\344\270\213\344\270\200\351\233\206", nullptr));
        pb_pre->setText(QApplication::translate("Play_Dialog", "\344\270\212\344\270\200\351\233\206", nullptr));
        end_time->setText(QApplication::translate("Play_Dialog", "03:00:00", nullptr));
        cur_time->setText(QApplication::translate("Play_Dialog", "00:00:00", nullptr));
        pb_like->setText(QApplication::translate("Play_Dialog", "\347\202\271\350\265\236", nullptr));
        lb_like->setText(QString());
        pb_recommend->setText(QApplication::translate("Play_Dialog", "\347\214\234\347\214\234\344\275\240\345\226\234\346\254\242", nullptr));
        lb_play->setText(QApplication::translate("Play_Dialog", "\346\222\255\346\224\276\351\207\217\357\274\232", nullptr));
        lb_showplay->setText(QString());
        pb_cllike->setText(QApplication::translate("Play_Dialog", "\345\217\226\346\266\210\347\202\271\350\265\236", nullptr));
        pb_icon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Play_Dialog: public Ui_Play_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAY_DIALOG_H
