#include "catch.hpp"
#include "expression.hpp"
#include <math.h>
#include <string>
#include <iostream>

#include "tokenize.hpp"

TEST_CASE("Test Expression constructor", "[Expression]"){
    
    {
        Expression e;
        REQUIRE(e.getData().type == NoneType);
    }
    {
        Expression e(true);
        REQUIRE(e.getData().type == BoolType);
        REQUIRE(e.getData().boolValue);
    }
    {
        std::string str = "stringhaha";
        Expression e(str);
        REQUIRE(e.getData().type == StringType);
        REQUIRE(e.getData().stringValue == "stringhaha");
    }
    {
        double d = 10.6;
        Expression e(d);
        REQUIRE(e.getData().type == DoubleType);
        REQUIRE(e.getData().doubleValue == 10.6);
    }
    {
        Expression e(std::make_tuple(1.,2.));
        REQUIRE(e.getData().type == PointType);
        REQUIRE(e.getData().pointvalue.x == 1.);
        REQUIRE(e.getData().pointvalue.y == 2.);
    }
    {
        Expression e(std::make_tuple(1.,2.),std::make_tuple(3.,4.));
        REQUIRE(e.getData().type == LineType);
        REQUIRE(e.getData().lineValue.start.x == 1.);
        REQUIRE(e.getData().lineValue.start.y == 2.);
        REQUIRE(e.getData().lineValue.end.x == 3.);
        REQUIRE(e.getData().lineValue.end.y == 4.);
    }
    {
        Expression e(std::make_tuple(1.,2.),std::make_tuple(3.,4.), 5.);
        REQUIRE(e.getData().type == ArcType);
        REQUIRE(e.getData().arcValue.start.x == 1.);
        REQUIRE(e.getData().arcValue.start.y == 2.);
        REQUIRE(e.getData().arcValue.end.x == 3.);
        REQUIRE(e.getData().arcValue.end.y == 4.);
        REQUIRE(e.getData().arcValue.angle == 5.);
    }
    
}

