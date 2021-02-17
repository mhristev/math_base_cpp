#include "game.hpp"
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <cmath>
using namespace std;

bool file_exist(string file_name)
{
    ifstream check(file_name);
    return check.good();
}

Game::Game(){
    int hi;
    cout << "Hi, do you want to load a game[1] or create a brand new one[2]? [1]/[2]" << endl;
    bool yo = true;
    while (yo) {
        cin >> hi;
        if (cin.eof()) 
            exit(0);
    
        if (!cin.good() && !cin.eof() && hi != 1 && hi != 2) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please enter a valid value: ";
            continue;
        } else {
            yo = false;
        }
    }
    // creating new game
    if (hi == 1) {
        string file;
        cout << "Loading a game... enter the name of the file: ";
        while (cin >> file) {
            file = file + ".txt";
            if (file_exist(file)) {
                cout << "Reading the file..." << endl;
                read_file(file);
            } else {
                cout << "This file doesn't exist! Try again: ";
            }
        }
    } else if (hi == 2) {   
        string file;
        cout << "Creating new game..." << endl;
        cout << "Enter name for the new file: ";
        while (cin >> file) {
            if (file_exist(file)) {
                cout << "This file already exists! Enter a new name: ";
            } else {
                file = file + ".txt";
                create_game(file);
            }
        }
        
    }
}


void Game::play(Point &start){
    //first vector
    Vector S(start, way); 
    // vector after mult by the power
    Vector T = Mult(S,strength); 
    // find endpoint
    Point end_point((T.getX() + start.getX()), (T.getY() + start.getY())); 
    // vector from the start to the new endpoint
    Vector T2(start, end_point);
    
    int wall = 0;
    int i = 1;
    string write_;

    while (i) {
        //find colision point
        Point col_point;
        if (Vector::Check_Crossing(T2, play_ground->A_B) && wall != 1) {
            col_point = Point::cross_point(T2, play_ground->A_B);
            if (col_point == play_ground->A_B) {
                write_ = "The angle has been hit";
                cout << write_ << endl;
                write_to_file(write_);
            } else {
                write_ = "The ball bounced into the wall (" + to_string(col_point.getX()) + ", " + to_string(col_point.getY())+ ") ";
                cout << write_ << endl;
                write_to_file(write_);
            }
            wall = 1;

        } else if (Vector::Check_Crossing(T2, play_ground->B_C) && wall != 2) {
            col_point = Point::cross_point(T2, play_ground->B_C);
            if (col_point == play_ground->B_C) {
                write_ = "The angle has been hit";
                cout << write_ << endl;
                write_to_file(write_);
            } else {
                write_ = "The ball bounced into the wall (" + to_string(col_point.getX()) + ", " + to_string(col_point.getY())+ ") ";
                cout << write_ << endl;
                write_to_file(write_);
            }
            wall = 2;
        } 
        else if(Vector::Check_Crossing(T2, play_ground->C_D) && wall != 3) {
            col_point = Point::cross_point(T2, play_ground->C_D);
            wall = 3;
            if(col_point == play_ground->C_D) {
                write_ = "The angle has been hit";
                cout << write_ << endl;
                write_to_file(write_);
            } else {
                write_ = "The ball bounced into the wall (" + to_string(col_point.getX()) + ", " + to_string(col_point.getY())+ ") ";
                cout << write_ << endl;
                write_to_file(write_);
            }
        } else if (Vector::Check_Crossing(T2, play_ground->D_A) && wall != 4) {
            col_point = Point::cross_point(T2, play_ground->D_A);
            wall = 4;
            if (col_point == play_ground->D_A) {
                write_ = "The angle has been hit";
                cout << write_ << endl;
                write_to_file(write_);
            } else {
                write_ = "The ball bounced into the wall (" + to_string(col_point.getX()) + ", " + to_string(col_point.getY())+ ") ";
                cout << write_ << endl;
                write_to_file(write_);
            }
        } else {
            if (i == 1) {
                double a = start.getX() + T2.getX();
                double b = start.getY() + T2.getY();
                end_point(a, b);
                cout << "Ball at: " << end_point.getX() << " " << end_point.getY() << endl;
            } else {
            cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
            }
            input(end_point);
            return;
        }
        switch (wall) {
        case 1: {
                    if (col_point == play_ground->A_B) {
                        end_point = first_endpoint();
                        cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
                        input(end_point);
                        return;
                    }
                    Vector start_to_cross(play_ground->A_B.getPoints()[0], col_point);
                    Vector v2(end_point, col_point);
                    Vector bounced = Bounce(v2, start_to_cross);
                    double a = col_point.getX() + bounced.getX();
                    double b = col_point.getY() + bounced.getY();
                    end_point(a, b);
                    break;
                }

        case 2: {
                    if (col_point == play_ground->B_C) {
                        end_point = first_endpoint();
                        cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
                        input(end_point);
                        return;
                    }
                    Vector start_to_cross(play_ground->B_C.getPoints()[0], col_point);
                    Vector v2(end_point, col_point);
                    Vector bounced = Bounce(v2, start_to_cross);
                    double a = col_point.getX() + bounced.getX();
                    double b = col_point.getY() + bounced.getY();
                    end_point(a, b);
                    break;
                }
        case 3: {
                    if (col_point == play_ground->C_D) {
                        end_point = first_endpoint();
                        cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
                        input(end_point);
                        return;
                    }
                    Vector start_to_cross(play_ground->C_D.getPoints()[0], col_point);
                    Vector v2(end_point, col_point);
                    Vector bounced = Bounce(v2, start_to_cross);
                    double a = col_point.getX() + bounced.getX();
                    double b = col_point.getY() + bounced.getY();
                    end_point(a, b);
                    break;
                }
        case 4: {
                    if (col_point == play_ground->D_A) {
                        end_point = first_endpoint();
                        cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
                        input(end_point);
                        return;
                    }
                    Vector start_to_cross(play_ground->D_A.getPoints()[1], col_point);
                    Vector v2(end_point, col_point);
                    Vector bounced = Bounce(v2, start_to_cross);
                    double a = col_point.getX() + bounced.getX();
                    double b = col_point.getY() + bounced.getY();
                    end_point(a, b);
                    break;
                }
        default: {
                    double a = start.getX() + T2.getX();
                    double b = start.getY() + T2.getY();
                    end_point(a, b);
                    cout << "Ball at: "<< end_point.getX() << " " << end_point.getY() << endl;
                    input(end_point);
                    return;
                }
        }
        T2(col_point, end_point);
        i++;
    }
}

