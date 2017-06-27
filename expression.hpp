#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>

enum AtomType {NoneType, BoolType, DoubleType, StringType, PointType, LineType, ArcType};

struct Point{
    double x, y;
};

struct Line{
    Point start;
    Point end;
};

struct Arc{
    Point start;
    Point end;
    double angle;
};

struct Atom{
    AtomType type;
    bool boolValue;
    double doubleValue;
    std::string stringValue;
    Point pointvalue;
    Line lineValue;
    Arc arcValue;
    
};

class Expression{
    
public:
    // Default construct an Expression of type None
    Expression();
    
    // Construct an Expression with a single Boolean atom with value
    Expression(bool value);
    
    // Construct an Expression with a single Number atom with value
    Expression(double value);
    
    // Construct an Expression with a single Symbol atom with value
    Expression(const std::string & value);
    
    // Construct an Expression with a single Point atom with value
    Expression(std::tuple<double,double> value);
    
    // Construct an Expression with a single Line atom with starting
    // point start and ending point end
    Expression(std::tuple<double,double> start,
               std::tuple<double,double> end);
    
    // Construct an Expression with a single Arc atom with center
    // point center, starting point start, and spanning angle angle in radians
    Expression(std::tuple<double,double> start,
               std::tuple<double,double> end,
               double angle);
    
    // Equality operator for two Expressions, two expressions are equal if the have
    // the same type, atom value, and number of arguments
    // Numbers are compared using absolute value of difference less than machine epsilon
    bool operator == (const Expression & exp) const noexcept;
    
    //return true if two point have same x and y.
    bool comparePoints( Point point1,  Point point2) const;
    
    //return true if two lines have same points.
    bool compareLines(Line line1, Line line2)const;
    
    //return true if two arc have same points and angle;
    bool compareArcs(Arc arc1, Arc arc2)const;
        
    //getter
    Atom getData();
    
    //setter
    void setData(Atom data);
    
    //getter
    std::vector<Expression> getChildren();
    
    void setChild(int i, Expression e);
    
    void add(Expression e);
    
    Expression getExpression(int i);
    
    void showData();
        
private:
    
    Atom data;
    std::vector<Expression> children;
};

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) < std::numeric_limits<T>::epsilon();}

#endif
