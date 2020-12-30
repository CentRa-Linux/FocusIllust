#include "mainwindow.h"
#include "canvas.h"
#include <QApplication>
#include <QWidget>
#include <QGraphicsAnchorLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
