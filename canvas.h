#ifndef CANVAS_H
#define CANVAS_H
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>
#include <QDebug>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    Canvas(QWidget *parent = nullptr);

    void newImage(int *index, int *sizex, int *sizey);

    void focusTab(int *index, int *tabindex);

    void removeTab(int *index);
protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void paint();

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;

    virtual void penstart();
};

#endif // CANVAS_H
