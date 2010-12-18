#include "MotionPlan.h"
ObjectData::ObjectData(){}
QVector< QPolygonF >* ObjectData::polygons(){return &_polygons;}
QPointF* ObjectData::initPos(){return &_initPos;}
qreal ObjectData::initAngle(){return _initAngle;}
void ObjectData::setInitPos(QPointF* _pos_){_initPos = *_pos_;}
void ObjectData::setInitAngle(qreal _ang_){_initAngle = _ang_;}

RobotData::RobotData(){
  _bitmapItem = new BitmapItem();
}
QPointF* RobotData::goalPos(){return &_goalPos;}
qreal RobotData::goalAngle(){return _goalAngle;}
BitmapItem* RobotData::bitmapItem(){return _bitmapItem;};
ControlPoints* RobotData::controlPoints(){return &_controlPoints;}
void RobotData::setGoalPos(QPointF* _pos_){_goalPos = *_pos_;}
void RobotData::setGoalAngle(qreal _ang_){_goalAngle = _ang_;}
void RobotData::setBitmapItem(BitmapItem* _bitmapItem_){_bitmapItem = _bitmapItem_;}

