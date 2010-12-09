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

  return app.exec();
}
