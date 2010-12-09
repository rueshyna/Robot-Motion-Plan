#include "MotionPlan.h"

Window::Window(vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles){

  _setButton = new QPushButton("Set");
  _resetButton = new QPushButton("Reset");
  _showPathButton = new QPushButton("Show Path");
  _animationButton = new QPushButton("Animation");
  _smoothButton = new QPushButton("Smooth");
  _prePfButton = new QPushButton("PF pre");
  _nextPfButton = new QPushButton("PF next");
  productWindow();
}

QPushButton* Window::setButton(){return _setButton;};
QPushButton* Window::resetButton(){return _resetButton;};
QPushButton* Window::showPathButton(){return _showPathButton;};
QPushButton* Window::animationButton(){return _animationButton;};
QPushButton* Window::smoothButton(){return _smoothButton;};
QPushButton* Window::prePfButton(){return _prePfButton;};
QPushButton* Window::nextPfButton(){return _nextPfButton;};

void Window::productWindow(){
  QWidget* window = new QWidget();
  window->setWindowTitle("MotionPlan");
  window->resize(SCREEN_HIGHT,SCREEN_WIDTH);
  QGridLayout *layout = new QGridLayout;

  QGraphicsScene* mainScene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);
  PainterWidget* mainWidget = new PainterWidget(mainScene);

  QGraphicsScene* pfScene = new QGraphicsScene(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
  PainterWidget* pfWidget = new PainterWidget(pfScene);

  for(vector<ObstacleData>::iterator iter=obstacles->begin(); iter!=obstacles->end() ;++iter){
    ObjectItem *obs = new ObjectItem(mainWidget, &(*iter),NONE);
    mainScene->addItem(obs);
  }

  for(vector<RobotData>::iterator iter=robots->begin(); iter!=robots->end() ;++iter){
    ObjectItem *r_goal = new ObjectItem(mainWidget, &(*iter), R_GOAL);
    ObjectItem *r_init = new ObjectItem(mainWidget, &(*iter), R_INIT);
    mainScene->addItem(r_goal);
    mainScene->addItem(r_init);
  }

  mainWidget->setBackgroundBrush(QColor(230, 200, 167));
  pfWidget->setBackgroundBrush(QColor(230, 200, 167));

  layout->addWidget(mainWidget,0,0,1,4);
  layout->addWidget(pfWidget,0,4,1,8);
  layout->addWidget(setButton(),1,0);
  layout->addWidget(resetButton(),1,1);
  layout->addWidget(showPathButton(),1,2);
  layout->addWidget(animationButton(),1,3);
  layout->addWidget(smoothButton(),1,4);
  layout->addWidget(prePfButton(),1,7);
  layout->addWidget(nextPfButton(),1,8);
  layout->setSizeConstraint(QLayout::SetFixedSize);

  window->setLayout(layout);
  window->resize(SCREEN_WIDTH+50, SCREEN_HIGHT+70);
  window->show();
//  QObject::connect(PFbutton(),SIGNAL(clicked()), this, SLOT(showPF()));
  showPF();
  pfScene->addItem(robots->at(1).bitmapItem());
}
void Window::showPF(){
  Bitmap *map = new Bitmap();
  vector< vector<int> > bmap =  map->setObstacles(obstacles);

  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
   // QTransform matrix;
   // matrix = matrix.rotate(i->goalAngle());
    //for(ControlPoints::iterator j=i->controlPoints()->begin(); j!=i->controlPoints()->end(); ++j){
      //QPointF p = matrix.map(*j)+ *i->goalPos();

      i->setBitmapItem(new BitmapItem(map->NF1(i->goalPos(), &bmap)));

    //}
  }

/*  Bitmap *map = new Bitmap();
  map->setObstacles(obstacles);

  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
    QTransform matrix;
    matrix = matrix.rotate(i->goalAngle());

    for(ControlPoints::iterator j=i->controlPoints()->begin(); j!=i->controlPoints()->end(); ++j){
      QWidget* window = new QWidget();
      QHBoxLayout *layout = new QHBoxLayout;
      vector< vector<int> > bmap;
      QPointF p = matrix.map(*j)+ *i->goalPos();
      bmap = map->NF1(&p);

      QGraphicsScene* scene = new QGraphicsScene(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
      PFwindow* _pf = new PFwindow(scene);
      BitmapItem* mapItem = new BitmapItem(_pf, bmap);
      scene->addItem(mapItem);

      _pf->setRenderHint(QPainter::Antialiasing);
      _pf->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
      layout->addWidget(_pf);
      window->setLayout(layout);
      window->setWindowTitle("Potential Field");
      window->show();
    }
  }*/
  //layout->setSizeConstraint(QLayout::SetFixedSize);
}
