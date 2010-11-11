#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QtGui>

#define SCREEN_WIDTH 400
#define SCREEN_HIGHT 400
#define SCALE 3

enum STATE { NUM_OF_OBJECTS=0, NUM_OF_POLYGONS, NUM_OF_VERTICES, VERTICE_POINT, INIT, GOAL, NUM_OF_CONTROL_POINTS,  CONTROL_POINT };

enum INPUT { ROBOT, OBSTACLE };

enum BUTTON { LEFT, RIGHT};

using std::vector;
using std::string;
using std::ifstream;
using std::size_t;
using std::istringstream;
using std::cout;
using std::endl;

typedef QVector<QPoint> Vertice;

class Object{
  public :
    Object();
  protected :
    vector<QPolygonF> polygons;
    QPointF init_position;
    qreal init_angle;
  public :
    vector<QPolygonF>* getPolygons();
    QPointF* getInit_position();
    qreal* getInit_angle();
};

typedef Object ObstacleData;
typedef QVector<QPoint> ControlPoints;

class RobotData : public Object{
  public :
    RobotData();
  private :
    QPointF goal_position;
    qreal goal_angle;
    ControlPoints controlPoint;
  public :
    QPointF* getGoal_position();
    qreal* getGoal_angle();
    ControlPoints* getControlPoint();
};


class Modul{
  public :
    Modul();
  private :
    vector<ObstacleData> obstacle;
    vector<RobotData> robot;
    int setNumOf(string*);
    void setControl(string*, Object*);
    void setPosition(string*, Object*, STATE);
  public :
    void read_file(string*, INPUT);
    vector<ObstacleData>* getObstacles();
    vector<RobotData>* getRobots();
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

class Obstacle : public QGraphicsItem{
  public:
    Obstacle();
    Obstacle(PainterWidget*);
    Obstacle(PainterWidget*,ObstacleData);
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
    ObstacleData dataset;
    const vector<QPolygonF> mask;
};
class View{
  public :
    View(vector<RobotData>*, vector<ObstacleData>*);
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
  private :
    void productWindow();
};


/*
class Robot : public QGraphicsItem{
  public:
    Robot(ViewPort*);
    Robot(ViewPort*, RobotData);
    bool advance();
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    void initPos();
  protected:
    QVariant itemChange(GraphicsItemChange, const QVariant&);
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
  private:
    QPointF newPos;
    ViewPort *graph;
    RobotData dataset;
};*/
