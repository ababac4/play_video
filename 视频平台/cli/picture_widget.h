#ifndef PICTURE_WIDGET_H
#define PICTURE_WIDGET_H

#include <QWidget>
#include<QPixmap>
#include"savevideothread.h"
namespace Ui {
class picture_widget;
}

class picture_widget : public QWidget
{
    Q_OBJECT

public:
    explicit picture_widget(QWidget *parent = nullptr);
    ~picture_widget();
public slots:
 void sl_sentimg(QImage img);

private:
    Ui::picture_widget *ui;

};

#endif // PICTURE_WIDGET_H
