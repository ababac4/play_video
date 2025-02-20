#include "upload_file.h"
#include "ui_upload_file.h"
#include<QFileDialog>
upload_file::upload_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::upload_file)
{
    ui->setupUi(this);
}

upload_file::~upload_file()
{
    delete ui;
}

void upload_file::on_pb_find_clicked()
{

        QString path=QFileDialog::getOpenFileName(this,"请选择文件","./");

        //判断
        if(path.isEmpty()) return;
        ui->le_file->setText(path);
        m_filepath=path;
}


void upload_file::on_pb_clear_clicked()
{
    ui->le_file->setText("");
}

void upload_file::slot_upload_process(qint64 cur, qint64 max)
{
ui->pgb_set->setMaximum(max);
ui->pgb_set->setValue(cur);
}
#include<QDebug>
void upload_file::on_pb_upload_clicked()
{
            Hobby h;

            h.cartoon=ui->cb_cartoon->isChecked()?'1':'0';
            h.food=ui->cb_food->isChecked()?'1':'0';
            h.game=ui->cb_game->isChecked()?'1':'0';
            h.life=ui->cb_life->isChecked()?'1':'0';
            h.music=ui->cb_music->isChecked()?'1':'0';
            Q_EMIT sig_Uploadfile(m_filepath,h);
}
#include<QMessageBox>
void upload_file::slot_up_success()
{
QMessageBox::about(this,"提示","上传成功！");
}

