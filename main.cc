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

  Bitmap *map = new Bitmap();
  map->setObstacles(obstacles);
  Window *view = new Window(robots,obstacles);


  return app.exec();
}
