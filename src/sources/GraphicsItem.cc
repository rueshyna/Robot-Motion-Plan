#include "MotionPlan.h"

ObjectItem::ObjectItem(ObjectData* od, ROBOT_POS r_pos) :dataset(od),mask(*dataset->polygons()), robot_pos(r_pos){
  setScale(SCALE);
  setTransform(QTransform(1.0,0.0,0.0,0.0,-1.0,0.0,0.0,0.0,1.0));
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
  initPos();
}

QRectF ObjectItem::boundingRect() const{
   return QRectF(-45, -45, 90, 90);
}

QPainterPath ObjectItem::shape() const{
  QPainterPath path;

  for(QVector<QPolygonF>::const_iterator i = mask.begin(); i != mask.end(); ++i){
    path.addPolygon(*i);
  }
  return path;
}
void ObjectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
  switch (robot_pos) {
    case (NONE) :
      painter->setBrush(QColor(250,155,155));
      break;
    case (R_INIT) :
      painter->setBrush(QColor(250,255,150));
      break;
    case (R_GOAL) :
      painter->setPen(QColor(150,150,150));
      painter->setBrush(QColor(150,150,150));
      break;
    default : break;
  }
  QVector<QPolygonF> *polys = dataset->polygons();

  for(QVector<QPolygonF>::iterator i = polys->begin(); i != polys->end(); ++i){
    painter->drawPolygon(*i);
  }
}

void ObjectItem::initPos(){
  switch (robot_pos) {
    case (NONE) :
    case (R_INIT) :
      setRotation(static_cast<int>(dataset->initAngle()));
      setPos((*dataset->initPos())*scale());
      break;
    case (R_GOAL) :{
        RobotData* ds_robot = static_cast<RobotData*>(dataset);
        setRotation(static_cast<int>(ds_robot->goalAngle()));
        setPos((*ds_robot->goalPos())*scale());
      }
      break;
    default :
      break;
  }

  setY(SCREEN_HIGHT - pos().y());

}

void ObjectItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
  pressPos = event->scenePos() - pos();
  update();
}

void ObjectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent*){
  setSelected(false);
  update();
}
void ObjectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
  if(event->buttons() == Qt::LeftButton){
    setPos(event->scenePos()-pressPos);
  //QTransform matrix;
  //matrix = matrix.rotate(90);

    switch (robot_pos) {
      case (NONE) :
      case (R_INIT) :{
          dataset->setInitPos(&pos());
          dataset->initPos()->setY(SCREEN_HIGHT - pos().y());
          QPointF newPos = *dataset->initPos()/scale();
          dataset->setInitPos(&QPointF(static_cast<int>(newPos.x()), static_cast<int>(newPos.y())));
        }
        break;
      case (R_GOAL) : {
          RobotData* ds_robot = static_cast<RobotData*>(dataset);
          ds_robot->setGoalPos(&pos());
          ds_robot->goalPos()->setY(SCREEN_HIGHT - pos().y());
          QPointF newPos = *ds_robot->goalPos()/scale();
          ds_robot->setGoalPos(&QPointF(static_cast<int>(newPos.x()), static_cast<int>(newPos.y())));
            cout<<"x "<<(int)dataset->initAngle() <<" "<<(int)newPos.y()<<" "<<(int)newPos.x()<<" " <<(*ds_robot->cSpace())[0][(int)newPos.y()][(int)newPos.x()] <<endl;
          if((*ds_robot->cSpace())[0][(int)newPos.y()][(int)newPos.x()]){
            cout<<"yes"<<endl;
          }else{
            cout<<"no "<<endl;
          }
        }
        break;
      default :
        break;
    }

  }else if(event->buttons() == Qt::RightButton){
    QPointF nowPos = event->scenePos() - pos();
    qreal newAngle = 2.0*M_PI -(atan2(nowPos.y(), nowPos.x())- atan2(pressPos.y(), pressPos.x()))*180.0/M_PI*2.0;
    setRotation(newAngle);

    switch (robot_pos) {
      case (NONE) :
      case (R_INIT) :
        dataset->setInitAngle(static_cast<int>(newAngle));
        break;
      case (R_GOAL) : {
        RobotData* ds_robot = static_cast<RobotData*>(dataset);
        ds_robot->setGoalAngle(static_cast<int>(newAngle));
      }
        break;
      default :
        break;
    }
  }

  update();
}
