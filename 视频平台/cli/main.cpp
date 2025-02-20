#include "mainwindow.h"

#include <QApplication>
#include"ckenel.h"
#include <QApplication>
#include <iostream>
#undef main
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   //w.show();
    Ckenel::create();//走构造

    return a.exec();
}
