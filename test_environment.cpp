#include <iostream>

#include "catch.hpp"
#include "environment.hpp"

TEST_CASE("Test mapping function" , "[environment]"){
    
}

TEST_CASE("Test define procedure", "[environment]"){
    {
        std::string str = "define";
        std::string str2 = "answer";
        double d = 1;
        Expression e0(str);
        Expression e1(str2);
        Expression e2(d);
    
        e0.add(e1);
        e0.add(e2);
    
        Environment en;
        Expression ee = en.procedureDefine(e0);
        Expression result(1.);
    
        bool check = (ee == result);
        REQUIRE(check);
    }
    {
        std::string str = "define";
        std::string str2 = "a";
        bool b = true;
        Expression e0(str);
        Expression e1(str2);
        Expression e2(b);
        
        e0.add(e1);
        e0.add(e2);
        
        Environment en;
        Expression ee = en.procedureDefine(e0);
        Expression result(true);
        
        bool check = (ee == result);
        REQUIRE(check);
    }
}

TEST_CASE("Test if procedure", "[environment]"){
    {
        std::string str = "if";
        bool b = true;
        double d = 1;
        double dd = 100;
        
        Expression e0(str);
        Expression e1(b);
        Expression e2(d);
        Expression e3(dd);
        
        e0.add(e1);
        e0.add(e2);
        e0.add(e3);
        
        Environment en;
        Expression ee = en.procedureIf(e0);
        Expression result(d);
        
        bool check = (ee == result);
        REQUIRE(check);
    }
    {
        std::string str = "if";
        bool b = false;
        double d = 1;
        double dd = 100;
        
        Expression e0(str);
        Expression e1(b);
        Expression e2(d);
        Expression e3(dd);
        
        e0.add(e1);
        e0.add(e2);
        e0.add(e3);
        
        Environment en;
        Expression ee = en.procedureIf(e0);
        Expression result(dd);
        
        bool check = (ee == result);
        REQUIRE(check);
    }
}

TEST_CASE("procedure error henadling", "[environment]"){
    {
        Environment en;
        Expression e;
        REQUIRE_THROWS_AS(en.procedureNot(e), InterpreterSemanticError);
    }
    {
        Environment en;
        Expression e(true);
        REQUIRE_THROWS_AS(en.procedureNot(e), InterpreterSemanticError);
    }
    {
        Environment en;
        Expression e;
        REQUIRE_THROWS_AS(en.procedureBegin(e), InterpreterSemanticError);
    }
    {
        Environment en;
        Expression e(true);
        REQUIRE_THROWS_AS(en.procedureNot(e), InterpreterSemanticError);
    }

    {
        Environment en;
        Expression e(true);
        REQUIRE_THROWS_AS(en.procedureDefine(e), InterpreterSemanticError);
    }
}

TEST_CASE("Test relational procedure", "[environment]"){
    {
        std::string s = "<";
        double one = 1;
        double two = 2;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        e0.add(e1);
        e0.add(e2);
        Environment en;
        Expression ee = en.procedureRelational(e0);
        REQUIRE(ee.getData().boolValue);
    }
    {
        std::string s = ">";
        double one = 1;
        double two = 2;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        e0.add(e1);
        e0.add(e2);
        Environment en;
        Expression ee = en.procedureRelational(e0);
        REQUIRE(!ee.getData().boolValue);
    }
    {
        std::string s = "<=";
        double one = 1;
        double two = 2;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        e0.add(e1);
        e0.add(e2);
        Environment en;
        Expression ee = en.procedureRelational(e0);
        REQUIRE(ee.getData().boolValue);
    }
    {
        std::string s = "=";
        double one = 1;
        double two = 1;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        e0.add(e1);
        e0.add(e2);
        Environment en;
        Expression ee = en.procedureRelational(e0);
        REQUIRE(ee.getData().boolValue);
    }
}

TEST_CASE("Test set get map", "[environment]"){
    {
        std::map<std::string, double> map;
        Environment en;
        en.setMap("guhao", 185);
        map = en.getMap();
        REQUIRE(map["guhao"] == 185);
    }
}

TEST_CASE("Wrong number of arguments" ,"[environment]"){
    {
        Environment en;
        std::string str = "point";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedurePoint(e), InterpreterSemanticError);
    }
    {
        Environment en;
        std::string str = "line";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedureLine(e), InterpreterSemanticError);
    }
    {
        Environment en;
        std::string str = "arc";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedureArc(e), InterpreterSemanticError);
    }
    {
        Environment en;
        std::string str = "if";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedureIf(e), InterpreterSemanticError);
    }
    {
        Environment en;
        std::string str = "/";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedureDivision(e), InterpreterSemanticError);
    }
    {
        Environment en;
        std::string str = "if";
        Expression e(str);
        REQUIRE_THROWS_AS(en.procedureRelational(e), InterpreterSemanticError);
    }
}

TEST_CASE("Test extractfrommap", "[environment]"){
    
    {
        Environment en;
        Expression e(std::make_tuple(1.,1.),std::make_tuple(10.,10.));
        Line line = en.extractLineFromMap(e);
        REQUIRE(line.start.x == 1);
        REQUIRE(line.start.y == 1);
        REQUIRE(line.end.x == 10);
        REQUIRE(line.end.y == 10);
        
    }
    {
        Environment en;
        Expression e(std::make_tuple(1.,1.),std::make_tuple(10.,10.),5.);
        Arc line = en.extractArcFromMap(e);
        REQUIRE(line.start.x == 1);
        REQUIRE(line.start.y == 1);
        REQUIRE(line.end.x == 10);
        REQUIRE(line.end.y == 10);
        REQUIRE(line.angle == 5);
    }
}

TEST_CASE("Test plus procedure", "[environment]"){
    {
        std::string s = "+";
        double one = 1;
        double two = 2;
        double four = 4;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        Expression e3(four);
        e0.add(e1);
        e0.add(e2);
        e0.add(e3);
        Environment en;
        Expression ee = en.procedurePlus(e0);
        Expression result(7.);
        bool check = (ee == result);
        REQUIRE(check);
    }
    {
        std::string s = "+";
        double one = 1;
        double two = 10;
        double four = 100;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        Expression e3(four);
        e0.add(e1);
        e0.add(e2);
        e0.add(e3);
        Environment en;
        Expression ee = en.procedurePlus(e0);
        Expression result(111.);
        bool check = (ee == result);
        REQUIRE(check);
    }
    {
        std::string s = "+";
        double one = 1;
        double two = 2;
        Expression e0(s);
        Expression e1(one);
        Expression e2(two);
        e0.add(e1);
        e0.add(e2);
        Environment en;
        Expression ee = en.procedurePlus(e0);
        Expression result(3.);
        bool check = (ee == result);
        REQUIRE(check);
    }
}
