#include "MotionPlan.h"

double* Point::getX(){return &x;}
double* Point::getY(){return &y;}

Object::Object(){}
vector< Vertice >* Object::getVertices(){return &vertices;}
Point* Object::getInit_position(){return &init_position;}
double* Object::getInit_angle(){return &init_angle;}

Robot::Robot(){}
Point* Robot::getGoal_position(){return &goal_position;}
double* Robot::getGoal_angle(){return &goal_angle;}
ControlPoints* Robot::getControlPoint(){return &controlPoint;}
