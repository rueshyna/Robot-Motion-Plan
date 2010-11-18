#include "MotionPlan.h"

Window::Window(vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles){

  _PFbutton = new QPushButton("PF");
  b2 = new QPushButton("b2");
  b3 = new QPushButton("b3");
  b4 = new QPushButton("b4");
  productWindow();
}

QPushButton* Window::PFbutton(){return _PFbutton;};

void Window::productWindow(){
  QWidget* window = new QWidget();
  window->setWindowTitle("MotionPlan");
  window->resize(SCREEN_HIGHT,SCREEN_WIDTH);
  QGridLayout *blayout = new QGridLayout;
  QVBoxLayout *vlayout = new QVBoxLayout;
  QGraphicsScene* scene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);

  PainterWidget* pwidget = new PainterWidget(scene,robots,obstacles);

  for(vector<ObstacleData>::iterator iter=obstacles->begin(); iter!=obstacles->end() ;++iter){
    ObjectItem *obs = new ObjectItem(pwidget, &(*iter),NONE);
    scene->addItem(obs);
  }

  for(vector<RobotData>::iterator iter=robots->begin(); iter!=robots->end() ;++iter){
    ObjectItem *r_goal = new ObjectItem(pwidget, &(*iter), R_GOAL);
    ObjectItem *r_init = new ObjectItem(pwidget, &(*iter), R_INIT);
    scene->addItem(r_goal);
    scene->addItem(r_init);
    //drawObstacles.push_back(obs);
  }

  pwidget->setRenderHint(QPainter::Antialiasing);
  pwidget->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
  pwidget->setBackgroundBrush(QColor(230, 200, 167));

  vlayout->addWidget(pwidget);
  blayout->addWidget(_PFbutton,1,0);
  blayout->addWidget(b2,1,1);
  blayout->addWidget(b3,1,2);
  blayout->addWidget(b4,1,3);
  vlayout->addLayout(blayout);
  window->setLayout(vlayout);
  window->resize(SCREEN_WIDTH+100, SCREEN_HIGHT+100);
  window->show();

  QObject::connect(PFbutton(),SIGNAL(clicked()), this, SLOT(showPF()));
}
void Window::showPF(){
  Bitmap *map = new Bitmap();
  map->setObstacles(obstacles);
  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
    QTransform matrix;
    matrix = matrix.rotate(i->goalAngle());
    for(ControlPoints::iterator j=i->controlPoints()->begin(); j!=i->controlPoints()->end(); ++j){
      vector< vector<int> > bmap;
      QPointF p = matrix.map(*j)+ *i->goalPos();
      bmap = map->NF1(&p);

      QVBoxLayout *vlayout = new QVBoxLayout;
      QWidget* window = new QWidget();
      QGraphicsScene* scene = new QGraphicsScene(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
      PFwindow* _pf = new PFwindow(scene);
      BitmapItem* mapItem = new BitmapItem(_pf, bmap);
      scene->addItem(mapItem);

      _pf->setRenderHint(QPainter::Antialiasing);
      _pf->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
      _pf->setBackgroundBrush(QColor(230, 200, 167));

      vlayout->addWidget(_pf);
      window->setLayout(vlayout);
      window->setWindowTitle("Potential Field");
      window->resize(PF_WIDTH+100, PF_HIGHT+100);
      window->show();
      //cout <<"map: " <<endl;
     // for(int k=0; k!=128; ++k){
     //   for(int l=0; l!=128; ++l){
     //     cout << bmap[l][k] << " ";
     //   }
     //   cout <<endl;
     // }
    }
  }
}
