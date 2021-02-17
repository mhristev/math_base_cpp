#include "point.hpp"

Point::Point(double a, double b): x(a), y(b) {};
Point::Point(): x(0), y(0) {}

double Point::getX()
{
    return x;
}

double Point::getY()
{
    return y;
} 

int Point::cross_formula(Point s, Point e, Point p)
{
    int val = (e.y - s.y) * (p.x - e.x) - (e.x - s.x) * (p.y - e.y); 
  
    if(val == 0)
        return 0;
    if(val > 0) 
        return 1;
    else
        return 2;
}


Point Point::cross_point(Vector v1, Vector v2)
{

    double x1 = v1.getPoints()[0].getX();
    double y1 = v1.getPoints()[0].getY();
    double x2 = v1.getPoints()[1].getX();
    double y2 = v1.getPoints()[1].getY();


    double x3 = v2.getPoints()[0].getX();
    double y3 = v2.getPoints()[0].getY();
    double x4 = v2.getPoints()[1].getX();
    double y4 = v2.getPoints()[1].getY();

    double result_x = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4))/((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));
    double result_y = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4))/((x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4));

    return Point(result_x, result_y);
}


void Point::operator()(double a, double b)
{
    this->x = a;
    this->y = b;
}

ostream& operator<<(ostream& out, Point& p)
{
    cout << "Point: " << p.getX() << " : " << p.getY();
    return out;
}

bool Point::operator==(Vector& v)
{
    if (x == v.getPoints()[0].getX() && y == v.getPoints()[0].getY()) {
        return true;
    } else if (x == v.getPoints()[1].getX() && y == v.getPoints()[1].getY()) {
        return true;
    } else {
        return false;
    }
}