#include "mytablewidegt.h"
#include<QDebug>
MyTableWidegt::MyTableWidegt()
{

}

void MyTableWidegt::slot_setInfo(FileInfo *item)
{
    //作为第一列出现 文件名
    FileInfo *it=new FileInfo;
    it->absolutePath=item->absolutePath;
    it->dir=item->dir;
    it->fileid=item->fileid;
    it->isPause=item->isPause;
    it->md5=item->md5;
    it->name=item->name;
    it->pFile=item->pFile;
    it->pos=item->pos;
    it->rtmp=item->rtmp;
    it->size=item->size;
    it->time=item->time;
    it->timestamp=item->timestamp;
    it->type=item->type;

    this->info=it;
    this->setText(info->name);

    if(info->type=="file"){
        this->setIcon(QIcon(":/images/file.png"));
    }else if(info->type=="flv"||info->type=="mp4"){
    this->setIcon(QIcon(":/images/play.png"));
    }else if(info->type=="pdf"){
this->setIcon(QIcon(":/images/PDF.png"));
    }
    else{
    this->setIcon(QIcon(":/images/folder.png"));
    }
    this->setCheckState(Qt::Unchecked);
}
