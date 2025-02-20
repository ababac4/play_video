#include "logindialog.h"
#include "ui_logindialog.h"
#include<QIcon>
#include<QDebug>
#include<QInputDialog>
#include<QMessageBox>
#include"ckenel.h"
#include"useritem.h"
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->sw_page->setCurrentIndex(0);
    ui->tabWidget->setCurrentIndex(3);
    s_pdf=new show_pdf;
    menu=new QMenu;
    m_set_menu=new QMenu;
    m_download_menu =new QMenu;
    m_upgrad_menu=new QMenu;
    m_Finish_menu=new QMenu;
    dio=new Play_Dialog;


    QAction* act_folder=new QAction(QIcon(":/images/folder.png"),"新建文件夹");
    QAction* act_upload_file=new QAction("上传文件");
    QAction* act_upload_dir=new QAction("上传文件夹");
    menu->addAction(act_folder);
    menu->addSeparator();
    menu->addAction(act_upload_file);
    menu->addAction(act_upload_dir);

    QAction* act_download=new QAction("下载文件");
    QAction* act_share=new QAction("分享文件");
    QAction* act_delete=new QAction("删除文件");
    QAction* act_GetShare=new QAction("获取分享文件");
    QAction* act_Playvideo=new QAction("播放视频");

    QAction* act_PDF=new QAction("打开pdf");
    m_set_menu->addAction(act_folder);
    m_set_menu->addSeparator();
    m_set_menu->addAction(act_download);
    m_set_menu->addAction(act_share);
    m_set_menu->addAction(act_delete);
    m_set_menu->addAction("收藏");
    m_set_menu->addSeparator();
    m_set_menu->addAction(act_Playvideo);
    m_set_menu->addAction(act_GetShare);

    m_Finish_menu->addAction(act_PDF);
    m_Finish_menu->addAction(act_PDF);
    connect(act_share,SIGNAL(triggered(bool)),this,SLOT(share_file(bool)));
    connect(act_delete,SIGNAL(triggered(bool)),this,SLOT(delete_file(bool)));
    connect(act_download,SIGNAL(triggered(bool)),this,SLOT(download_file(bool)));

    connect(act_folder,SIGNAL(triggered(bool)),this,SLOT(add_folder_trigger(bool)));
    connect(act_upload_file,SIGNAL(triggered(bool)),this,SLOT(upload_file_trigger(bool)));
    connect(act_upload_dir,SIGNAL(triggered(bool)),this,SLOT(upload_dir_trigger(bool)));
    connect(act_GetShare,SIGNAL(triggered(bool)),this,SLOT(act_GetShare_trigger(bool)));
    connect(act_Playvideo,SIGNAL(triggered(bool)),this,SLOT(act_Playvideo_trigger(bool)));

    connect(act_PDF,SIGNAL(triggered(bool)),this,SLOT(act_PDF_trigger(bool)));



    QAction *act_pause_down=new QAction("暂停文件");
    QAction *act_prsum_down=new QAction("恢复文件");


    QAction *act_pause_up=new QAction("暂停文件");
    QAction *act_prsum_up=new QAction("恢复文件");

    m_download_menu->addAction(act_pause_down);
    m_download_menu->addAction(act_prsum_down);
    m_download_menu->addAction("全部暂停");
    m_download_menu->addAction("全部恢复");

    m_upgrad_menu->addAction(act_pause_up);
    m_upgrad_menu->addAction(act_prsum_up);
    m_upgrad_menu->addAction("全部暂停");
    m_upgrad_menu->addAction("全部恢复");

    connect(act_pause_down,SIGNAL(triggered(bool)),this,SLOT(slot_down_pause(bool)));
    connect(act_prsum_down,SIGNAL(triggered(bool)),this,SLOT(slot_down_presum(bool)));
    connect(act_pause_up,SIGNAL(triggered(bool)),this,SLOT( slot_up_pause(bool)));
    connect(act_prsum_up,SIGNAL(triggered(bool)),this,SLOT(slot_up_presum(bool)));
    connect(ui->twg_download,&QTableWidget::customContextMenuRequested,this,[this](QPoint){this->m_download_menu->exec(QCursor::pos());});
    connect(ui->twg_upload,&QTableWidget::customContextMenuRequested,this,[this](QPoint){this->m_upgrad_menu->exec(QCursor::pos());});
    connect(ui->twg_finish,&QTableWidget::customContextMenuRequested,this,[this](QPoint){this->m_Finish_menu->exec(QCursor::pos());});
    //connect();



}

