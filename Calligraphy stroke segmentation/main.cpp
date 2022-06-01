
#include "MainWindow.h"
#include <QtWidgets/QApplication>
#include <QTextStream>
#include <stdio.h>

int main(int argc, char *argv[])
{
   if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

   QTextStream cin(stdin, QIODevice::ReadOnly);

   QTextStream cout(stdout, QIODevice::WriteOnly);

   QTextStream cerr(stderr, QIODevice::WriteOnly);

    QApplication a(argc, argv);
    MainWindow w;


    /* set background color */
    QPalette palette(w.palette());
    palette.setColor(QPalette::Background, Qt::white);
    w.setPalette(palette);

    w.show();


    return a.exec();
}
