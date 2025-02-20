/********************************************************************************
** Form generated from reading UI file 'picture_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURE_WIDGET_H
#define UI_PICTURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_picture_widget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *lb_showimage;

    void setupUi(QWidget *picture_widget)
    {
        if (picture_widget->objectName().isEmpty())
            picture_widget->setObjectName(QString::fromUtf8("picture_widget"));
        picture_widget->resize(300, 200);
        picture_widget->setMinimumSize(QSize(300, 200));
        picture_widget->setMaximumSize(QSize(300, 200));
        verticalLayout = new QVBoxLayout(picture_widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        lb_showimage = new QLabel(picture_widget);
        lb_showimage->setObjectName(QString::fromUtf8("lb_showimage"));
        lb_showimage->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));

        verticalLayout->addWidget(lb_showimage);


        retranslateUi(picture_widget);

        QMetaObject::connectSlotsByName(picture_widget);
    } // setupUi

    void retranslateUi(QWidget *picture_widget)
    {
        picture_widget->setWindowTitle(QApplication::translate("picture_widget", "Form", nullptr));
        lb_showimage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class picture_widget: public Ui_picture_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURE_WIDGET_H