void Game::write_to_file(string str)
{
    ofstream out = ofstream(file_name, std::ios::app);
    if (out.is_open()) {
      out << endl;
      out << str;
      out.close();
    }
}

double check_cin(double check)
{  
    bool go = true;
    while (go) {
        cin >> check;
        if (cin.eof()) exit(0);
        if (!cin.good() && !cin.eof()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please enter a valid value: ";
            continue;
        } else {
            go = false;
        }
    }
    return check;
}

double check_power(double power)
{
    bool go = true;
    while (go) {
        cin >> power;
        if (cin.eof()) exit(0);
        if (power <= 5 && power >= 2) {
            go = false;
        } else {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Enter valid power: ";
            continue;
        }
    }
    return power;
}

bool check_cin_vector(Vector s_e, double w)
{
    if (w == 0) {
        return false;
    }
    if ((w/10) < Lenght(s_e) && Lenght(s_e) < (w*3/10)) {
        return false;
    } else {
        cout << "Invalid end point, please change it!" << endl;
        return true;
    }
}

double Game::read_field(string file_name)
{
    this->file_name = file_name;
    ifstream in = ifstream(file_name);
    int p;
    vector <int> cords;

    if (in.is_open()) {
        while (in >> p) {
            cords.push_back(p);
        }
    }
    in.close();
    Point A(cords[0], cords[1]);
    Point B(cords[2], cords[3]);
    Point C(cords[4], cords[5]);
    Point D(cords[6], cords[7]);

    Ground gr(A, B, C, D);
    return gr.find_w();
}

vector <Point> Game::return_corners(string file_name)
{
    ifstream in = ifstream(file_name);
    int p;
    vector <int> corners;

    if (in.is_open()) {
        while (in >> p) {
            corners.push_back(p);
        }
    }
    in.close();
    Point corner1(corners[0], corners[1]);
    Point corner3(corners[4], corners[5]);

    vector <Point> corns;
    corns.push_back(corner1);
    corns.push_back(corner3);

    return corns;
}

