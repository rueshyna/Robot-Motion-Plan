#include "MotionPlan.h"

int main (int argc, char *argv[]){
  QApplication app(argc, argv);
  string robot("robot");
  string obstacle("obstacle");
  vector<RobotData> *robots;
  vector<ObstacleData> *obstacles;
  Modul *modul = new Modul();

  modul->read_file(&robot, ROBOT);
  robots = modul->getRobots();
  modul->read_file(&obstacle, OBSTACLE);
  obstacles = modul->getObstacles();

  View *view = new View(robots,obstacles);
  return app.exec();
}
