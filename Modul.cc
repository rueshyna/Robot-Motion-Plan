#include "MotionPlan.h"

Object::Object(){}
vector< QPolygonF >* Object::getPolygons(){return &polygons;}
QPointF* Object::getInit_position(){return &init_position;}
qreal* Object::getInit_angle(){return &init_angle;}

RobotData::RobotData(){}
QPointF* RobotData::getGoal_position(){return &goal_position;}
qreal* RobotData::getGoal_angle(){return &goal_angle;}
ControlPoints* RobotData::getControlPoint(){return &controlPoint;}

Modul::Modul(){}
vector<ObstacleData>* Modul::getObstacles(){return &obstacle;}
vector<RobotData>* Modul::getRobots(){return &robot;}

void Modul::read_file(string* _file, INPUT file) {
  ifstream object_file(_file->c_str());
  string line("");
  int num_of_objects(0);
  int num_of_polygons(0);
  int num_of_vertices(0);
  int num_of_control_points(0);
  bool isEnd(true);
  STATE states = NUM_OF_OBJECTS;
  Object *object = 0;;
  string commit("#");
  string empty("");
  QPolygonF *polygon = 0;

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
                object = new RobotData();
                break;
              case OBSTACLE :
                object = new ObstacleData();
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
          polygon = new QPolygonF();
          states = VERTICE_POINT;
          break;
        case VERTICE_POINT:{
              istringstream position(line);
              qreal x,y;
              position >> x >> y;
              *polygon << QPointF(x, y);
              //vertice.push_back(point);
              num_of_vertices -= 1;

              if(num_of_vertices == 0){
                object->getPolygons()->push_back(*polygon);
                //object->getVertices()->push_back(vertice);
                //vertice.clear();
                num_of_polygons -= 1;
                if(num_of_polygons){
                  states = NUM_OF_VERTICES;
                }else{
                  states = INIT;
                }
              }
            break;
          }
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
              RobotData* r = static_cast<RobotData*>(object);
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

int Modul::setNumOf(string *str){
  istringstream convert(*str);
  int integer;
  convert >> integer;
  return integer;
}

void Modul::setPosition(string *str, Object *object, STATE state){
  istringstream position(*str);
  double _x, _y, angle;
  position >> _x >> _y >> angle;
  QPointF *p=0;
  RobotData* robot;

  switch(state){
    case INIT :
      p= object->getInit_position();
      *(object->getInit_angle()) = angle;
      break;
    case GOAL :
      robot = static_cast<RobotData*>(object);
      p = robot->getGoal_position();
      *(robot->getGoal_angle()) = angle;
    default :
      break;
  }

  p->setX(_x);
  p->setY(_y);
}

void Modul::setControl(string *str, Object *object){
  istringstream position(*str);
  double _x, _y;
  position >> _x >> _y;
  QPoint *p = new QPoint(_x, _y);
  RobotData* robot = static_cast<RobotData*>(object);
  robot->getControlPoint()->push_back(*p);
}