void Game::create_game(string file_name)
{
    double x_y;
    ofstream game(file_name);
    if (game.is_open()) {
        cout << "OK, we need the points of the table" << endl;
        bool field = true;
        //creating and checking the field
        while (field) {
            vector <double> check;
            for (int i = 1; i <= 4; i++) {
                cout << "Point " << i << endl;
                cout << "x: ";
                x_y = check_cin(x_y);
                check.push_back(x_y);
                cout << "y: ";
                x_y = check_cin(x_y);
                check.push_back(x_y);
            }
            Point A(check[0], check[1]);
            Point B(check[2], check[3]);
            Point C(check[4], check[5]);
            Point D(check[6], check[7]);
            Ground gr(A, B, C, D);

            if (!gr.check_ground()) {
                cout << "Invalid field! Enter new points!" << endl;
                continue;
            } else {
                for (int i = 0; i < 8; i++) {
                    game << check[i];
                    game << " ";
                }
                field = false;
            }
        }

        
        double xs;
        double xe;
        double ys;
        double ye;
        game << endl;
        // starting point and check if it's in the field
        cout << "Starting point" << endl;
        cout << "x: ";
        xs = check_cin(xs);
        cout << "y: ";
        ys = check_cin(ys);
        vector <Point> corners = return_corners(file_name);
        Point p(xs, ys);

        while(!check_startpoint(corners[0], corners[1], p)) {
            cout << "Out of range... new startpoint, please:" << endl;
            cout << "x: ";
            xs = check_cin(xs);
            cout << "y: ";
            ys = check_cin(ys);
            p(xs, ys);
        }
        game << xs;
        game << " ";
        game << ys;

        double dm;
        game << " ";
        cout << "Diameter: ";
        dm = check_cin(dm);
        game << dm;
        game << endl;
        cout << "Power level: ";
        double power;
        power = check_power(power);
        game << power;
        game << " ";
        bool i = 1;
        // next strikes
        while(i) {        
            cout << "Where to direct the ball? Enter a point: " << endl;
            cout << "x: ";
            xe = check_cin(xe);
            cout << "y: ";
            ye = check_cin(ye);
            double w = read_field(file_name);
            Point st(xs,ys);
            Point end(xe, ye);
            Vector v(st, end);
            i = check_cin_vector(v, w);
        }
        game << xe;
        game << " ";
        game << ye;
        game.close();
    }
    read_file(file_name);
}


void Game::write_to_file(double power, double x, double y)
{
    ofstream out = ofstream(file_name, std::ios::app);
    if (out.is_open()) {
        out << endl;
        out << power << " " << x << " " << y;
        out.close();
    }
}
void Game::write_to_file(Point &p)
{
    ofstream out = ofstream(file_name, std::ios::app);
    if(out.is_open()) {
       out << endl;
       out << "+-----------------------+" << endl; 
       out << p.getX() << " " << p.getY();;
       out.close();
    }
}

void Game::input(Point &end_point)
{
  if (!cin.eof()) {
      string type;
      double x;
      double y;
      double power;
      write_to_file(end_point);
      cout << "Where to direct the ball? Enter a point: " << endl;
      cout << "x: ";
      x = check_cin(x);
      cout << "y: ";
      y = check_cin(y);
      cout << "Power: ";
      power = check_power(power);
      Point endd(x,y);
      Vector v(end_point, endd);
      this->strength = power;
      bool i = check_cin_vector(v, play_ground->find_w());


      while (i) {   
          cout << "x: ";
          x = check_cin(x);
          cout << "y: ";
          y = check_cin(y);
          cout << "Power: ";
          check_power(power);
          endd(x,y);
          v(end_point, endd);
          i = check_cin_vector(v, play_ground->find_w());
     }
     write_to_file(power, x, y);
     this->way = endd;
     cout << way << endl;
     play(end_point);
  }
}

bool check_startpoint(Point corner1, Point corner3, Point p)
{      
    if (p.getX() > corner1.getX() && p.getX() < corner3.getX() && p.getY() > corner1.getY() && p.getY() < corner3.getY()) 
        return true; 
    else
        return false; 
} 

Point Game::help_points(Point p1, Point p2)
{
    // trigonometry
    double tan = atan2(p2.getY() - p1.getY(), p2.getX() - p1.getX());
    double point_x = p1.getX() + (diameter/2) * cos(tan);
    double point_y = p1.getY() + diameter/2 * sin(tan);

    return Point(point_x, point_y);
}