TEST_CASE("Test setdata function", "[expression]"){
    {
        Expression e(true);
        Expression ee;
        Atom a;
        a.type = BoolType;
        a.boolValue = true;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
    {
        std::string str = "hello";
        Expression e(str);
        Expression ee;
        Atom a;
        a.type = StringType;
        a.stringValue = "hello";
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
    {
        double d = 123.45;
        Expression e(d);
        Expression ee;
        Atom a;
        a.type = DoubleType;
        a.doubleValue = d;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
    {
        double d =  1 / std::sqrt(5) / std::sqrt(5);
        std::cout << d << std::endl;
        Expression e(0.2);
        Expression ee;
        Atom a;
        a.type = DoubleType;
        a.doubleValue = d;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
    {
        Expression e(std::make_tuple(1.,2.));
        Atom a;
        a.type = PointType;
        a.pointvalue.x = 1.;
        a.pointvalue.y = 2.;
        Expression ee;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(e.getData().type == ee.getData().type);
        REQUIRE(check);
    }

}

TEST_CASE("Additional setdata test", "[Expression]"){
    {
        Expression e(std::make_tuple(1.,2.));
        Atom a;
        a.type = LineType;
        a.pointvalue.x = 1.;
        a.pointvalue.y = 2.;
        Expression ee;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(!check);
    }
    {
        Expression e(std::make_tuple(1.,2.));
        Atom a;
        a.type = PointType;
        a.pointvalue.x = 1.;
        a.pointvalue.y = 3.;
        Expression ee;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(!check);
    }
    {
        Expression e(std::make_tuple(1.,2.),std::make_tuple(3.,4.));
        Atom a;
        a.type = LineType;
        a.lineValue.start.x = 1.;
        a.lineValue.start.y = 2.;
        a.lineValue.end.x = 3.;
        a.lineValue.end.y = 4.;
        Expression ee;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
    {
        Expression e(std::make_tuple(1.,2.),std::make_tuple(3.,4.),5.);
        Atom a;
        a.type = ArcType;
        a.arcValue.start.x = 1.;
        a.arcValue.start.y = 2.;
        a.arcValue.end.x = 3.;
        a.arcValue.end.y = 4.;
        a.arcValue.angle = 5.;
        Expression ee;
        ee.setData(a);
        bool check = (e == ee);
        REQUIRE(check);
    }
}

TEST_CASE("Test = sign", "[Expression]"){
    {
        double a = 1;
        double b = 2;
        double c = 3;
        double d = 4;
        double e = 5;
        double f = 6;
        
        Expression g(a);
        Expression h(b);
        Expression i(c);
        Expression j(d);
        Expression k(e);
        
        h.add(j);
        h.add(k);
        
        g.add(h);
        g.add(i);
        
        Expression test = h;
        
        bool check0 = (test == h);
        REQUIRE(check0);
        
        bool check = (g.getChildren()[0] == h);
        REQUIRE(check);
    }
}

TEST_CASE("Test show data", "[expression]"){
    {
        Expression e(true);
        e.showData();
    }
    {
        Expression e(false);
        e.showData();
    }
    {
        Expression e;
        e.showData();
    }
    {
        std::string str = "earth";
        Expression e(str);
        e.showData();
    }
    {
        double d = 99.9;
        Expression e(d);
        e.showData();
    }
    {
        Expression e(std::make_tuple(1.,1.));
        e.showData();
    }
    {
        Expression e(std::make_tuple(1.,1.),std::make_tuple(1.,1.));
        e.showData();
    }
    {
        Expression e(std::make_tuple(1.,1.),std::make_tuple(1.,1.),5.);
        e.showData();
    }
}

TEST_CASE("Test set data", "[expression]"){
    {
        Atom a;
        a.type = StringType;
        a.stringValue = "hello";
        Expression e;
        e.setData(a);
        
        REQUIRE(e.getData().type == a.type);
        REQUIRE(e.getData().stringValue == a.stringValue);
    }
    {
        Atom a;
        a.type = DoubleType;
        a.doubleValue = 1.;
        Expression e;
        e.setData(a);
        
        REQUIRE(e.getData().type == a.type);
        REQUIRE(e.getData().doubleValue == a.doubleValue);
    }
    {
        Atom a;
        a.type = BoolType;
        a.boolValue = true;
        Expression e;
        e.setData(a);
        
        REQUIRE(e.getData().type == a.type);
        REQUIRE(e.getData().boolValue == a.boolValue);
    }
}

TEST_CASE("Test == operator overloading", "[expression]"){
    
    {
        std::string str = "define";
        std::string str1 = "a";
        double d = 1;
        Expression a(str);
        Expression b(str1);
        Expression c(d);
        
        a.add(b);
        a.add(c);
        
        std::string str2 = "define";
        std::string str3 = "b";
        double d2 = 2;
        Expression a1(str2);
        Expression b1(str3);
        Expression c1(d);
        
        a1.add(b1);
        a1.add(c1);
        
        bool boolean = (a == a1);
        REQUIRE(boolean);
    }
    {
        Expression a(true);
        Expression b(false);
  
        bool boolean = (a == b);
        REQUIRE(!boolean);
    }
    {
        Expression a(true);
        
        bool boolean = (a == a);
        REQUIRE(boolean);
    }
    {
        std::string str = "define";
        std::string str1 = "a";
        double d = 1;
        Expression a(str);
        Expression b(str1);
        Expression c(d);
        a.add(b);
        a.add(c);
        std::string str2 = "define1";
        std::string str3 = "b";
        double d2 = 2;
        Expression a1(str2);
        Expression b1(str3);
        Expression c1(d);
        a1.add(b1);
        a1.add(c1);
        bool boolean = (a == a1);
        REQUIRE(!boolean);
    }
     
}

TEST_CASE("test additional","[expression]"){
    {
        double d1 = 1.0;
        double d2 = 0.1;
        Expression a(d1);
        Expression b(d2);
        
        bool boolean = (a == b);
        REQUIRE(!boolean);
    }

    {
        std::string str = "define";
        std::string str1 = "a";
        double d = 1;
        Expression a(str);
        Expression b(str1);
        Expression c(d);
        a.add(b);
        a.add(c);
        std::string str2 = "define";
        std::string str3 = "b";
        double d2 = 2;
        bool boo = true;
        Expression a1(str2);
        Expression b1(str3);
        Expression c1(d);
        Expression d1(boo);
        a1.add(b1);
        a1.add(c1);
        a1.add(d1);
        bool boolean = (a == a1);
        REQUIRE(!boolean);
    }
    {
        std::string str = "define";
        Expression a(str);
        Expression b(str);
        bool boolean = (a == b);
        REQUIRE(boolean);
    }
    {
        std::string str = "define";
        double d = 1.0;
        Expression a(str);
        Expression b(d);
        
        bool boolean = (a == b);
        REQUIRE(!boolean);
    }
}

