#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QMenu>
#include"packdef.h"
#include"mytablewidegt.h"
#include<QVector>
#include<QCloseEvent>
#include"play_dialog.h"
#include"show_pdf.h"
#include"friendlist.h"
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
signals:
    void sig_close_dio();
    void sig_send_upInfo(QString name,QString dir);
    void sig_download_file(int file_id,QString dir);
    void sig_download_folder(int file_id,QString dir);
    void sig_add_Folder(QString path,QString dir);
    void sig_changDir(QString dir);
    void sig_upload_folder(QString path,QString dir);
    void sig_share_info(QVector<int> res,QString dir);
    void sig_Send_Link(QString dir,int code);
    void sig_delete_file(QVector<int> res,QString dir);
    void sig_down_attr(int timestamp,int result);
    void sig_up_attr(int timestamp,int result);

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

public slots:
    void on_pb_file_clicked();

    void on_pb_tram_clicked();

    void on_pb_share_clicked();

    void on_pb_addfile_clicked();
    void add_folder_trigger(bool op);
    void upload_file_trigger(bool op);
    void upload_dir_trigger(bool op);
    void share_file(bool flag);
    void delete_file(bool flag);
    void download_file(bool flag);
    void act_GetShare_trigger(bool flag);
    void slot_down_pause(bool flag);
    void slot_down_presum(bool flag);
    void slot_up_pause(bool flag);
    void slot_up_presum(bool flag);
    void act_PDF_trigger(bool flag);
    void act_Playvideo_trigger(bool flag);
    void slot_insertFile(FileInfo*info);
    void slot_insertOK(FileInfo*info);
    void slot_uploadProgess(int timestamp,int pos);
    void slot_deleteFile(int row);
    void slot_insertInfo(FileInfo *info);
    void slot_deleteDownFile(int row);
    void slot_insertDownOK(FileInfo *info);
    void slot_insertShareInfo(QString name,int size,QString time,int Link);
    void slot_DownloadInfo(FileInfo *info);
    void slot_DownloadProgess(int timestamp,int pos);
    void closeEvent(QCloseEvent* event);
    void setCoin(int id);
    void slot_delete_ALL();
    void slot_deleteShare_ALL();
    FileInfo* slot_getInfoBytime(int timestamp);
    FileInfo* slot_getUpInfoBytime(int timestamp);
    void clearshare();
private slots:
    void on_twg_content_cellClicked(int row, int column);

    void on_twg_content_customContextMenuRequested(const QPoint &pos);

    void on_twg_download_cellClicked(int row, int column);

    void slot_openPath(bool flag);
    void on_twg_content_cellDoubleClicked(int row, int column);

    void on_pb_pre_clicked();

    void on_twg_upload_cellClicked(int row, int column);






    void on_twg_finish_cellDoubleClicked(int row, int column);

    void on_pb_name_clicked();

private:
    Ui::LoginDialog *ui;
    QMenu*menu;
    QMenu*m_set_menu;
    QMenu*m_download_menu;
    QMenu*m_Finish_menu;
    QMenu*m_upgrad_menu;
    Play_Dialog *dio;
    show_pdf *s_pdf;

};

#endif // LOGINDIALOG_H
