#ifndef VIEW_H
#define VIEW_H
#include "MotionPlan.h"

class PainterWidget : public QGraphicsView{
  Q_OBJECT
  public :
    PainterWidget(QGraphicsScene*);
  protected :
    void keyPressEvent(QKeyEvent*);
    void scaleView(qreal);
};
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
    void animation();
    void reset();
    void smooth();
    void showPf();
    void prePf();
    void nextPf();
    void showPath();
  private :
    int viewPf;
    vector<PathItem*>* pathItemPool;
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
    vector<ObjectItem*>* robotInits;
    PainterWidget* mainWidget;
    PainterWidget* pfWidget;
    QGraphicsScene* mainScene;
    QGraphicsScene* pfScene;
    void productWindow();
    QPushButton *_setButton;
    QPushButton *_resetButton;
    QPushButton *_showPathButton;
    QPushButton *_animationButton;
    QPushButton *_smoothButton;
    QPushButton *_prePfButton;
    QPushButton *_nextPfButton;
    vector< vector <vector<int> > > *_cspace;
};
class BitmapItem : public QGraphicsItem{
  public :
    BitmapItem();
    BitmapItem(vector< vector<int> >);
    QRectF boundingRect() const;
    vector< vector<int> >* bitmap();
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
    void setBitmap(vector< vector<int> >*);
  private :
    vector< vector<int> > _bitmap;
};
class PathItem : public QGraphicsItem{
  public :
    PathItem(QVector<QPolygonF>*, PointAndAngle*);
    QPainterPath shape() const;
    QRectF boundingRect() const;
    void initPos();
    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*);
  private :
    QVector<QPolygonF>* _poly;
    PointAndAngle* _point;
};
class ObjectItem : public QGraphicsItem{
  public:
    ObjectItem(ObjectData*, ROBOT_POS);
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
    ObjectData* dataset;
    const QVector<QPolygonF> mask;
    ROBOT_POS robot_pos;
};

#endif
