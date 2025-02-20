/********************************************************************************
** Form generated from reading UI file 'show_pdf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_PDF_H
#define UI_SHOW_PDF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show_pdf
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *twg_pdf;
    QScrollArea *scrollArea;
    QWidget *scw_show;
    QPushButton *pb_next;
    QPushButton *pb_pre;

    void setupUi(QDialog *show_pdf)
    {
        if (show_pdf->objectName().isEmpty())
            show_pdf->setObjectName(QString::fromUtf8("show_pdf"));
        show_pdf->resize(602, 733);
        horizontalLayout = new QHBoxLayout(show_pdf);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        twg_pdf = new QWidget(show_pdf);
        twg_pdf->setObjectName(QString::fromUtf8("twg_pdf"));
        scrollArea = new QScrollArea(twg_pdf);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(-10, -10, 491, 751));
        scrollArea->setWidgetResizable(true);
        scw_show = new QWidget();
        scw_show->setObjectName(QString::fromUtf8("scw_show"));
        scw_show->setGeometry(QRect(0, 0, 489, 749));
        scrollArea->setWidget(scw_show);
        pb_next = new QPushButton(twg_pdf);
        pb_next->setObjectName(QString::fromUtf8("pb_next"));
        pb_next->setGeometry(QRect(490, 10, 93, 28));
        pb_next->setBaseSize(QSize(2, 0));
        pb_pre = new QPushButton(twg_pdf);
        pb_pre->setObjectName(QString::fromUtf8("pb_pre"));
        pb_pre->setGeometry(QRect(490, 60, 93, 31));

        horizontalLayout->addWidget(twg_pdf);


        retranslateUi(show_pdf);

        QMetaObject::connectSlotsByName(show_pdf);
    } // setupUi

    void retranslateUi(QDialog *show_pdf)
    {
        show_pdf->setWindowTitle(QApplication::translate("show_pdf", "Dialog", nullptr));
        pb_next->setText(QApplication::translate("show_pdf", "\344\270\213\344\270\200\351\241\265", nullptr));
        pb_pre->setText(QApplication::translate("show_pdf", "\344\270\212\344\270\200\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class show_pdf: public Ui_show_pdf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_PDF_H
