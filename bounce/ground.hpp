#ifndef GROUND_HPP
#define GROUND_HPP

#include "vector.hpp"


class Ground{
public:
    Vector A_B;
    Vector B_C;
    Vector C_D;
    Vector D_A;
public:
    Ground(Point a, Point b, Point c, Point d);
    Ground();
    double find_w();
    bool check_ground();
};




#endif