#ifndef GAME_HPP
#define GAME_HPP

#include "point.hpp"
#include "ground.hpp"
#include "vector.hpp"


class Game{
    string file_name;
    Point start;
    Point way;
    Ground *play_ground; // A, B, C, D
    double strength;
    double diameter;

public:
    Game();
    void input(Point &end_point);
    void write_to_file(double power, double x, double y);
    void write_to_file(Point &p);
    void write_to_file(string str);
    void play(Point &start);
    void read_file(string file_name);
    void create_game(string file_name);
    double read_field(string file_name);
    Point first_endpoint();
    Point help_points(Point p1, Point p2);
    Ground dm_ground(Ground gr);
    vector <Point> return_corners(string file_name);

};

bool file_exist(string file_name);
double check_cin(double check);
double check_power(double power);
bool check_cin_vector(Vector s_e, double w);
bool check_startpoint(Point corner1, Point corner3, Point p);


#endif