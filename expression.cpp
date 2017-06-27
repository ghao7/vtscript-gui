#include "expression.hpp"
#include <iostream>

Expression::Expression(){
    data.type = NoneType;
}

Expression::Expression(bool value){
    data.type = BoolType;
    data.boolValue = value;
}

Expression::Expression(double value){
    data.type = DoubleType;
    data.doubleValue = value;
}

Expression::Expression(const std::string & value){
    data.type = StringType;
    data.stringValue = value;
}

Expression::Expression(std::tuple<double, double> value){
    data.type = PointType;
    data.pointvalue.x = std::get<0>(value);
    data.pointvalue.y = std::get<1>(value);
}

Expression::Expression(std::tuple<double,double> start,
                       std::tuple<double,double> end){
    data.type = LineType;
    data.lineValue.start.x = std::get<0>(start);
    data.lineValue.start.y = std::get<1>(start);
    data.lineValue.end.x = std::get<0>(end);
    data.lineValue.end.y = std::get<1>(end);
    
}

Expression::Expression(std::tuple<double,double> start,
                       std::tuple<double,double> end,
                       double angle){
    data.type = ArcType;
    data.arcValue.start.x = std::get<0>(start);
    data.arcValue.start.y = std::get<1>(start);
    data.arcValue.end.x = std::get<0>(end);
    data.arcValue.end.y = std::get<1>(end);
    data.arcValue.angle = angle;
    
}

bool Expression::operator == (const Expression & exp) const noexcept{
    
    if (this == &exp){
        return true;
    }
    
    if (this->data.type != exp.data.type){
        return false;
    }

    if (this->data.type == BoolType){
        if (this->data.boolValue != exp.data.boolValue){
            return false;
        }
    }else if (this -> data.type == DoubleType){
        if (!almost_equal(this->data.doubleValue, exp.data.doubleValue, 1)){
            return false;
        }
            
    }else if (this->data.type == StringType){
        if (this->data.stringValue != exp.data.stringValue){
            return false;
        }
    }else if (this->data.type == PointType){
        if (!comparePoints(this->data.pointvalue, exp.data.pointvalue)){
            return false;
        }
    }else if (this->data.type == LineType){
        if (!compareLines(this->data.lineValue, exp.data.lineValue)){
            return false;
        }
    }else if (this->data.type == ArcType){
        if (!compareArcs(this->data.arcValue, exp.data.arcValue)){
            return false;
        }
    }
     
    if (this->children.size() != exp.children.size()){
        return false;
    }
     
    return true;
}

bool Expression::comparePoints(Point point1, Point point2) const{
    if (!almost_equal(point1.x, point2.x, 2)){
        return false;
    }
    if (!almost_equal(point1.y, point2.y, 2)){
        return false;
    }
    return true;
}

bool Expression::compareLines(Line line1, Line line2)const{
    if (!comparePoints(line1.start, line2.start)){
        return false;
    }
    if (!comparePoints(line1.end, line2.end)){
        return false;
    }
    return true;
}

bool Expression::compareArcs(Arc arc1, Arc arc2)const{
    if (!comparePoints(arc1.start, arc2.start)){
        return false;
    }
    if (!comparePoints(arc1.end, arc1.end)){
        return false;
    }
    if (!almost_equal(arc1.angle, arc2.angle, 2)){
        return false;
    }
    return true;
}

Atom Expression::getData(){
    return data;
}

void Expression::setData(Atom data){
    this-> data = data;
}
     

std::vector<Expression> Expression::getChildren(){
    return children;
}

void Expression::add(Expression e){
    children.push_back(e);
}

void Expression::setChild(int i, Expression e){
    children[i] = e;
}

Expression Expression::getExpression(int i){
    return children[i];
}

void Expression::showData(){
    AtomType type = data.type;
    switch (type) {
        case NoneType:
            std::cout << "None" ;
        case BoolType:
            if (data.boolValue == true)
                std::cout << "True";
            else
                std::cout << "False";
            break;
            
        case DoubleType:
            std::cout << data.doubleValue;
            break;
            
        case StringType:
            std::cout << data.stringValue;
            break;
        case PointType:
            std::cout << data.pointvalue.x << "," << data.pointvalue.y ;
            break;
        case LineType:
            std::cout << "(" << data.lineValue.start.x << "," << data.lineValue.start.y << ")("
            << data.lineValue.end.x << "," << data.lineValue.end.y << ")";
            break;
        case ArcType:
            std::cout << "(" << data.arcValue.start.x << "," << data.arcValue.start.y << ")("
            << data.arcValue.end.x << "," << data.arcValue.end.y << ")," << data.arcValue.angle;
            break;
        default:
            break;
    }
}
