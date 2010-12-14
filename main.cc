#include "MotionPlan.h"

int main (int argc, char *argv[]){
  QApplication app(argc, argv);
  string robot("robot");
  string obstacle("obstacle");
  vector<RobotData> *robots;
  vector<ObstacleData> *obstacles;
  Parser *parser = new Parser();

  parser->read_file(&robot, ROBOT);
  robots = parser->getRobots();
  parser->read_file(&obstacle, OBSTACLE);
  obstacles = parser->getObstacles();

  Window *window = new Window(robots,obstacles);
//window->showPF();
//QPointF p1 = robots->at(0).polygons()->at(0).at(0);
//QPointF p2 = robots->at(0).polygons()->at(0).at(1);

 //QPointF p = CSpace::edgeVector(&p1, &p2, &QPointF(0,0));
 QVector< QVector <QVector<int> > > a = CSpace::cObstacle(&robots->at(0),obstacles);
  return app.exec();
}
