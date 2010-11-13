#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QtGui>
#include <vector>
#include <cstring>
#include <string>

#define SCREEN_WIDTH 400
#define SCREEN_HIGHT 400
#define SCALE 3

using std::vector;
using std::string;
using std::ifstream;
using std::size_t;
using std::istringstream;
using std::cout;
using std::endl;

enum STATE { NUM_OF_OBJECTS=0, NUM_OF_POLYGONS, NUM_OF_VERTICES, VERTICE_POINT, INIT, GOAL, NUM_OF_CONTROL_POINTS,  CONTROL_POINT };

enum INPUT { ROBOT, OBSTACLE };

enum ROBOT_POS {R_INIT, R_GOAL, NONE};

/* Modul */
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

typedef ObjectData ObstacleData;
typedef QVector<QPoint> ControlPoints;

class RobotData : public ObjectData{
  public :
    RobotData();
  private :
    QPointF _goalPos;
    qreal _goalAngle;
    ControlPoints _controlPoints;
  public :
    QPointF* goalPos();
    qreal goalAngle();
    ControlPoints* controlPoints();
    void setGoalPos(QPointF*);
    void setGoalAngle(qreal);
};

class Parser{
  public :
    Parser();
  private :
    vector<ObstacleData> obstacle;
    vector<RobotData> robot;
    int setNumOf(string*);
    void setControl(string*, ObjectData*);
    void setPosition(string*, ObjectData*, STATE);
  public :
    void read_file(string*, INPUT);
    vector<ObstacleData>* getObstacles();
    vector<RobotData>* getRobots();
};

/* View */

class Window{
  public :
    Window(vector<RobotData>*, vector<ObstacleData>*);
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
  private :
    void productWindow();
};

class PainterWidget : public QGraphicsView{
  Q_OBJECT
  public :
    PainterWidget(QGraphicsScene* , vector<RobotData>*, vector<ObstacleData>*);
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
  protected :
    void keyPressEvent(QKeyEvent*);
    void scaleView(qreal);
};

class ObjectItem : public QGraphicsItem{
  public:
    ObjectItem(PainterWidget*,ObjectData*, ROBOT_POS);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    void initPos();
  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
  private:
    QPointF pressPos;
    PainterWidget *graph;
    ObjectData* dataset;
    const QVector<QPolygonF> mask;
    ROBOT_POS robot_pos;
};
