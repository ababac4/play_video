#ifndef SHOW_PDF_H
#define SHOW_PDF_H

#include <QDialog>
#include <QLabel>
#include<QMessageBox>
#include"QDebug"
#include"QVBoxLayout"
#include"./proper/poppler-qt5.h"
namespace Ui {
class show_pdf;
}

class show_pdf : public QDialog
{
    Q_OBJECT

public:
    explicit show_pdf(QWidget *parent = nullptr);
    ~show_pdf();
    void show_my_pdf(QString path);


    void showPage(int pageNum);
private slots:
    void on_pb_next_clicked();

    void on_pb_pre_clicked();

private:
    Ui::show_pdf *ui;
    QString filename;
    int page;
    QVBoxLayout *m_layout;
    Poppler::Document* document;
};

#endif // SHOW_PDF_H
