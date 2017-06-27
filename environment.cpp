#include <iostream>
#include <cmath>
#include "environment.hpp"

Environment::Environment(){
    map["pi"] = atan2(0., -1.);
}

Expression Environment::mapping(Expression e){
    if (e.getData().type != StringType){
        return e;
    }
    std::string str = e.getData().stringValue;
    
    if (map.find(str) != map.end()){
        double d = map[str];
        Expression ee(d);
        return ee;
    }
    if (pointMap.find(str) != pointMap.end()){
        Point p = pointMap[str];
        Expression ee(std::make_tuple(p.x,p.y));
        return ee;

    }
    if (lineMap.find(str) != lineMap.end()){
        Line l = lineMap[str];
        Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y));
        return ee;

    }
    if (arcMap.find(str) != arcMap.end()){
        Arc l = arcMap[str];
        Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y),l.angle);
        return ee;

    }
    if (boolMap.find(str)!= boolMap.end()){
        bool b = boolMap[str];
        Expression ee(b);
        return ee;
        
    }
    throw InterpreterSemanticError("Not defined");
    
}

Expression Environment::procedureSin(Expression e){
    if (e.getChildren().size() != 1){
        throw InterpreterSemanticError("Invalid argument number");
    }
    double temp = extractNumFromMap(e.getExpression(0));
    temp = sin(temp);
    Expression ee(temp);
    return ee;
}

Expression Environment::procedureCos(Expression e){
    if (e.getChildren().size() != 1){
        throw InterpreterSemanticError("Invalid argument number");
    }
    double temp = extractNumFromMap(e.getExpression(0));
    temp = cos(temp);
    Expression ee(temp);
    return ee;
}

Expression Environment::procedureArctan(Expression e){
    if (e.getChildren().size() != 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    double first = extractNumFromMap(e.getExpression(0));
    double second = extractNumFromMap(e.getExpression(1));
    double temp = atan2(first,second);
    Expression ee(temp);
    return ee;
}

Expression Environment::procedureDraw(Expression e){
    std::vector<Expression> drawList;
    for (int i =0; i< e.getChildren().size(); i++){
        AtomType type = e.getExpression(i).getData().type;
        if (type == PointType || type == LineType || type == ArcType){
            drawList.push_back(e.getExpression(i));
        }else if (type == StringType){
            std::string str = e.getExpression(i).getData().stringValue;
            if (pointMap.find(str) != pointMap.end()){
                Point p = pointMap[str];
                Expression ee(std::make_tuple(p.x,p.y));
                drawList.push_back(ee);
                
            }
            if (lineMap.find(str) != lineMap.end()){
                Line l = lineMap[str];
                Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y));
                drawList.push_back(ee);
                
            }
            if (arcMap.find(str) != arcMap.end()){
                Arc l = arcMap[str];
                Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y),l.angle);
                drawList.push_back(ee);
                
            }

        }
    }
    itemsToDraw.push_back(drawList);
    Expression ee;
    return ee;
}