void LoginDialog::setCoin(int coinid)
{
    QString path=QString(":/face/btn_avatar_a%1.png").arg(coinid);
    qDebug()<<path;
    ui->pb_name->setIcon(QIcon(path));

}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pb_file_clicked()
{
       ui->sw_page->setCurrentIndex(0);
}


void LoginDialog::on_pb_tram_clicked()
{
    ui->sw_page->setCurrentIndex(1);
}


void LoginDialog::on_pb_share_clicked()
{
//    int rows=ui->twg_myshare_file->rowCount();
//    for(int i=0;i<rows;i++) ui->twg_myshare_file->removeRow(i);
    //ui->twg_myshare_file->clear();

   Ckenel::create()->slot_Get_sharelist();
//   Ckenel::create()->slot_Get_sharelist();
    ui->sw_page->setCurrentIndex(2);
}


void LoginDialog::on_pb_addfile_clicked()
{
   menu->exec(QCursor::pos());
}

void LoginDialog::add_folder_trigger(bool op)
{

    qDebug()<<__func__;
    QString path=QInputDialog::getText(this," 创建文件夹","文件夹名");
    QString temp=path;
    if(path.isEmpty()||temp.remove(' ').isEmpty()){
       QMessageBox::about(this,"提示","文件夹名不能空");
       return;
    }
    QString dir=ui->lb_find->text();
    Q_EMIT sig_add_Folder(path,dir);



}
#include<QFileDialog>

void LoginDialog::upload_file_trigger(bool op)
{
    qDebug()<<__func__;
    QString name=QFileDialog::getOpenFileName(this,"选择文件","./");
    if(name.isEmpty()) return;
    QString dir=ui->lb_find->text();
    Q_EMIT sig_send_upInfo(name,dir);
}

void LoginDialog::upload_dir_trigger(bool op)
{

    qDebug()<<__func__;
    QString path=QFileDialog::getExistingDirectory(this,"选择文件夹","./");
    if(path.isEmpty()) return;

    Q_EMIT sig_upload_folder(path,ui->lb_find->text());

}

void LoginDialog::share_file(bool flag)
{

qDebug()<<__func__;
//打钩的进行存储
int rows=ui->twg_content->rowCount();
QString dir=ui->lb_find->text();
QVector<int>res;
for(int i=0;i<rows;i++){
   MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(i,0);
   if(item->checkState()==Qt::Checked){
         res.push_back(item->info->fileid);
   }
}
Q_EMIT sig_share_info(res,dir);
}

void LoginDialog::delete_file(bool flag)
{

qDebug()<<__func__;
//打钩的进行存储
int rows=ui->twg_content->rowCount();
QString dir=ui->lb_find->text();
QVector<int>res;
for(int i=0;i<rows;i++){
   MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(i,0);
   if(item->checkState()==Qt::Checked){
         res.push_back(item->info->fileid);
   }
}
Q_EMIT sig_delete_file(res,dir);
}

void LoginDialog::download_file(bool flag)
{

qDebug()<<__func__;
int rows=ui->twg_content->rowCount();
QString dir=ui->lb_find->text();
for(int i=0;i<rows;i++){
    MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(i,0);
    if(item->checkState()==Qt::Checked){
        if(item->info->type=="folder"){

            Q_EMIT sig_download_folder(item->info->fileid,dir);

        }else{
           Q_EMIT sig_download_file(item->info->fileid,dir);
        }
    }
}


}

