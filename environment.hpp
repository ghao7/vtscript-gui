#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include <map>
#include <list>
#include <math.h>

#include "expression.hpp"
#include "interpreter_semantic_error.hpp"


class Environment{
    public:
    //default constructor
    Environment();
    
    Expression mapping(Expression e);
    
    //evaluate sin procedure
    Expression procedureSin(Expression e);
    
    //evaluate cos procedure
    Expression procedureCos(Expression e);
    
    //evaluate arctan procedure
    Expression procedureArctan(Expression e);
    
    //evaluate point procedure
    Expression procedurePoint(Expression e);
    
    //evaluate line procedure
    Expression procedureLine(Expression e);
    
    //evaluate arc procedure
    Expression procedureArc(Expression e);
    
    //evaluate not procedure
    Expression procedureNot(Expression e);
    
    //evaluate and procedure
    Expression procedureAnd(Expression e);
    
    //evaluate or procedure
    Expression procedureOr(Expression e);
    
    //evaluate define procedure
    Expression procedureDefine(Expression e);
    
    //evaluate plus procedure
    Expression procedurePlus(Expression e);
    
    //evaluate multiply procedure
    Expression procedureMultiply(Expression e);
    
    //evaluate division procedure
    Expression procedureDivision(Expression e);
    
    //evaluate if procedure
    Expression procedureIf(Expression e);
    
    //evaluate begin procedure
    Expression procedureBegin(Expression e);
    
    //evaluate relational procedure
    Expression procedureRelational(Expression e);
    
    //evaluate minus procedure
    Expression procedureMinus(Expression e);
    
    //evaluate draw procedure
    Expression procedureDraw(Expression e);
    
    //return true if there is booltype in children
    bool checkBoolInChildren(Expression e);
    
    //setter
    void setMap(std::string str, double d);
    
    //getter
    std::map<std::string,double> getMap();
    
    std::vector<std::vector<Expression>> getItemsToDraw();
    
    //extract double number from map
    double extractNumFromMap(Expression e);
    
    //extract bool number from map
    bool extractBoolFromMap(Expression e);
    
    //extract point from map
    Point extractPointFromMap(Expression e);
    
    //extract line from map
    Line extractLineFromMap(Expression e);
    
    //extract arc from map
    Arc extractArcFromMap(Expression e);
    
    private:
    
    std::map<std::string, double> map;
    
    std::map<std::string, bool> boolMap;
    
    std::map<std::string,Point> pointMap;
    
    std::map<std::string,Line> lineMap;
    
    std::map<std::string,Arc> arcMap;
    
    std::vector<std::vector<Expression>> itemsToDraw;
    
};

#endif
