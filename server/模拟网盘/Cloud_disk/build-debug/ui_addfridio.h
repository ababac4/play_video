/********************************************************************************
** Form generated from reading UI file 'addfridio.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRIDIO_H
#define UI_ADDFRIDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addfridio
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_name;
    QLabel *label;
    QPushButton *pb_yes;
    QPushButton *pb_no;

    void setupUi(QDialog *addfridio)
    {
        if (addfridio->objectName().isEmpty())
            addfridio->setObjectName(QString::fromUtf8("addfridio"));
        addfridio->resize(326, 50);
        addfridio->setMinimumSize(QSize(326, 50));
        addfridio->setMaximumSize(QSize(326, 50));
        widget = new QWidget(addfridio);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 307, 42));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lb_name = new QLabel(widget);
        lb_name->setObjectName(QString::fromUtf8("lb_name"));
        lb_name->setMinimumSize(QSize(72, 21));
        lb_name->setMaximumSize(QSize(72, 21));

        horizontalLayout->addWidget(lb_name);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(131, 20));
        label->setMaximumSize(QSize(131, 20));

        horizontalLayout->addWidget(label);

        pb_yes = new QPushButton(widget);
        pb_yes->setObjectName(QString::fromUtf8("pb_yes"));
        pb_yes->setMinimumSize(QSize(40, 40));
        pb_yes->setMaximumSize(QSize(40, 40));

        horizontalLayout->addWidget(pb_yes);

        pb_no = new QPushButton(widget);
        pb_no->setObjectName(QString::fromUtf8("pb_no"));
        pb_no->setMinimumSize(QSize(41, 40));
        pb_no->setMaximumSize(QSize(41, 40));

        horizontalLayout->addWidget(pb_no);


        retranslateUi(addfridio);

        QMetaObject::connectSlotsByName(addfridio);
    } // setupUi

    void retranslateUi(QDialog *addfridio)
    {
        addfridio->setWindowTitle(QApplication::translate("addfridio", "Dialog", nullptr));
        lb_name->setText(QString());
        label->setText(QApplication::translate("addfridio", "\350\257\267\346\261\202\346\267\273\345\212\240\344\275\240\344\270\272\345\245\275\345\217\213", nullptr));
        pb_yes->setText(QApplication::translate("addfridio", "\345\220\214\346\204\217", nullptr));
        pb_no->setText(QApplication::translate("addfridio", "\345\217\215\345\257\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addfridio: public Ui_addfridio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRIDIO_H