void LoginDialog::act_GetShare_trigger(bool flag)
{
  QString text=QInputDialog::getText(this,"获取连接","输入链接分享文件");
  int code=text.toInt();

  Q_EMIT sig_Send_Link(ui->lb_find->text(),code);
}

void LoginDialog::slot_down_pause(bool flag)
{
    qDebug()<<__func__;
 int rows=ui->twg_download->rowCount();
 for(int i=0;i<rows;i++){
     MyTableWidegt* item=(MyTableWidegt*)ui->twg_download->item(i,0);
     if(item->checkState()==Qt::Checked){
         QPushButton *button=(QPushButton *)ui->twg_download->cellWidget(i,5);
         if(button->text()=="开始"){
             button->setText("暂停");
         }
          Q_EMIT sig_down_attr(item->info->timestamp,1);
     }
 }
}

void LoginDialog::slot_down_presum(bool flag)
{
    qDebug()<<__func__;
    int rows=ui->twg_download->rowCount();
    for(int i=0;i<rows;i++){
        MyTableWidegt* item=(MyTableWidegt*)ui->twg_download->item(i,0);
        if(item->checkState()==Qt::Checked){
            QPushButton *button=(QPushButton *)ui->twg_download->cellWidget(i,5);
            if(button->text()=="暂停"){
                button->setText("开始");
            }
            Q_EMIT sig_down_attr(item->info->timestamp,0);
        }
    }
}

void LoginDialog::slot_up_pause(bool flag)
{
    qDebug()<<__func__;
    int rows=ui->twg_upload->rowCount();
    for(int i=0;i<rows;i++){
        MyTableWidegt* item=(MyTableWidegt*)ui->twg_upload->item(i,0);
        if(item->checkState()==Qt::Checked){
            QPushButton *button=(QPushButton *)ui->twg_upload->cellWidget(i,5);
            if(button->text()=="开始"){
                button->setText("暂停");
            }
           Q_EMIT sig_up_attr(item->info->timestamp,1);
        }
    }
}

void LoginDialog::slot_up_presum(bool flag)
{
    qDebug()<<__func__;
    int rows=ui->twg_upload->rowCount();
    for(int i=0;i<rows;i++){
        MyTableWidegt* item=(MyTableWidegt*)ui->twg_upload->item(i,0);
        if(item->checkState()==Qt::Checked){
            QPushButton *button=(QPushButton *)ui->twg_upload->cellWidget(i,5);
            if(button->text()=="暂停"){
                button->setText("开始");
            }
             Q_EMIT sig_up_attr(item->info->timestamp,0);
        }
    }
}

void LoginDialog::act_PDF_trigger(bool flag)
{

    int rows=ui->twg_finish->rowCount();

    for(int i=0;i<rows;i++){
        MyTableWidegt* item=(MyTableWidegt*)ui->twg_finish->item(i,0);
        if(item->checkState()==Qt::Checked){
           qDebug()<<item->info->name;
        }

    }
}

