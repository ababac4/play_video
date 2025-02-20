#ifndef PDFLOADTHREAD_H
#define PDFLOADTHREAD_H
#include "qmutex.h"
#include <QQueue>
#include <QThreadPool>
#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <poppler-qt5.h>
class PdfLoadThread : public QObject , public QRunnable
{
    Q_OBJECT
public:
    PdfLoadThread(Poppler::Document* document, int pageNum, QObject* parent=nullptr)
        : QObject(parent), QRunnable(), m_document(document), m_pageNum(pageNum) {}

    void run()
    {
        Poppler::Page* pdfPage = m_document->page(m_pageNum);
        if (!pdfPage) {
            return;
        }
        QImage image = pdfPage->renderToImage(195, 195, -1, -1, -1, -1, Poppler::Page::Rotation::Rotate0);//可更改195, 数值越大，渲染率越高
        delete pdfPage;
        emit pageLoaded(m_pageNum, image);
    }

signals:
    void pageLoaded(int pageNum, QImage image);

private:
    Poppler::Document* m_document;
    int m_pageNum;
};

#endif // PDFLOADTHREAD_H
