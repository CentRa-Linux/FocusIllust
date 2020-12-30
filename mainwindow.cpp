#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvas.h"
#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QGraphicsAnchorLayout>

int tabindex = 0;
int ptabindex = 0;
int isizex = 800;
int isizey = 800;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    tabindex += 1;
    Canvas *painter = new Canvas(this);
    painter->newImage(&tabindex, &isizex, &isizey);
    ui->tabs->addTab(painter,"Untitled");
}

void MainWindow::on_tabs_tabCloseRequested(int index)
{
    Canvas *painter = new Canvas(this);
    qDebug("%d",tabindex);
    if (tabindex != 0) {
        ui->tabs->removeTab(index);
        painter->removeTab(&index);
        tabindex -= 1;
    }
}

void MainWindow::on_tabs_currentChanged(int index)
{
    Canvas *painter = new Canvas(this);
    painter->focusTab(&index, &ptabindex);
    ptabindex = index;
}
