#ifndef QT_INTERPRETER_HPP
#define QT_INTERPRETER_HPP
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <string>
#include <sstream>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QtMath>
#include <QRectF>

#include "qgraphics_arc_item.hpp"
#include "interpreter.hpp"


class QtInterpreter: public QObject{
    Q_OBJECT
    
public:
    // Default construct an QtInterpreter with the default environment and an empty AST
    QtInterpreter(QObject * parent = nullptr);
    
    //convert expression to QString
    QString convertToQString(Expression e);
    
    void convertToGraphics(Expression e);
    
    QRectF findRegion(Arc arc);
    
    void parseIss(std::istream &iss);
    
signals:
    // a signal emitting a graphic to be drawn as a pointer
    void drawGraphic(QGraphicsItem * item);
    
    // a signal emitting an informational message
    void info(QString message);
    
    // a signal emitting an error message
    void error(QString message);
    
public slots:
    // a public slot that accepts and expression string and parses/evaluates it
    void parseAndEvaluate(QString entry);
    
private:
    Interpreter interp;
};

#endif
