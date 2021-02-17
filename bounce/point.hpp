#ifndef POINT_HPP
#define POINT_HPP

#include "vector.hpp"
#include <iostream>
using namespace std;
class Vector;

class Point{
    double x;
    double y;
public:
    Point(double a, double b);
    Point();
    double getX();
    double getY();
    static int cross_formula(Point s, Point e, Point p);
    static Point cross_point(Vector v1, Vector v2);
    void operator()(double a, double b);
    bool operator==(Vector& v);
    friend ostream& operator<<(ostream& out, Point& p);
    friend ostream& operator<<(ostream& out, Vector& v);
};

ostream& operator<<(ostream& out, Point& p);


#endif