void LoginDialog::act_Playvideo_trigger(bool flag)
{

// 第一个箭头为主
 //如果是flv则播放其rtmp链接，实现在线播放
 int rows=ui->twg_content->rowCount();
 QString dir=ui->lb_find->text();
 for(int i=0;i<rows;i++){
     MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(i,0);
     if(item->checkState()==Qt::Checked){
         if(item->info->type=="flv"||item->info->type=="mp4"){
           dio->show();
           dio->play_my_video(item->info->rtmp);
         }else{

         }
     }
 }
}
#include<QProgressBar>
void LoginDialog::slot_insertFile(FileInfo *info)
{
//插入表格
//列: 文件 大小 时间 速率 进度 按钮
    int rows=ui->twg_upload->rowCount();
    ui->twg_upload->setRowCount(rows+1);
    MyTableWidegt *item=new MyTableWidegt;
    item->slot_setInfo(info);
    ui->twg_upload->setItem(rows,0,item);
    QTableWidgetItem *item1=new  QTableWidgetItem(info->getsize(info->size));
    ui->twg_upload->setItem(rows,1,item1);
    QTableWidgetItem *item2=new  QTableWidgetItem(info->time);
    ui->twg_upload->setItem(rows,2,item2);
    QTableWidgetItem *item3=new  QTableWidgetItem("0kb/s");
    ui->twg_upload->setItem(rows,3,item3);

    QProgressBar *progress=new QProgressBar;
    progress->setMaximum(info->size);
    ui->twg_upload->setCellWidget(rows,4,progress);
    QPushButton* button =new QPushButton;
    if(info->isPause==0){
        button->setText("暂停");
    }else{
        button->setText("开始");
    }
     ui->twg_upload->setCellWidget(rows,5,button);

}

void LoginDialog::slot_insertOK(FileInfo *info)
{

//列: 文件 大小 时间 上传完成
    int rows=ui->twg_finish->rowCount();

    ui->twg_finish->setRowCount(rows+1);
    MyTableWidegt *item=new MyTableWidegt;

    item->slot_setInfo(info);

    ui->twg_finish->setItem(rows,0,item);
    QTableWidgetItem *item1=new  QTableWidgetItem(info->getsize(info->size));
    ui->twg_finish->setItem(rows,1,item1);
    QTableWidgetItem *item2=new  QTableWidgetItem(info->time);
    ui->twg_finish->setItem(rows,2,item2);
    QTableWidgetItem *item3=new  QTableWidgetItem("上传完成");
    ui->twg_finish->setItem(rows,3,item3);
}

void LoginDialog::slot_uploadProgess(int timestamp, int pos)
{
    //遍历时间戳来对对于表格进行更新

   int rows=ui->twg_upload->rowCount();
   for(int i=0;i<rows;i++){
    MyTableWidegt*item=(MyTableWidegt*)ui->twg_upload->item(i,0);
    if(item->info->timestamp==timestamp){
        QProgressBar *progress=(QProgressBar*)ui->twg_upload->cellWidget(i,4);
        item->info->pos=pos;
        progress->setValue(pos);
        //超过进度最大 回收
        if(progress->value()>=progress->maximum()){
             slot_insertOK(item->info);//已完成列表
             slot_deleteFile(i);//删除
            return;
        }
    }
   }
}

void LoginDialog::slot_deleteFile(int row)
{
 ui->twg_upload->removeRow(row);
}

void LoginDialog::slot_insertInfo(FileInfo*info)
{
    int rows=ui->twg_content->rowCount();
    ui->twg_content->setRowCount(rows+1);
    MyTableWidegt *item=new MyTableWidegt;
    item->slot_setInfo(info);
    ui->twg_content->setItem(rows,0,item);

    QTableWidgetItem *item1=new QTableWidgetItem(info->getsize(info->size));
    ui->twg_content->setItem(rows,1,item1);
    QTableWidgetItem *item2=new QTableWidgetItem(info->time);
    ui->twg_content->setItem(rows,2,item2);
}

void LoginDialog::slot_deleteDownFile(int row)
{
 ui->twg_download->removeRow(row);
}

void LoginDialog::slot_insertDownOK(FileInfo *info)
{
    //列: 文件 大小 时间 上传完成
        int rows=ui->twg_finish->rowCount();

        ui->twg_finish->setRowCount(rows+1);
        MyTableWidegt *item0=new MyTableWidegt;

        item0->slot_setInfo(info);

        ui->twg_finish->setItem(rows,0,item0);
        QTableWidgetItem *item1=new  QTableWidgetItem(info->getsize(info->size));
        ui->twg_finish->setItem(rows,1,item1);
        QTableWidgetItem *item2=new  QTableWidgetItem(info->time);
        ui->twg_finish->setItem(rows,2,item2);
        QPushButton *button=new QPushButton;

        connect(button,SIGNAL(clicked(bool)),this,SLOT(slot_openPath(bool)));

        button->setIcon(QIcon(":/images/folder.png"));
        button->setToolTip(info->absolutePath);

        button->setFlat(true);
        ui->twg_finish->setCellWidget(rows,3,button);
}

