#ifndef QGRAPHICS_ARC_ITEM_HPP
#define QGRAPHICS_ARC_ITEM_HPP

#include <QGraphicsEllipseItem>
#include <QPainter>
#include <QWidget>

class QGraphicsArcItem: public QGraphicsEllipseItem{
public:
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = Q_NULLPTR);
};

#endif
