#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

enum STATE { NUM_OF_OBJECTS=0, NEW_OBJECT, NUM_OF_POLYGONS, NUM_OF_VERTICES, VERTICE_POINT, INIT, GOAL, NUM_OF_CONTROL_POINTS,  CONTROL_POINT };

enum INPUT { ROBOT, OBSTACLE };

using std::vector;
using std::string;
using std::ifstream;
using std::size_t;
using std::istringstream;
using std::cout;
using std::endl;

class Point{
  public :
    Point(double _x = 0.0, double _y = 0.0):x(_x),y(_y){};
  public :
    double* getX();
    double* getY();
  private :
    double x;
    double y;
};

typedef vector<Point> Vertice;

class Object{
  public :
    Object();
  protected :
    vector< Vertice > vertices;
    Point init_position;
    double init_angle;
  public :
    vector< Vertice >* getVertices();
    Point* getInit_position();
    double* getInit_angle();
};

typedef vector<Point> ControlPoints;

class Robot : public Object{
  public :
    Robot();
  private :
    Point goal_position;
    double goal_angle;
    ControlPoints controlPoint;
  public :
    Point* getGoal_position();
    double* getGoal_angle();
    ControlPoints* getControlPoint();
};

typedef Object Obstacle;

class IO{
  public :
    IO();
  private :
    vector<Obstacle> obstacle;
    vector<Robot> robot;
    int setNumOf(string*);
    void setControl(string*, Object*);
    void setPosition(string*, Object*, STATE);
  public :
    void read_file(string*, INPUT);
    vector<Obstacle>* getObstacles();
    vector<Robot>* getRobots();
};
