#include "MotionPlan.h"

IO::IO(){}

vector<Obstacle>* IO::getObstacles(){return &obstacle;}
vector<Robot>* IO::getRobots(){return &robot;}

void IO::read_file(string* _file, INPUT file) {
  ifstream object_file(_file->c_str());
  string line;
  int num_of_objects;
  int num_of_polygons;
  int num_of_vertices;
  int num_of_control_points;
  bool isEnd(true);
  STATE states = NUM_OF_OBJECTS;
  Object *object;
  string commit("#");
  string empty("");
  Vertice vertice;

  while(isEnd){
    if(!getline(object_file,line)){break;}

    if(line != empty && line.at(0) != commit.at(0)){
      switch (states){
        case NUM_OF_OBJECTS :
          num_of_objects = setNumOf(&line);
          states = NUM_OF_POLYGONS;
          break;
        case NUM_OF_POLYGONS :
          if(num_of_objects){
            switch(file){
              case ROBOT :
                object = new Robot();
                break;
              case OBSTACLE :
                object = new Obstacle();
                break;
              default : break;
            }
            num_of_polygons = setNumOf(&line);
            states = NUM_OF_VERTICES;
          }
          else{
            isEnd=false;
          }
          break;
        case NUM_OF_VERTICES :
          num_of_vertices = setNumOf(&line);
          states = VERTICE_POINT;
          break;
        case VERTICE_POINT:{
            istringstream position(line);
            double x,y;
            position >> x >> y;
            Point point(x, y);
            vertice.push_back(point);
            num_of_vertices -= 1;

            if(num_of_vertices == 0){
              object->getVertices()->push_back(vertice);
              vertice.clear();
              num_of_polygons -= 1;
              if(num_of_polygons){
                states = NUM_OF_VERTICES;
              }else{
                states = INIT;
              }
            }
          break;}
        case INIT :
          setPosition(&line, object, INIT);
          switch(file){
            case ROBOT:
              states = GOAL;
              break;
            case OBSTACLE:
              states = NUM_OF_POLYGONS;
              num_of_objects -= 1;
              obstacle.push_back(*object);
              break;
            default : break;
          }
          break;
        case GOAL :
          setPosition(&line, object, GOAL);
          states = NUM_OF_CONTROL_POINTS;
          break;
        case NUM_OF_CONTROL_POINTS :
          num_of_control_points = setNumOf(&line);
          states = CONTROL_POINT;
          break;
        case CONTROL_POINT :{
            setControl(&line, object);
            num_of_control_points -= 1;
            if(num_of_control_points == 0){
              Robot* r = static_cast<Robot*>(object);
              robot.push_back(*r);
              states = NUM_OF_POLYGONS;
              num_of_objects -=1;
            }
            break;
          }
        default :
          break;
      }
    }
  }
}

int IO::setNumOf(string *str){
  istringstream convert(*str);
  int integer;
  convert >> integer;
  return integer;
}

void IO::setPosition(string *str, Object *object, STATE state){
  istringstream position(*str);
  double _x, _y, angle;
  position >> _x >> _y >> angle;
  Point *p;
  Robot* robot;

  switch(state){
    case INIT :
      p= object->getInit_position();
      *(object->getInit_angle()) = angle;
      break;
    case GOAL :
      robot = static_cast<Robot*>(object);
      p = robot->getGoal_position();
      *(robot->getGoal_angle()) = angle;
      break;
  }

  *(p->getX()) = _x;
  *(p->getY()) = _y;
}

void IO::setControl(string *str, Object *object){
  istringstream position(*str);
  double _x, _y;
  position >> _x >> _y;
  Point *p = new Point(_x, _y);
  Robot* robot = static_cast<Robot*>(object);
  robot->getControlPoint()->push_back(*p);
}
