#include "MotionPlan.h"

BitmapItem::BitmapItem(){}
BitmapItem::BitmapItem(vector< vector<int> > _bitmap_):_bitmap(_bitmap_){
  setScale(PF_SCALE);
  //setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}

vector< vector<int> >* BitmapItem::bitmap(){return &_bitmap;}

void BitmapItem::setBitmap(vector< vector<int> >* _bitmap_){
  _bitmap = *_bitmap_;
  update();
}
void BitmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
  QTransform matrix;
  matrix = matrix.rotate(-90);

  int countX(0);
  int countY(0);

  for(vector< vector<int> >::iterator i = _bitmap.begin(); i != _bitmap.end(); ++i){
    for(vector<int>::iterator j = i->begin(); j != i->end(); ++j){
      if(*j == -1){
        painter->setBrush(QColor(0,0,0));
        painter->setPen(QColor(0,0,0));
      }else{
        painter->setBrush(QColor(255-*j,0,120));
        painter->setPen(QColor(255-*j,0,120));
      }
      QPointF *newPos = &matrix.map(QPointF(countX,countY));
      ++countY;
      double rectScale = 1;
      painter->drawRect(newPos->x()*rectScale, newPos->y()*rectScale-rectScale, rectScale, rectScale);
    }
    countY=0;
    ++countX;
  }
}

QRectF BitmapItem::boundingRect() const{
   return QRectF(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
}
