#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QtGui>
#include <vector>
#include <cstring>
#include <string>

#define SCREEN_WIDTH 128*SCALE
#define SCREEN_HIGHT 128*SCALE
#define SCALE 3
#define PF_WIDTH 128*PF_SCALE
#define PF_HIGHT 128*PF_SCALE
#define PF_SCALE 2
#define M 255

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


//Controller
class Bitmap{
  public :
    Bitmap();
    void setObstacles(vector<ObstacleData>*);
    vector< vector<int> > NF1(QPointF*);
  private :
    vector< vector<int> > _bitmap;
};

/* View */

class PFwindow : public QGraphicsView{
  public :
    PFwindow(QGraphicsScene*);
  protected :
    void keyPressEvent(QKeyEvent*);
    void scaleView(qreal);
};

class Window : public QObject{
  Q_OBJECT
  public :
    Window(vector<RobotData>*, vector<ObstacleData>*);
    QPushButton* PFbutton();
  public slots:
    void showPF();
  private :
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
    void productWindow();
    QPushButton *_PFbutton;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
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
class BitmapItem : public QGraphicsItem{
  public :
    BitmapItem(PFwindow*);
    BitmapItem(PFwindow*, vector< vector<int> >);
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
  private :
    vector< vector<int> > bitmap;
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
