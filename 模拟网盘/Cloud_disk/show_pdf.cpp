#include "show_pdf.h"
#include "ui_show_pdf.h"

//show_pdf::show_pdf(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::show_pdf)
//{
//    page=0;
//    m_layout=new QVBoxLayout;
//    m_layout->setContentsMargins(0,0,0,0);
//    m_layout->setSpacing(3);
//    //将层设置到大控件上 设置图层

//    ui->setupUi(this);
//}

//show_pdf::~show_pdf()
//{
//    delete ui;
//}

//void show_pdf::show_my_pdf(QString path)
//{
//     filename=path;
//    if(filename.isEmpty()){

//    return;//如果文件路径为空则返回

//    }

//   document = Poppler::Document::load(filename);//加载pdf文件

//    if (!document || document->isLocked()) {

//    QMessageBox::information(this,"提示",QString::fromUtf8("无法打开文件:%1").arg(filename));//如果加载不成功，输出错误信息，并返回

//    delete document;

//    return;

//    }
//    //再次检查document是否可用

//    if (document == 0) {

//    // ui->label_message->setText(QString::fromUtf8("文件内无内容:%1").arg(filename));//不可用则输出错误信息，并返回

//    return;

//    }

//    //将PDF文档的每一页输出为QImage

//    // for(int pageNumber=0;pageNumbernumPages();pageNumber++){

//    //获取指定页码的页面，页码从0开始

//    Poppler::Page* pdfPage = document->page(page);

//    if (pdfPage == 0) {

//    qDebug();

//    return;

//    }

//    //将页面内容转换为QImage

//    QImage image = pdfPage->renderToImage();

//    // double xres=72.0, yres=72.0; int x=-1, y=-1, width=-1, height=-1;

//    // QImage image = pdfPage->renderToImage(xres, yres, x, y, width, height);

//    // if (image.isNull()) {

//    // qDebug()

//    // return;

//    // }

//    // 在QLabel中显示QImage

//    QLabel *label = new QLabel(this);

//    label->setPixmap(QPixmap::fromImage(image));


//    m_layout->addWidget(label);
//    ui->scw_show->setLayout(m_layout);


//}




//void show_pdf::on_pb_next_clicked()
//{
//    QVBoxLayout *newlayout=new QVBoxLayout;
//    ui->scw_show->setLayout(newlayout);

//    page++;
//    Poppler::Page* pdfPage = document->page(page);

//    if (pdfPage == 0) {

//    qDebug();

//    return;

//    }

//    //将页面内容转换为QImage

//    QImage image = pdfPage->renderToImage();

//    // double xres=72.0, yres=72.0; int x=-1, y=-1, width=-1, height=-1;

//    // QImage image = pdfPage->renderToImage(xres, yres, x, y, width, height);

//    // if (image.isNull()) {

//    // qDebug()

//    // return;

//    // }

//    // 在QLabel中显示QImage

//    QLabel *label = new QLabel(this);

//    label->setPixmap(QPixmap::fromImage(image));
//    QVBoxLayout *m_layout=new QVBoxLayout;

//    m_layout->addWidget(label);
//    ui->scw_show->setLayout(m_layout);


//}
show_pdf::show_pdf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::show_pdf),
    page(0),
    document(nullptr) // 初始化document为nullptr
{
    ui->setupUi(this);
    m_layout = new QVBoxLayout(ui->scw_show); // 直接在ui->scw_show上设置布局
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(5);
}

show_pdf::~show_pdf()
{
    delete ui;
    delete document; // 确保在析构函数中删除document
}

void show_pdf::show_my_pdf(QString path)
{
    filename = path;
    if (filename.isEmpty()) {
        return;
    }

    delete document; // 删除旧的document（如果有的话）
    document = Poppler::Document::load(filename);

    if (!document || document->isLocked()) {
        QMessageBox::information(this, "提示", QString::fromUtf8("无法打开文件:%1").arg(filename));
        return;
    }

    // 显示第一页
    showPage(page);
}

void show_pdf::showPage(int pageNum)
{
    page = pageNum;
    Poppler::Page* pdfPage = document->page(page);
    if (!pdfPage) {
        qDebug() << "无法获取页面:" << page;
        return;
    }

    QImage image = pdfPage->renderToImage();
    if (image.isNull()) {
        qDebug() << "无法渲染页面为图像:" << page;
        return;
    }

    // 移除当前布局中的所有小部件（避免内存泄漏）
    while (QLayoutItem* item = m_layout->takeAt(0)) {
        delete item->widget(); // 删除小部件
        delete item; // 删除布局项
    }

    // 在QLabel中显示QImage
    QLabel* label = new QLabel(this);
    label->setPixmap(QPixmap::fromImage(image));
    m_layout->addWidget(label);
}

void show_pdf::on_pb_next_clicked()
{
    page++;
    showPage(page); // 调用showPage方法显示下一页
}

void show_pdf::on_pb_pre_clicked()
{
    page--;
    showPage(page);
}

