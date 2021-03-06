#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "MotionPlan.h"

class Smooth{
  private :
    Smooth();
    static bool checkPath(vector< vector < vector<int> > >*, vector< PointAndAngle >*, vector< PointAndAngle >*,int,int);
  public :
    static void smooth(vector< vector < vector<int> > >*, vector< PointAndAngle >*, vector< PointAndAngle >*, int, int);
};

class TreeNode{
  private :
    TreeNode();
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
    static int delta(double, double);
    static bool checkPreIndex(double, double, vector<VectorFrom>* );
    static bool checkNextIndex(double, double, vector<VectorFrom>* );
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
