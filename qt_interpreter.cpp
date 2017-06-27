#include "qt_interpreter.hpp"

QtInterpreter::QtInterpreter(QObject * parent):QObject(parent){
    
}

void QtInterpreter::parseAndEvaluate(QString entry){
    std::string str = entry.toStdString();
    std::istringstream iss(str);
    bool ok = interp.parse(iss);
    if(!ok){
        qDebug()<< "wrong" ;
        emit error("Error: Connot parse input");
    }else{
        try {
            Expression e = interp.eval();
            QString message = convertToQString(e);
            emit info(message);

            std::vector<std::vector<Expression>> itemsDraw = interp.getEn().getItemsToDraw();
            for (int i = 0; i < itemsDraw.size(); i++){
                for (int j = 0; j< itemsDraw[i].size(); j++){
                    convertToGraphics(itemsDraw[i][j]);
                }
            }
        } catch (const InterpreterSemanticError &e) {
            QString errorM = "Error: " + QString::fromStdString(e.what());
            emit error(errorM);
        }
        
    }
}

void QtInterpreter::parseIss(std::istream &iss){
    bool ok = interp.parse(iss);
    if(!ok){
        qDebug()<< "wrong" ;
        emit error("Error: Connot parse input");
    }else{
        try {
            Expression e = interp.eval();
            QString message = convertToQString(e);
            emit info(message);
            
            std::vector<std::vector<Expression>> itemsDraw = interp.getEn().getItemsToDraw();
            for (int i = 0; i < itemsDraw.size(); i++){
                for (int j = 0; j< itemsDraw[i].size(); j++){
                    convertToGraphics(itemsDraw[i][j]);
                }
            }
            
        } catch (const InterpreterSemanticError &e) {
            QString errorM = "Error: " + QString::fromStdString(e.what());
            emit error(errorM);
        }
        
    }
}

void QtInterpreter:: convertToGraphics(Expression e){
    AtomType type = e.getData().type;
    switch (type) {
        case PointType:
        {
            Point point = e.getData().pointvalue;
            QGraphicsEllipseItem * item = new QGraphicsEllipseItem();
            item->setRect(point.x-2,point.y-2,4,4);
            item->setPen(QPen(Qt::black));
            item->setBrush(QBrush(Qt::black));

            emit (drawGraphic(item));
            break;
        }
        case LineType:
        {
            Line line = e.getData().lineValue;
            QGraphicsItem * item = new QGraphicsLineItem(line.start.x,line.start.y,line.end.x,line.end.y);
            emit (drawGraphic(item));
            break;
        }
        case ArcType:
        {
            QGraphicsArcItem *item = new QGraphicsArcItem;
            Arc arc =e.getData().arcValue;
            QRectF rect = findRegion(arc);
            item->setRect(rect);
            double startAngle = -atan2(arc.end.y - arc.start.y, arc.end.x - arc.start.x);
            item->setStartAngle(qRadiansToDegrees(startAngle)*16);
            
            double angle = e.getData().arcValue.angle;
            item->setSpanAngle(qRadiansToDegrees(angle)*16);
            emit (drawGraphic(item));
            break;
        }
        default:
            throw InterpreterSemanticError("Not drawing type");
            break;
    }
}

QRectF QtInterpreter::findRegion(Arc arc){
    QRectF rect;
    double radius = qSqrt(qPow(arc.start.x - arc.end.x,2) + qPow(arc.start.y- arc.end.y,2));
    rect.setRect(arc.start.x - radius, arc.start.y - radius , 2*radius, 2*radius);
    return rect;
}

QString QtInterpreter::convertToQString(Expression e){
    Atom data = e.getData();
    AtomType type = data.type;
    QString str;
    switch (type) {
        case NoneType:
            str = "(None)";
            break;
        case BoolType:
            if (data.boolValue){
                str =  "(True)";
            }else{
                str =  "(False)";
            }
            break;
        case DoubleType:
            str = "(" + QString::number(data.doubleValue) + ")";
            break;
            
        case StringType:
            str = "(" + QString::fromStdString(data.stringValue) +")";
            break;
        case PointType:
            str = "(" + QString::number(data.pointvalue.x) +"," + QString::number(data.pointvalue.y) + ")";
            break;
        case LineType:
            str =  "((" + QString::number(data.lineValue.start.x) + "," + QString::number(data.lineValue.start.y) + ")(" + QString::number(data.lineValue.end.x)+ "," + QString::number(data.lineValue.end.y) + "))";
            break;
        case ArcType:
            str =  "((" + QString::number(data.arcValue.start.x) + "," + QString::number(data.arcValue.start.y) + ")("
            + QString::number(data.arcValue.end.x) + "," + QString::number(data.arcValue.end.y) + ") " + QString::number(data.arcValue.angle) + ")";
            break;
        default:
            break;
    }
    
    return str;
}
