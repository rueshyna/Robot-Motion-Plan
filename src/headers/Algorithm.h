#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "MotionPlan.h"

class TreeNode{
  private :
    PointAndAngle* _point;
    TreeNode* _parent;
  public :
    TreeNode(PointAndAngle*);
    TreeNode(PointAndAngle*, TreeNode*);
    PointAndAngle* point();
    TreeNode* parent();
    void setPoint(PointAndAngle*);
    void setTreeNode(TreeNode*);
};

class BFS{
  private :
    BFS();
    static bool empty(vector< stack<PointAndAngle*> >*);
    static void whoIsneighbor(vector<PointAndAngle>*);
    static PointAndAngle* first(vector< stack<PointAndAngle*> >*);
  public :
    static vector< PointAndAngle > path(QPointF*, double, QPointF*, double, vector< vector<int> >* , vector< vector< vector<int> > >*);
};

class Bitmap{
  private :
    Bitmap();
  public :
    static void setObstacle(vector< vector<int> >*, QPolygonF* , double , QPointF*);
    static vector< vector<int> > setObstacles(vector<ObstacleData>*);
    static vector< vector<int> > NF1(QPointF*, vector< vector<int> >*);
};
class CSpace{
  private :
    CSpace();
    static VectorFrom edgeVector(QPointF*, QPointF*, QPointF*, INPUT);
    static double countAngle(double*, double*);
    static bool sortF(VectorFrom,VectorFrom);
    static void findVector(vector<VectorFrom>*, QPolygonF*, INPUT);
    static void sortByAngle(vector<VectorFrom>*);
    static bool minIndex(double, double);
  public :
    static vector< vector < vector<int> > > cObstacle(RobotData*, vector<ObstacleData>*);
};
class VectorFrom : public QPointF{
  private :
    int _from;
    double _angle;
    INPUT _input;
  public :
    VectorFrom();
    VectorFrom(double, double);
    VectorFrom(double, double, int);
    int from();
    void setFrom(int);
    double angle();
    void setAngle(double);
    INPUT Input();
    void setInput(INPUT);
};
#endif
