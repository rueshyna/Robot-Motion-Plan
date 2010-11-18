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
  for(int i = 0; i != bitmap.size(); ++i){
    for(int j = 0; j != bitmap.at(i).size(); ++j){
      if(bitmap.at(j).at(i) == -1){
        painter->setPen(QColor(255,255,255));
      }else{
        painter->setPen(QColor(bitmap.at(j).at(i),0,0));
      }
      painter->drawPoint(QPointF(j,i));
    }
  }
}
QRectF BitmapItem::boundingRect() const{
   return QRectF(0, 0, 400, 400);
}
