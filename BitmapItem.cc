#include "MotionPlan.h"

BitmapItem::BitmapItem(PFwindow* graphView){}
BitmapItem::BitmapItem(PFwindow* graphView, vector< vector<int> > _bitmap):bitmap(_bitmap){
  setScale(2);
  setCacheMode(DeviceCoordinateCache);
  setZValue(-1);
}
void BitmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*){
    /*  cout <<"map: " <<endl;
      for(int k=0; k!=128; ++k){
        for(int l=0; l!=128; ++l){
          cout << bitmap.at(l).at(k) << " ";
        }
        cout <<endl;
      }*/
  QTransform matrix;
  matrix = matrix.rotate(-90);

  for(int i = 0; i != bitmap.size(); ++i){
    for(int j = 0; j != bitmap.at(i).size(); ++j){
      if(bitmap.at(j).at(i) == -1){
        painter->setBrush(QColor(0,0,0));
        painter->setPen(QColor(0,0,0));
      }else{
        painter->setBrush(QColor(255-bitmap.at(j).at(i),0,120));
        painter->setPen(QColor(255-bitmap.at(j).at(i),0,120));
      }
      QPointF newPos = matrix.map(QPointF(j,i));
      double rectScale = 1;
      painter->drawRect(newPos.x()*rectScale,newPos.y()*rectScale,rectScale,rectScale);
    }
  }
}
QRectF BitmapItem::boundingRect() const{
   return QRectF(0, -PF_HIGHT, PF_WIDTH, PF_HIGHT);
}
