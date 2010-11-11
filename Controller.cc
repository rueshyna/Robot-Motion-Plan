#include "MotionPlan.h"

Obstacle::Obstacle(){}
Obstacle::Obstacle(PainterWidget *graphView) : graph(graphView),mask(*(dataset.getPolygons())){
  setScale(SCALE);
  setTransform(QTransform(1.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,1.0));
  setFlag(ItemIsMovable, true);
  setFlag(ItemIsSelectable, true);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

Obstacle::Obstacle(PainterWidget *graphView, ObstacleData od) : graph(graphView), dataset(od),mask(*(dataset.getPolygons())){
  setScale(SCALE);
  setTransform(QTransform(1.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,1.0));
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

QRectF Obstacle::boundingRect() const{
   return QRectF(-45, -45, 90, 90);
}

QPainterPath Obstacle::shape() const{
  QPainterPath path;

  for(vector<QPolygonF>::const_iterator i = mask.begin(); i != mask.end(); ++i){
    path.addPolygon(*i);
  }
  return path;
}
void Obstacle::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
  painter->setBrush(QColor(255,150,150));
  vector<QPolygonF> *polys = dataset.getPolygons();

  for(vector<QPolygonF>::iterator i = polys->begin(); i != polys->end(); ++i){
    painter->drawPolygon(*i);
  }
}

void Obstacle::initPos(){
  setPos((*(dataset.getInit_position()))*scale());
  setY(SCREEN_HIGHT - pos().y());
  setRotation(*(dataset.getInit_angle()));
}

void Obstacle::mousePressEvent(QGraphicsSceneMouseEvent* event){
  pressPos = event->scenePos() - pos();

  if(event->button() == Qt::RightButton){
    *(dataset.getInit_position()) = pressPos;
  }
  update();
}

void Obstacle::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
  setSelected(false);
  update();
}
void Obstacle::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
  if(event->buttons() == Qt::LeftButton){
    setPos(event->scenePos()-pressPos);
  }else if(event->buttons() == Qt::RightButton){
    QPointF nowPos = event->scenePos() - pos();
    qreal newAngle = 2.0*M_PI -(atan2(nowPos.y(), nowPos.x())- atan2(pressPos.y(), pressPos.x()))*180.0/M_PI*2.0;
    *(dataset.getInit_angle()) = newAngle;
    setRotation(newAngle);
  }

  update();
}
