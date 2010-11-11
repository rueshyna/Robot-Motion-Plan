#include "MotionPlan.h"

PainterWidget::PainterWidget(QGraphicsScene* outscene,  vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles){
  setScene(outscene);
  setCacheMode(CacheBackground);
  setViewportUpdateMode(BoundingRectViewportUpdate);
  setRenderHint(QPainter::Antialiasing);
  setTransformationAnchor(AnchorUnderMouse);
  setResizeAnchor(AnchorViewCenter);
}

void PainterWidget::keyPressEvent(QKeyEvent* event){
  switch (event->key()) {
   case Qt::Key_Up:
       break;
   case Qt::Key_Down:
       break;
   case Qt::Key_Left:
       break;
   case Qt::Key_Right:
       break;
   case Qt::Key_Plus:
       scaleView(qreal(1.2));
       break;
   case Qt::Key_Minus:
       scaleView(1 / qreal(1.2));
       break;
   case Qt::Key_Space:
   case Qt::Key_Enter:
       break;
   default:
       QGraphicsView::keyPressEvent(event);
   }
};
void PainterWidget::scaleView(qreal scaleFactor){
  qreal factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
  if (factor < 0.07 || factor > 100)
      return;

  scale(scaleFactor, scaleFactor);
};
View::View(vector<RobotData>* _robots, vector<ObstacleData>* _obstacles): robots(_robots), obstacles(_obstacles){
  productWindow();
}

void View::productWindow(){
  QWidget* window = new QWidget();
  window->setWindowTitle("MotionPlan");
  window->resize(SCREEN_HIGHT,SCREEN_WIDTH);
  QGridLayout *blayout = new QGridLayout;
  QVBoxLayout *vlayout = new QVBoxLayout;
  QGraphicsScene* scene = new QGraphicsScene(0, 0, SCREEN_WIDTH, SCREEN_HIGHT);

  PainterWidget* pwidget = new PainterWidget(scene,robots,obstacles);
  scene->sceneRect().setCoords(0,SCREEN_HIGHT, SCREEN_WIDTH,0);

  QVector<Obstacle*> drawObstacles;
  for(vector<ObstacleData>::iterator iter=obstacles->begin(); iter!=obstacles->end() ;++iter){
    Obstacle *obs = new Obstacle(pwidget, *iter);
    drawObstacles.push_back(obs);
    obs->initPos();
    scene->addItem(&(*obs));
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
