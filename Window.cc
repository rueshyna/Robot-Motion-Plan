#include "MotionPlan.h"

Window::Window(vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles){
  productWindow();
}
void Window::productWindow(){
  QWidget* window = new QWidget();
  window->setWindowTitle("MotionPlan");
  window->resize(SCREEN_HIGHT,SCREEN_WIDTH);
  QGridLayout *blayout = new QGridLayout;
  QVBoxLayout *vlayout = new QVBoxLayout;
  QGraphicsScene* scene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);

  PainterWidget* pwidget = new PainterWidget(scene,robots,obstacles);
  scene->sceneRect().setCoords(0,SCREEN_HIGHT, SCREEN_WIDTH,0);

  //QVector<ObjectItem*> drawObstacles;
  for(vector<ObstacleData>::iterator iter=obstacles->begin(); iter!=obstacles->end() ;++iter){
    ObjectItem *obs = new ObjectItem(pwidget, &(*iter),NONE);
    scene->addItem(obs);
    //drawObstacles.push_back(obs);
  }

  for(vector<RobotData>::iterator iter=robots->begin(); iter!=robots->end() ;++iter){
    ObjectItem *r_init = new ObjectItem(pwidget, &(*iter), R_INIT);
    ObjectItem *r_goal = new ObjectItem(pwidget, &(*iter), R_GOAL);
    scene->addItem(r_init);
    scene->addItem(r_goal);
    //drawObstacles.push_back(obs);
  }

  pwidget->setRenderHint(QPainter::Antialiasing);
  pwidget->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  pwidget->setBackgroundBrush(QColor(230, 200, 167));

  QPushButton *b1 = new QPushButton("b1");
  QPushButton *b2 = new QPushButton("b2");
  QPushButton *b3 = new QPushButton("b3");
  QPushButton *b4 = new QPushButton("b4");

  vlayout->addWidget(pwidget);
  blayout->addWidget(b1,1,0);
  blayout->addWidget(b2,1,1);
  blayout->addWidget(b3,1,2);
  blayout->addWidget(b4,1,3);
  vlayout->addLayout(blayout);
  window->setLayout(vlayout);
  window->resize(SCREEN_WIDTH+100, SCREEN_HIGHT+100);
  window->show();
}
