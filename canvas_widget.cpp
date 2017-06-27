#include "canvas_widget.hpp"


CanvasWidget::CanvasWidget(QWidget * parent):QWidget(parent){
    scene = new QGraphicsScene(this);
    QGraphicsView * view = new QGraphicsView();
    view->setScene(scene);
    
    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(view);
    setLayout(layout);
    
}

void CanvasWidget::addGraphic(QGraphicsItem * item){
    scene->addItem(item);
}