Expression Environment::procedurePoint(Expression e){
    if (e.getChildren().size() != 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    double first = extractNumFromMap(e.getExpression(0));
    double second = extractNumFromMap(e.getExpression(1));
    Expression ee(std::make_tuple(first,second));
    return ee;
}

Expression Environment::procedureLine(Expression e){
    if (e.getChildren().size() != 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Point point1 = extractPointFromMap(e.getExpression(0));
    Point point2 = extractPointFromMap(e.getExpression(1));
    Expression ee(std::make_tuple(point1.x,point1.y),std::make_tuple(point2.x, point2.y));
    return ee;
}

Expression Environment::procedureArc(Expression e){
    if (e.getChildren().size() != 3){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Point point1 = extractPointFromMap(e.getExpression(0));
    Point point2 = extractPointFromMap(e.getExpression(1));
    double angle = extractNumFromMap(e.getExpression(2));
    Expression ee(std::make_tuple(point1.x,point1.y),std::make_tuple(point2.x, point2.y),angle);
    return ee;
}

Expression Environment::procedureAnd(Expression e){
    bool result = true;
    for (int i = 0; i < e.getChildren().size(); i++){
        Expression child = e.getExpression(i);
        
        bool b = extractBoolFromMap(child);
        result = (result && b);
    }
    Expression ee(result);
    return ee;
}

Expression Environment::procedureOr(Expression e){
    bool result = false;
    for (int i = 0; i < e.getChildren().size(); i++){
        Expression child = e.getExpression(i);
        
        bool b = extractBoolFromMap(child);
        result = (result || b);
    }
    Expression ee(result);
    return ee;
}

Expression Environment::procedureNot(Expression e){
    if (e.getChildren().size() != 1){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Expression first = e.getExpression(0);
    if (first.getData().type != BoolType){
        throw InterpreterSemanticError("Invalid expression type");
    }
    bool result = !extractBoolFromMap(first);
    Expression ee(result);
    return ee;
}

Expression Environment::procedureBegin(Expression e){
    if (e.getChildren().size() == 0){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Expression end = e.getChildren().back();
    return mapping(end);
}

Expression Environment::procedureIf(Expression e){
    if (e.getChildren().size() != 3){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Expression first = e.getChildren()[0];
    Expression second = e.getChildren()[1];
    Expression third = e.getChildren()[2];
    
    if (first.getData().type != BoolType){
        throw InterpreterSemanticError("Non bool type in if");
    }
    bool b = first.getData().boolValue;
    Expression ee;
    if (b){
        ee = second;
    }else{
        ee = third;
    }
    if (ee.getData().type == DoubleType || ee.getData().type == BoolType){
        return ee;
    }
    std::string str = ee.getData().stringValue;
    if (map.find(str) != map.end()){
        double d = map[str];
        Expression ee(d);
        return ee;
    }
    if (boolMap.find(str) != boolMap.end()){
        bool b = boolMap[str];
        Expression ee(b);
        return ee;
    }
    throw InterpreterSemanticError("Not defined");
}

Expression Environment::procedurePlus(Expression e){
    if (checkBoolInChildren(e)){
        throw InterpreterSemanticError("Invalid expression type");
    }
    double temp = 0;
    for (int i = 0; i < e.getChildren().size(); i++){
        double d = extractNumFromMap(e.getExpression(i));
        temp = temp + d;
    }
    Expression ee(temp);
    return ee;
}

Expression Environment::procedureMultiply(Expression e){
    if (checkBoolInChildren(e)){
        throw InterpreterSemanticError("Invalid expression type");
    }
    double result = 1;
    for (int i = 0; i < e.getChildren().size(); i++){
        double d = extractNumFromMap(e.getExpression(i));
        result = result * d;
    }
    Expression ee(result);
    return ee;
}

Expression Environment::procedureDivision(Expression e){
    if (checkBoolInChildren(e)){
        throw InterpreterSemanticError("Invalid expression type");
    }
    if (e.getChildren().size() != 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    double first = extractNumFromMap(e.getExpression(0));
    double second = extractNumFromMap(e.getExpression(1));
    double result = first/second;
    
    Expression ee(result);
    return ee;
}

Expression Environment::procedureRelational(Expression e){
    if (checkBoolInChildren(e)){
        throw InterpreterSemanticError("Invalid expression type");
    }
    if (e.getChildren().size()!= 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    std::string str = e.getData().stringValue;
    double first = extractNumFromMap(e.getExpression(0));
    double second = extractNumFromMap(e.getExpression(1));
    bool result;
    
    if (str == "<"){
        result = (first < second);
    }else if (str == "<="){
        result = (first <= second);
    }else if (str == ">"){
        result = (first > second);
    }else if (str == ">="){
        result = (first >= second);
    }else {
        result = (first == second);
    }
    Expression ee(result);
    return ee;
}

Expression Environment::procedureMinus(Expression e){
    if (checkBoolInChildren(e)){
        throw InterpreterSemanticError("Invalid expression type");
    }
    if (e.getChildren().size() > 2){
        throw InterpreterSemanticError("Too many arguments");
    }
    double result;
    if (e.getChildren().size() == 1){
        double d = extractNumFromMap(e.getExpression(0));
        result = d * (-1);
    }else {
        double d = extractNumFromMap(e.getExpression(0));
        double dd = extractNumFromMap(e.getExpression(1));
        result = d - dd;
    }
    
    Expression ee(result);
    return ee;
}

Expression Environment::procedureDefine(Expression e){
    if (e.getChildren().size() != 2){
        throw InterpreterSemanticError("Invalid argument number");
    }
    Expression first = e.getChildren()[0];
    Expression second = e.getChildren()[1];
    if (first.getData().type != StringType){
        throw InterpreterSemanticError("Wrong type");
    }
    if (first.getData().stringValue == "begin" || first.getData().stringValue == "if"){
        throw InterpreterSemanticError("Redefine special form.");
    }
    if (first.getData().stringValue == "pi"){
        throw InterpreterSemanticError("redefine builtin symbol");
    }
    std::string str = first.getData().stringValue;
    
    if (second.getData().type == BoolType){
        bool b = second.getData().boolValue;
        boolMap[str] = b;
        return second;
    }
    if (second.getData().type == DoubleType){
        double d = second.getData().doubleValue;
        map[str] = d;
        return second;
    }
    if (second.getData().type == PointType){
        Point p = extractPointFromMap(second);
        pointMap[str] = p;
        Expression ee(std::make_tuple(p.x,p.y));
        return ee;
    }
    if (second.getData().type == LineType){
        Line l = extractLineFromMap(second);
        lineMap[str] = l;
        Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y));
        return ee;
    }
    if (second.getData().type == ArcType){
        Arc l = extractArcFromMap(second);
        arcMap[str] = l;
        Expression ee(std::make_tuple(l.start.x,l.start.y),std::make_tuple(l.end.x,l.end.y),l.angle);
        return ee;
    }
    if (map.find(second.getData().stringValue) != map.end()){
        double d = map[second.getData().stringValue];
        map[str] = d;
        Expression ee(d);
        return ee;
    }
    std::string s = second.getData().stringValue;
    boolMap[str] = boolMap[s];
    bool bb = boolMap[str];
    Expression ee(bb);
    return ee;
}

std::map<std::string, double> Environment::getMap(){
    return map;
}

void Environment::setMap(std::string str, double d){
    map[str] = d;
}

bool Environment::extractBoolFromMap(Expression e){
    if (e.getData().type == BoolType){
        return e.getData().boolValue;
    }
    if (boolMap.find(e.getData().stringValue) == boolMap.end()){
        throw InterpreterSemanticError("Not defined");
    }
    bool b = boolMap[e.getData().stringValue];
    return b;
}

double Environment::extractNumFromMap(Expression e){
    if (e.getData().type == DoubleType){
        return e.getData().doubleValue;
    }
    if (map.find(e.getData().stringValue) == map.end()){
        throw InterpreterSemanticError("Not defined");
    }
    double d = map[e.getData().stringValue];
    return d;
}

Point Environment::extractPointFromMap(Expression e){
    if (e.getData().type == PointType){
        return e.getData().pointvalue;
    }
    if (pointMap.find(e.getData().stringValue) == pointMap.end()){
        throw InterpreterSemanticError("Not defined");
    }
    Point p = pointMap[e.getData().stringValue];
    return p;
}

Line Environment::extractLineFromMap(Expression e){
    if (e.getData().type == LineType){
        return e.getData().lineValue;
    }
    if (lineMap.find(e.getData().stringValue) == lineMap.end()){
        throw InterpreterSemanticError("Not defined");
    }
    Line l = lineMap[e.getData().stringValue];
    return l;
}

Arc Environment::extractArcFromMap(Expression e){
    if (e.getData().type == ArcType){
        return e.getData().arcValue;
    }
    if (arcMap.find(e.getData().stringValue) == arcMap.end()){
        throw InterpreterSemanticError("Not defined");
    }
    Arc a = arcMap[e.getData().stringValue];
    return a;
}

std::vector<std::vector<Expression>> Environment::getItemsToDraw(){
    return itemsToDraw;
}

bool Environment::checkBoolInChildren(Expression e){
    for (int i = 0; i < e.getChildren().size(); i++){
        if (e.getExpression(i).getData().type == BoolType){
            return true;
        }
        if (e.getExpression(i).getData().type == StringType){
            if (boolMap.find(e.getExpression(i).getData().stringValue) != boolMap.end()){
                return true;
            }
        }
    }
    return false;
}

