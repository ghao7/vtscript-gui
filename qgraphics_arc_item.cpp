#include "qgraphics_arc_item.hpp"

void QGraphicsArcItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget){
    painter->drawArc(this->rect(),this->startAngle(),this->spanAngle());
}
