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
//vector< vector<int> > set = Bitmap::setObstacles(obstacles);
 // vector< vector<int> > bmap = Bitmap::NF1(robots->at(0).goalPos(), &set);

//  vector< vector <vector<int> > > cspace = CSpace::cObstacle(&robots->at(0),obstacles);
//  vector<PointAndAngle> path = BFS::path(robots->at(0).initPos(), robots->at(0).initAngle(),robots->at(0).goalPos(),robots->at(0).goalAngle(), &bmap, &cspace );
  Window *window = new Window(robots,obstacles);

//  for(vector<PointAndAngle>::iterator i = path.begin(); i!=path.end(); ++i){
//    cout << i->x() <<" " <<i->y() <<" "<<i->z() <<endl;
//  }
//  cout << "init" <<set[robots->at(0).initPos()->y()][robots->at(0).initPos()->x()]<<endl;;
//  cout << "goal" <<set[robots->at(0).goalPos()->y()][robots->at(0).goalPos()->x()]<<endl;;
//window->showPF();
//QPointF p1 = robots->at(0).polygons()->at(0).at(0);
//QPointF p2 = robots->at(0).polygons()->at(0).at(1);

 //QPointF p = CSpace::edgeVector(&p1, &p2, &QPointF(0,0));
  return app.exec();
}
