#include "MotionPlan.h"

Window::Window(vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles), viewPf(0){
   pathItemPool = new vector<PathItem*>();
   robotInits = new vector<ObjectItem*>();
  _setButton = new QPushButton("Set");
  _resetButton = new QPushButton("Reset");
  _showPathButton = new QPushButton("Show Path");
  _animationButton = new QPushButton("Animation");
  _smoothButton = new QPushButton("Smooth");
  _prePfButton = new QPushButton("PF Pre");
  _nextPfButton = new QPushButton("PF Next");
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
  QGridLayout *layout = new QGridLayout;

  mainScene = new QGraphicsScene(0,0, SCREEN_WIDTH, SCREEN_HIGHT);
  mainWidget = new PainterWidget(mainScene);

  pfScene = new QGraphicsScene(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
  pfWidget = new PainterWidget(pfScene);

  for(vector<ObstacleData>::iterator iter=obstacles->begin(); iter!=obstacles->end() ;++iter){
    ObjectItem *obs = new ObjectItem(&(*iter),NONE);
    mainScene->addItem(obs);
  }

  for(vector<RobotData>::iterator iter=robots->begin(); iter!=robots->end() ;++iter){
    ObjectItem *r_goal = new ObjectItem(&(*iter), R_GOAL);
    ObjectItem *r_init = new ObjectItem(&(*iter), R_INIT);
    mainScene->addItem(r_goal);
    mainScene->addItem(r_init);
    robotInits->push_back(r_init);
  }

  mainWidget->setBackgroundBrush(QColor(230, 200, 167));
  pfWidget->setBackgroundBrush(QColor(180, 200, 167));

  layout->addWidget(mainWidget,0,0,1,4);
  layout->addWidget(pfWidget,0,4,1,8);
  layout->addWidget(setButton(),1,0);
  layout->addWidget(resetButton(),1,1);
  layout->addWidget(showPathButton(),1,2);
  layout->addWidget(animationButton(),1,3);
  layout->addWidget(smoothButton(),2,0);
  layout->addWidget(prePfButton(),1,7);
  layout->addWidget(nextPfButton(),1,8);
  layout->setSizeConstraint(QLayout::SetFixedSize);

  window->setLayout(layout);
  window->resize(SCREEN_WIDTH+50, SCREEN_HIGHT+70);
  window->show();

  vector< vector<int> > bmap =  Bitmap::setObstacles(obstacles);

  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
      i->setBitmapItem(new BitmapItem(Bitmap::NF1(i->goalPos(), &bmap)));
      if(i==robots->begin()){
        i->bitmapItem()->show();
      }else{
        i->bitmapItem()->hide();
      }
      pfScene->addItem(i->bitmapItem());
  }

  QObject::connect(setButton(),SIGNAL(clicked()), this, SLOT(showPf()));
  QObject::connect(prePfButton(),SIGNAL(clicked()), this, SLOT(prePf()));
  QObject::connect(nextPfButton(),SIGNAL(clicked()), this, SLOT(nextPf()));
  QObject::connect(showPathButton(),SIGNAL(clicked()), this, SLOT(showPath()));
  QObject::connect(smoothButton(),SIGNAL(clicked()), this, SLOT(smooth()));
  //QObject::connect(animationButton(),SIGNAL(clicked()), this, SLOT(animation()));
  QObject::connect(resetButton(),SIGNAL(clicked()), this, SLOT(reset()));
}

void Window::animation(){
  for(vector<PathItem*>::iterator i = pathItemPool->begin(); i != pathItemPool->end(); ++i){
    mainScene->removeItem(*i);
  }
  pathItemPool->clear();
  for(int i=0; i!=robotInits->size(); ++i){
    vector<PointAndAngle>* path = robots->at(i).path();
    for(int j=path->size()-1; j!=-1; --j){
      robotInits->at(i)->setPos(QPointF(path->at(j).x()*SCALE,path->at(j).y()*SCALE));
      robotInits->at(i)->setY(SCREEN_HIGHT - robotInits->at(i)->pos().y());
      robotInits->at(i)->setRotation(path->at(j).z());
      mainScene->update();
    }
  }
}

void Window::reset(){
  for(vector<PathItem*>::iterator i = pathItemPool->begin(); i != pathItemPool->end(); ++i){
    mainScene->removeItem(*i);
  }
  pathItemPool->clear();
}
void Window::smooth(){
  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
    int last((i->path()->size())?static_cast<int>(i->path()->size()-1):0);
    vector<PointAndAngle> *path = new vector<PointAndAngle>();
    Smooth::smooth(i->cSpace(), path,i->path(),0,last);
    i->setPath(path);
  }
}
void Window::showPath(){
  for(vector<PathItem*>::iterator i = pathItemPool->begin(); i != pathItemPool->end(); ++i){
    mainScene->removeItem(*i);
  }
  pathItemPool->clear();
  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
    for(vector<PointAndAngle>::iterator j=i->path()->begin(); j!=i->path()->end(); ++j){
      PathItem *pathItem = new PathItem(i->polygons(), &*j);
      pathItemPool->push_back(pathItem);
      mainScene->addItem(pathItem);
    }
  }
}
void Window::prePf(){
  if(viewPf > 0){
    robots->at(viewPf--).bitmapItem()->hide();
    robots->at(viewPf).bitmapItem()->show();
  }
}
void Window::nextPf(){
  if(viewPf < robots->size()-1){
    robots->at(viewPf++).bitmapItem()->hide();
    robots->at(viewPf).bitmapItem()->show();
  }
}
void Window::showPf(){
  vector< vector<int> > bmap =  Bitmap::setObstacles(obstacles);

  for(vector<RobotData>::iterator i=robots->begin(); i!=robots->end(); ++i){
    i->bitmapItem()->setBitmap(&Bitmap::NF1(i->goalPos(), &bmap));
    i->setCSpace(&CSpace::cObstacle(&*i,obstacles));
    i->setPath(&(BFS::path(i->initPos(), i->initAngle(), i->goalPos(), i->goalAngle(), i->bitmapItem()->bitmap(), i->cSpace())));
  }
//  for(vector< vector<int> > ::iterator i = robots->at(0).cSpace()->at(0).begin(); i!=robots->at(0).cSpace()->at(0).end(); ++i){
//    for(vector<int>::iterator j = i->begin(); j!=i->end(); ++j){
//      cout << *j;
//    }
//    cout << endl;
//  }
}
