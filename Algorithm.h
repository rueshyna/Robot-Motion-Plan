#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "MotionPlan.h"
class Bitmap{
  private :
    Bitmap();
  public :
    static vector< vector<int> > setObstacles(vector<ObstacleData>*);
    static vector< vector<int> > NF1(QPointF*, vector< vector<int> >*);
};
class CSpace{
  private :
    CSpace();
    static QPointF edgeVector(QPointF*, QPointF*, QPointF*);
    static int countAngle(double*, double*);
    static bool sortF(const QPointF,const QPointF);
  public :
    static void sortByAngle(vector<QPointF>*);
    static QVector< QVector <QVector<int> > > cObstacle(RobotData*, vector<ObstacleData>*);
  
};
#endif