void LoginDialog::slot_insertShareInfo(QString name, int size, QString time, int Link)
{
    int rows=ui->twg_myshare_file->rowCount();

    ui->twg_myshare_file->setRowCount(rows+1);
    QTableWidgetItem *item=new QTableWidgetItem(name);

    ui->twg_myshare_file->setItem(rows,0,item);

    QTableWidgetItem *item1=new QTableWidgetItem(FileInfo::getsize(size));
    ui->twg_myshare_file->setItem(rows,1,item1);
    QTableWidgetItem *item2=new QTableWidgetItem(time);
    ui->twg_myshare_file->setItem(rows,2,item2);
    QTableWidgetItem *item3=new QTableWidgetItem(QString::number(Link));
    ui->twg_myshare_file->setItem(rows,3,item3);
}
#include<QProcess>
void LoginDialog::slot_openPath(bool flag){
QPushButton *button=(QPushButton *)QObject::sender();
QString path=button->toolTip();
//进程打开文件
path.replace('/','\\');
QProcess process;
QStringList lst;
//lst.push_back("/select,");
//lst.push_back("path");
//"explorer /select,+路径 打开目录"
lst<<QString("/select,")<<path;//重载操作符
process.startDetached("explorer",lst);

}
void LoginDialog::slot_DownloadInfo(FileInfo *info)
{
    //插入表格
    //列: 文件 大小 时间 速率 进度 按钮
        int rows=ui->twg_download->rowCount();
        ui->twg_download->setRowCount(rows+1);
        MyTableWidegt *item=new MyTableWidegt;
        item->slot_setInfo(info);
        ui->twg_download->setItem(rows,0,item);
        QTableWidgetItem *item1=new  QTableWidgetItem(info->getsize(info->size));
        ui->twg_download->setItem(rows,1,item1);
        QTableWidgetItem *item2=new  QTableWidgetItem(info->time);
        ui->twg_download->setItem(rows,2,item2);
        QTableWidgetItem *item3=new  QTableWidgetItem("0kb/s");
        ui->twg_download->setItem(rows,3,item3);

        QProgressBar *progress=new QProgressBar;
        progress->setMaximum(info->size);
        ui->twg_download->setCellWidget(rows,4,progress);
        QPushButton* button =new QPushButton;
        if(info->isPause==0){
            button->setText("暂停");
        }else{
            button->setText("开始");
        }
        ui->twg_download->setCellWidget(rows,5,button);
}

void LoginDialog::slot_DownloadProgess(int timestamp, int pos)
{


    int rows=ui->twg_download->rowCount();
    for(int i=0;i<rows;i++){
     MyTableWidegt*item=(MyTableWidegt*)ui->twg_download->item(i,0);
     if(item->info->timestamp==timestamp){
         QProgressBar *progress=(QProgressBar*)ui->twg_download->cellWidget(i,4);
         item->info->pos=pos;
         progress->setValue(pos);
         //超过进度最大 回收
         if(progress->value()>=progress->maximum()){
             slot_insertDownOK(item->info);//已完成列表

             slot_deleteDownFile(i);//删除
             return;
         }
     }
    }
}

void LoginDialog::closeEvent(QCloseEvent *event)
{
    if(QMessageBox::question(this,"退出提示","是否退出")==QMessageBox::Yes){
       event->accept();
       Q_EMIT sig_close_dio();
    }else{
        event->ignore();//忽略不然一直卡住
    }
}

