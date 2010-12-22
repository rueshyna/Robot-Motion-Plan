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
vector< vector <vector<int> > >* RobotData::cSpace(){return &_cSpace;}
vector<PointAndAngle>* RobotData::path(){return &_path;}
void RobotData::setGoalPos(QPointF* _pos_){_goalPos = *_pos_;}
void RobotData::setGoalAngle(qreal _ang_){_goalAngle = _ang_;}
void RobotData::setBitmapItem(BitmapItem* _bitmapItem_){_bitmapItem = _bitmapItem_;}
void RobotData::setCSpace(vector< vector <vector<int> > >* _cSpace_){_cSpace = *_cSpace_;}
void RobotData::setPath(vector<PointAndAngle>* _path_ ){_path = *_path_;}