Ground Game::dm_ground(Ground gr)
{
    // finding the mirror points of the angles

    vector <Point> field_points;
    Point p1 = help_points(gr.A_B.getPoints()[0], gr.A_B.getPoints()[1]);
    Point p2 = help_points(gr.D_A.getPoints()[1], gr.D_A.getPoints()[0]);

    double dx  = p2.getX() - p1.getX();
    double dy  = p2.getY() - p1.getY();

    double a   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    double b   = 2 * dx * dy / (dx*dx + dy*dy);

    double x2  = round(a * (gr.A_B.getPoints()[0].getX() - p1.getX()) + b * (gr.A_B.getPoints()[0].getY() - p1.getY()) + p1.getX()); 
    double y2  = round(b * (gr.A_B.getPoints()[0].getX() - p1.getX()) - a * (gr.A_B.getPoints()[0].getY() - p1.getY()) + p1.getY());

    Point mirror(x2, y2);

    field_points.push_back(mirror);
    //-----------------------------------------------------------------------------------------------------------//

    p1 = help_points(gr.B_C.getPoints()[0], gr.B_C.getPoints()[1]);
    p2 = help_points(gr.A_B.getPoints()[1], gr.A_B.getPoints()[0]);

    dx  = p2.getX() - p1.getX();
    dy  = p2.getY() - p1.getY();

    a   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    x2  = round(a * (gr.B_C.getPoints()[0].getX() - p1.getX()) + b * (gr.B_C.getPoints()[0].getY() - p1.getY()) + p1.getX()); 
    y2  = round(b * (gr.B_C.getPoints()[0].getX() - p1.getX()) - a * (gr.B_C.getPoints()[0].getY() - p1.getY()) + p1.getY());

    mirror(x2, y2);

    field_points.push_back(mirror);
   //-------------------------------------------------------------

    p1 = help_points(gr.C_D.getPoints()[0], gr.C_D.getPoints()[1]);
    p2 = help_points(gr.B_C.getPoints()[1], gr.B_C.getPoints()[0]);

    dx  = p2.getX() - p1.getX();
    dy  = p2.getY() - p1.getY();

    a   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    x2  = round(a * (gr.C_D.getPoints()[0].getX() - p1.getX()) + b * (gr.C_D.getPoints()[0].getY() - p1.getY()) + p1.getX()); 
    y2  = round(b * (gr.C_D.getPoints()[0].getX() - p1.getX()) - a * (gr.C_D.getPoints()[0].getY() - p1.getY()) + p1.getY());

    mirror(x2, y2);

    field_points.push_back(mirror);
    //-----------------------------------------------------------------------------------------------------------------------------

    p1 = help_points(gr.D_A.getPoints()[0], gr.D_A.getPoints()[1]);
    p2 = help_points(gr.C_D.getPoints()[1], gr.C_D.getPoints()[0]);

    dx  = p2.getX() - p1.getX();
    dy  = p2.getY() - p1.getY();

    a   = (dx * dx - dy * dy) / (dx * dx + dy*dy);
    b   = 2 * dx * dy / (dx*dx + dy*dy);

    x2  = round(a * (gr.D_A.getPoints()[0].getX() - p1.getX()) + b * (gr.D_A.getPoints()[0].getY() - p1.getY()) + p1.getX()); 
    y2  = round(b * (gr.D_A.getPoints()[0].getX() - p1.getX()) - a * (gr.D_A.getPoints()[0].getY() - p1.getY()) + p1.getY());

    mirror(x2, y2);
    field_points.push_back(mirror);

    return Ground(field_points[0], field_points[1], field_points[2], field_points[3]);
}


void Game::read_file(string filename)
{   
    file_name = filename;
    ifstream in = ifstream(file_name);
    double p;
    vector <double> cords;

    if (in.is_open()) {
        while (in >> p) {
            cords.push_back(p);
        }
    }

    in.close();
    Point A(cords[0], cords[1]);
    Point B(cords[2], cords[3]);
    Point C(cords[4], cords[5]);
    Point D(cords[6], cords[7]);
    diameter = cords[10];

    Ground gr(A, B, C, D);

    if (!gr.check_ground()) {
        cout << "invalid field! Please change it!" << endl;
        exit(0);
    }
    //ground + dm
    Ground gr_dm = dm_ground(gr);
    //start point
    Point start(cords[8], cords[9]);

    if (!check_startpoint(A, C, start)) {
        cout << "Starting point is not inside!" << endl;
        exit(0);
    }

    double str = cords[11];
    Point end(cords[12], cords[13]);
    //first vector
    Vector first_vector(start, end);

    this->play_ground = &gr_dm;
    
    if (check_cin_vector(first_vector, play_ground->find_w()))
        exit(0);

    
    this->start = start;
    this->way = end;
    this->strength = str;
    play(start);
}

Point Game::first_endpoint()
{
    ifstream in = ifstream(file_name);
    double p;
    vector <double> cords;

    if (in.is_open()) {
        while (in >> p) {
            cords.push_back(p);
        }
    }
    in.close();
    Point start(cords[8], cords[9]);
    return start;
}