#ifndef VIEW_H
#define VIEW_H
#include "MotionPlan.h"

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
    void showPf();
    void prePf();
    void nextPf();
  private :
    int viewPf;
    vector<RobotData>* robots;
    vector<ObstacleData>* obstacles;
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
    void setBitmap(vector< vector<int> > _bitmap);
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
#endif
