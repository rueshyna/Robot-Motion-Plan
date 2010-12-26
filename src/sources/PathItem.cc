#include "MotionPlan.h"

PathItem::PathItem(QVector<QPolygonF>* _poly_, PointAndAngle* _point_): _poly(_poly_),_point(_point_){
  setScale(SCALE);
  setTransform(QTransform(1.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,1.0));
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
  initPos();
}
QRectF PathItem::boundingRect() const{
   return QRectF(-SCREEN_HIGHT, -SCREEN_WIDTH, 2*SCREEN_HIGHT, 2*SCREEN_WIDTH);
}
QPainterPath PathItem::shape() const{
  QPainterPath path;

  for(QVector<QPolygonF>::const_iterator i = _poly->begin(); i != _poly->end(); ++i){
    path.addPolygon(*i);
  }
  return path;
}
void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
  painter->setPen(QColor(200,50,150));

  for(QVector<QPolygonF>::iterator i = _poly->begin(); i != _poly->end(); ++i){
    painter->drawPolygon(*i);
  }
}
void PathItem::initPos(){
  setRotation(_point->z());
  setPos(QPointF(_point->x(),_point->y())*SCALE);
  setY(SCREEN_HIGHT - pos().y());
}
