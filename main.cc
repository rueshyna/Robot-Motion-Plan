#include "MotionPlan.h"

int main (int argc, char *argv[]){
  QApplication app(argc, argv);
  string robot("robot");
  string obstacle("obstacle");
  vector<RobotData> *robots;
  vector<ObstacleData> *obstacles;
  Parser *modul = new Parser();

  modul->read_file(&robot, ROBOT);
  robots = modul->getRobots();
  modul->read_file(&obstacle, OBSTACLE);
  obstacles = modul->getObstacles();

  Window *view = new Window(robots,obstacles);
  return app.exec();
}
