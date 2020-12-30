#include "canvas.h"
#include "paintevent.h"
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <QDebug>
#include <QList>
#include <QImage>

bool isclicked = false;
bool ispainting = false;
int mx;
int my;
int lx;
int ly;
int l2x;
int l2y;
int pensize = 1;
int spensize = 1;
int mpensize = 4;
QString imes;
std::vector<QImage> ibufs{QImage(800,800,QImage::Format_A2BGR30_Premultiplied)};
QImage ibuf = QImage(800,800,QImage::Format_A2BGR30_Premultiplied);

Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter p2(&ibuf);
    p2.save ();
    p2.setRenderHint(QPainter::Antialiasing);
    if (isclicked == true)
    {
        p2.setPen(QPen(Qt::black,pensize,Qt::SolidLine));
        p2.setBrush(Qt::black);
        p2.drawLine(mx,my,lx,ly);
        p2.setPen(Qt::NoPen);
        p2.end();
        imes = QStringLiteral("%1,%2,%3,%4").arg(mx).arg(my).arg(lx).arg(ly);
        qDebug() << imes;
    }
    p2.restore();
    p2.end();
    QPainter p(this);
    p.drawImage(QPoint(0,0),ibuf);
    p.end();
}

void Canvas::paint()
{
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    isclicked = true;
    penstart();
    QPoint mousepos = event->pos();
    mx = mousepos.x();
    my = mousepos.y();
    lx = mx;
    ly = my;
    l2x = lx;
    l2y = ly;
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    isclicked = false;
    qDebug("Released");
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    QPoint mousepos = event->pos();
    l2x = lx;
    l2y = ly;
    lx = mx;
    ly = my;
    mx = mousepos.x();
    my = mousepos.y();
    if (isclicked == true)
    {
        update();
    } else {
        //lx = mousepos.x();
        //ly = mousepos.y();
    }
    if (pensize < mpensize)
    {
        pensize++;
    }
}

void Canvas::newImage(int *index, int *sizex, int *sizey)
{
    qDebug("新しいイメージの作成 %d", *index);
    QImage pimage = QImage(*sizex,*sizey,QImage::Format_A2BGR30_Premultiplied);
    ibufs.push_back(pimage);
    qDebug("作成完了");
}

void Canvas::removeTab(int *index)
{
    std::vector<QImage>::iterator itr = ibufs.begin();
    itr += *index;

    qDebug("消しまーす");
    ibufs.erase(itr);
    qDebug("消しましたー");
}

void Canvas::focusTab(int *index, int *tabindex)
{
    ibufs[*tabindex] = ibuf;
    ibuf = ibufs[*index];
}

void Canvas::penstart()
{
    pensize = spensize;
}
