#include "ground.hpp"

Ground::Ground(Point a, Point b, Point c, Point d): A_B(a, b), B_C(b, c), C_D(c, d), D_A(d, a) {}

bool Ground::check_ground()
{
    double w = Lenght(A_B);
    double h = Lenght(D_A);

    bool t = false;
    bool t2 = false; 

    if(w*2 == h)
    {
        t = true;
    }

    if(h*2 == w)
    {
        t2 = true;
    }

    if(t || t2)
    {
        return true;
    } else {
        return false;
    }
    
}

double Ground::find_w()
{
    vector<double> Lenghts;
    Lenghts.push_back(Lenght(A_B));
    Lenghts.push_back(Lenght(B_C));
    Lenghts.push_back(Lenght(C_D));
    Lenghts.push_back(Lenght(D_A));

    double res = 0;
    for(int i = 0; i < 4; i++)
    {
        if(Lenghts[i] > res)
        {
            res = Lenghts[i];
        }
    }

    return res;
}