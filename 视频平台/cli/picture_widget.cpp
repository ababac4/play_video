#include "picture_widget.h"
#include "ui_picture_widget.h"

picture_widget::picture_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::picture_widget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|
     Qt::WindowStaysOnTopHint);// FramelessWindowHint-无边框 WindowStaysOnTopHint在最上面

}

picture_widget::~picture_widget()
{
    delete ui;
}

void picture_widget::sl_sentimg(QImage img)
{
    QPixmap map;
    if(!img.isNull()){
        map=QPixmap::fromImage(img.scaled(ui->lb_showimage->size(),Qt::KeepAspectRatio));
    }else{
        map=QPixmap::fromImage(img);
    }
    ui->lb_showimage->setPixmap(map);
}
