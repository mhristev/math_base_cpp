#include "vector.hpp"
#include <iostream>
#include <cmath>

using namespace std;


Vector::Vector(Point start, Point end)
{
    this->x = end.getX() - start.getX();
    this->y = end.getY() - start.getY();
    points.push_back(start);
    points.push_back(end);
}

Vector::Vector(double a, double b)
{
    this->x = a;
    this->y = b;
}

double Vector::getX(){
    return x;
}

double Vector::getY()
{
    return y;
}

vector<Point> Vector::getPoints()
{
    return points;
}

bool Vector::Check_Crossing(Vector v1, Vector v2)
{ 
    int pr1 = Point::cross_formula(v1.getPoints()[0], v1.getPoints()[1], v2.getPoints()[0]);
    int pr2 = Point::cross_formula(v1.getPoints()[0], v1.getPoints()[1], v2.getPoints()[1]);
    int pr3 = Point::cross_formula(v2.getPoints()[0], v2.getPoints()[1], v1.getPoints()[0]);
    int pr4 = Point::cross_formula(v2.getPoints()[0], v2.getPoints()[1], v1.getPoints()[1]);

    if(pr1 != pr2 && pr3 != pr4)
        return true;
    else
        return false;
} 

Vector Add(Vector a, Vector b)
{
    return Vector(a.getX() + b.getX(), a.getY() + b.getY());
}

Vector Mult(Vector a, double s)
{
    return Vector(a.getX() * s, a.getY() * s);
}

double Scalar(Vector a, Vector b)
{
    return a.getX() * b.getX() + a.getY() * b.getY();
}


double Lenght(Vector a)
{
    return sqrt(a.getX() * a.getX() + a.getY() * a.getY());
}

Vector Unit(Vector a)
{
    return Mult(a, 1/Lenght(a));
}

Vector Project(Vector v, Vector a)
{
    return Mult(Unit(a), Scalar(v, a)/Lenght(a));
}

Vector Bounce(Vector v, Vector n)
{
    return Add(v, Mult(Project(v, n), -2));
}


void Vector::operator()(Point a, Point b)
{
    this->x = b.getX() - a.getX();
    this->y = b.getY() - a.getY();
    points[0](a.getX(), a.getY());
    points[1](b.getX(), b.getY());
}

ostream& operator<<(ostream& out, Vector& v) {
    cout << "Vector: " << v.getX() << ":" << v.getY() << " with start: " << v.getPoints()[0] << ", end: " << v.getPoints()[1];
    return out;
}


Point Vector::operator+(Point &a)
{
    return Point(x + a.getX(), y + a.getY());
}