void LoginDialog::slot_delete_ALL()
{
 int rows=ui->twg_content->rowCount();
 for(int i=rows-1;i>=0;i--){
     ui->twg_content->removeRow(i);
 }
}

void LoginDialog::slot_deleteShare_ALL()
{
    int rows=ui->twg_myshare_file->rowCount();
    for(int i=rows-1;i>=0;i--){
        ui->twg_myshare_file->removeRow(i);
    }
}

FileInfo* LoginDialog::slot_getInfoBytime(int timestamp)
{
    int rows=ui->twg_download->rowCount();
    for(int i=0;i<rows;i++){
        MyTableWidegt *item=(MyTableWidegt*)ui->twg_download->item(i,0);
        if(item->info->timestamp==timestamp){
            return item->info;
        }
    }
}

FileInfo *LoginDialog::slot_getUpInfoBytime(int timestamp)
{
    int rows=ui->twg_upload->rowCount();
    for(int i=0;i<rows;i++){
        MyTableWidegt *item=(MyTableWidegt*)ui->twg_upload->item(i,0);
        if(item->info->timestamp==timestamp){
            return item->info;
        }
    }
}

void LoginDialog::clearshare()
{
    int rows=ui->twg_myshare_file->rowCount();
    for(int i=rows-1;i>=0;i--){
        ui->twg_myshare_file->removeRow(i);
    }
}


void LoginDialog::on_twg_content_cellClicked(int row, int column)
{
     MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(row,0);
     if(item->checkState()==Qt::Checked){
         item->setCheckState(Qt::Unchecked);
     }else{
          item->setCheckState(Qt::Checked);
     }
}


void LoginDialog::on_twg_content_customContextMenuRequested(const QPoint &pos)
{
  m_set_menu->exec(QCursor::pos());
}


void LoginDialog::on_twg_download_cellClicked(int row, int column)
{
    MyTableWidegt *item=(MyTableWidegt*)ui->twg_download->item(row,0);
    if(item->checkState()==Qt::Checked){
        item->setCheckState(Qt::Unchecked);
    }else{
         item->setCheckState(Qt::Checked);
    }
}


void LoginDialog::on_twg_content_cellDoubleClicked(int row, int column)
{
    MyTableWidegt *item=(MyTableWidegt*)ui->twg_content->item(row,0);
    if(item->info->type=="flv"||item->info->type=="mp4"){
        dio->show();
        dio->play_my_video(item->info->rtmp);
    }

    else if(item->info->type!="file"&&item->info->type!="flv"){
        //发信号更新路径
        QString dir=ui->lb_find->text()+item->info->name+"/";
        ui->lb_find->setText(dir);
        Q_EMIT sig_changDir(dir);

    }
}


void LoginDialog::on_pb_pre_clicked()
{
    //获取路径
    QString path=ui->lb_find->text();

    if(path=="/") return;

    path=path.left(path.lastIndexOf("/"));// /123/-> /123
    path=path.left(path.lastIndexOf("/")+1);// /123-> / +1来包含左边的/
    ui->lb_find->setText(path);
   qDebug()<<path;
   Q_EMIT sig_changDir(path);

}


void LoginDialog::on_twg_upload_cellClicked(int row, int column)
{
    MyTableWidegt *item=(MyTableWidegt*)ui->twg_upload->item(row,0);
    if(item->checkState()==Qt::Checked){
        item->setCheckState(Qt::Unchecked);
    }else{
         item->setCheckState(Qt::Checked);
    }
}



void LoginDialog::on_twg_finish_cellDoubleClicked(int row, int column)
{
    MyTableWidegt *item=(MyTableWidegt*)ui->twg_finish->item(row,0);
    if(item->info->type=="pdf"){
        s_pdf->show();
        s_pdf->show_my_pdf(item->info->absolutePath);
    }
}


void LoginDialog::on_pb_name_clicked()
{
   Ckenel::create()->friend_list->show();
}

