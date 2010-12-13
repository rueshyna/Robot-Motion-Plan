#ifndef DATA_H
#define DATA_H
#include "MotionPlan.h"
class ObjectData{
  public :
    ObjectData();
  protected :
    QVector<QPolygonF> _polygons;
    QPointF _initPos;
    qreal _initAngle;
  public :
    QVector<QPolygonF>* polygons();
    QPointF* initPos();
    qreal initAngle();
    void setInitPos(QPointF*);
    void setInitAngle(qreal);
};

typedef QVector<QPoint> ControlPoints;
class RobotData : public ObjectData{
  public :
    RobotData();
  private :
    QPointF _goalPos;
    qreal _goalAngle;
    ControlPoints _controlPoints;
    BitmapItem* _bitmapItem;
  public :
    QPointF* goalPos();
    qreal goalAngle();
    BitmapItem* bitmapItem();
    ControlPoints* controlPoints();
    void setGoalPos(QPointF*);
    void setGoalAngle(qreal);
    void setBitmapItem(BitmapItem*);
};

class Parser{
  public :
    Parser();
  private :
    vector<RobotData> robots;
    vector<ObstacleData> obstacles;
    int setNumOf(string*);
    void setControl(string*, ObjectData*);
    void setPosition(string*, ObjectData*, STATE);
  public :
    void read_file(string*, INPUT);
    vector<ObstacleData>* getObstacles();
    vector<RobotData>* getRobots();
};
#endif
