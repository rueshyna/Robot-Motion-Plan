#include "MotionPlan.h"

int main(){
  string robot("robot");
  string obstacle("obstacle");
  vector<Robot> *robots;
  vector<Obstacle> *obstacles;
  IO *io = new IO();

  io->read_file(&robot, ROBOT);
  robots = io->getRobots();
  io->read_file(&obstacle, OBSTACLE);
  obstacles = io->getObstacles();


  /*io->read_file(&robot, ROBOT);
  o = io->getRobots();
  for(vector<Robot>::iterator i = o->begin(); i != o->end();++i){
    for(vector<Vertice>::iterator ix = i->getVertices()->begin(); ix != i->getVertices()->end(); ++ix){
      for(Vertice::iterator ixx = ix->begin(); ixx != ix->end(); ++ixx){
        cout <<" x y :" << *(ixx-> getX()) << " " <<  *(ixx-> getY()) <<endl;
      }
    }
    for(vector<Point>::iterator ix = i->getControlPoint()->begin();ix!=i->getControlPoint()->end();++ix){
      cout << "px py : " << *(ix->getX()) << " " <<*(ix->getY()) <<endl;
    }

    cout << "*(i->getInit_position) : " << *(i->getInit_position()->getX()) <<" " << *(i->getInit_position()->getY())<< endl;
    cout << "*(i->getInit_angle) : " << *(i->getInit_angle()) << endl;

    cout << "*(s->getGoal_position) : " << *(i->getGoal_position()->getX()) <<" " << *(i->getGoal_position()->getY())<< endl;
    cout << "*(s->getGoal_angle) : " << *(i->getGoal_angle()) << endl;
  }
  cout << "==================" << endl;
  io->read_file(&obstacle, OBSTACLE);

  s = io->getObstacles();
  for(vector<Obstacle>::iterator i = s->begin(); i != s->end();++i){
    for(vector<Vertice>::iterator ix = i->getVertices()->begin(); ix != i->getVertices()->end(); ++ix){
      for(Vertice::iterator ixx = ix->begin(); ixx != ix->end(); ++ixx){
        cout <<" x y :" << *(ixx-> getX()) << " " <<  *(ixx-> getY()) <<endl;
      }
    }

    cout << "*(i->getInit_position) : " << *(i->getInit_position()->getX()) <<" " << *(i->getInit_position()->getY())<< endl;
    cout << "*(i->getInit_angle) : " << *(i->getInit_angle()) << endl;

  }*/
  return 0;
}
