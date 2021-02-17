#ifndef VECTOR_HPP
#define VECTOR_HPP

using namespace std;
#include "point.hpp"
#include <iostream>
#include <vector>

class Point;

class Vector
{
    double x;
    double y;
    vector <Point> points;
public:
    Vector(Point start, Point end);
    Vector(double a, double b);
    double getX();
    double getY();
    vector <Point> getPoints();
    static bool Check_Crossing(Vector v1, Vector v2);
    void operator()(Point a, Point b);
    Point operator+(Point &a);
    friend ostream& operator<<(ostream& out, Vector& v); 

};


Vector Add(Vector a, Vector b);
Vector Mult(Vector a, double s);
double Scalar(Vector a, Vector b);
double Lenght(Vector a);
Vector Unit(Vector a);
Vector Project(Vector v, Vector a);
Vector Bounce(Vector v, Vector n);
ostream& operator<<(ostream& out, Vector& v);


#endif