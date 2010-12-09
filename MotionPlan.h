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
#define PF_SCALE 3
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
class BitmapItem;
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


//Controller
class Bitmap{
  public :
    Bitmap();
    vector< vector<int> > setObstacles(vector<ObstacleData>*);
    vector< vector<int> > NF1(QPointF*, vector< vector<int> >*);
};

/* View */

class Window : public QObject{
  Q_OBJECT
  public :
    Window(vector<RobotData>*, vector<ObstacleData>*);
    QPushButton* setButton();
    QPushButton* resetButton();
    QPushButton* showPathButton();
    QPushButton* animationButton();
    QPushButton* smoothButton();
    QPushButton* prePfButton();
    QPushButton* nextPfButton();
  public slots:
    void showPF();
  private :
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
    void productWindow();
    QPushButton *_setButton;
    QPushButton *_resetButton;
    QPushButton *_showPathButton;
    QPushButton *_animationButton;
    QPushButton *_smoothButton;
    QPushButton *_prePfButton;
    QPushButton *_nextPfButton;
};

class PainterWidget : public QGraphicsView{
  Q_OBJECT
  public :
    PainterWidget(QGraphicsScene*);
  protected :
    void keyPressEvent(QKeyEvent*);
    void scaleView(qreal);
};

class BitmapItem : public QGraphicsItem{
  public :
    BitmapItem();
    BitmapItem(vector< vector<int> >);
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
