#include "MotionPlan.h"

int main (int argc, char *argv[]){
  QApplication app(argc, argv);
  string robot("./src/data/robot");
  string obstacle("./src/data/obstacle");
  vector<RobotData> *robots;
  vector<ObstacleData> *obstacles;
  Parser *parser = new Parser();

  parser->read_file(&robot, ROBOT);
  robots = parser->getRobots();
  parser->read_file(&obstacle, OBSTACLE);
  obstacles = parser->getObstacles();

  vector< vector <vector<int> > > cspace = CSpace::cObstacle(&robots->at(0),obstacles);

  Window *window = new Window(robots,obstacles, &cspace);
//window->showPF();
//QPointF p1 = robots->at(0).polygons()->at(0).at(0);
//QPointF p2 = robots->at(0).polygons()->at(0).at(1);

 //QPointF p = CSpace::edgeVector(&p1, &p2, &QPointF(0,0));
 
  return app.exec();
}
