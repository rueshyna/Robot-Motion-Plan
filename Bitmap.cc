#include "MotionPlan.h"
#include <algorithm>
#include <cstdlib>
#include <map>

using std::max;
using std::abs;

Bitmap:: Bitmap(){
  for(int i = 0; i != 128; ++i){
    vector<int> i(128, M);
    _bitmap.push_back(i);
  }
}

void Bitmap::setObstacles(vector<ObstacleData>* obs){
  for(vector<ObstacleData>::iterator i = obs->begin(); i != obs->end(); ++i){
    for(QVector<QPolygonF>::iterator j = i->polygons()->begin(); j!= i->polygons()->end(); ++j){
      int xMin(127);
      int xMax(0);
      vector<int> yMin(128,127);
      vector<int> yMax(128,0);

      for(QPolygonF::iterator k = j->begin(); k != j->end(); ++k){

        QTransform matrix;
        matrix = matrix.rotate(i->initAngle());

        QPointF p1;
        QPointF p2;

        if( k != (j->end()-1)){
          p1 = matrix.map(*k)+ *i->initPos();
          p2 = matrix.map(*(k+1))+ *i->initPos();
        } else {
          p1 = matrix.map(*k)+ *i->initPos();
          p2 = matrix.map(*j->begin())+ *i->initPos();
        }

        if(p1.x() < xMin){
          xMin = p1.x();
        }
        if(p1.x() > xMax){
          xMax = p1.x();
        }
        double dx(p1.x() - p2.x());
        double dy(p1.y() - p2.y());
        double d(max(abs(dx), abs(dy)));
        int _d(static_cast<int>(d));

        for(int l=0; l != _d; ++l){
          int _x = (p1.x())-(dx/d)*l;
          int _y = (p1.y())-(dy/d)*l;
          _bitmap[_y][_x] = -1;

          if(_y < (yMin[_x])){
            yMin[_x] = _y;
          }

          if(_y > (yMax[_x])){
            yMax[_x] = _y;
          }
        }
      }
      for(int i = xMin; i != xMax; ++i){
        for(int j = yMax[i] - yMin[i]; j!= 0 ; --j ){
          _bitmap[yMax[i]-j][i] = -1;
        }
      }
    }
  }
}

vector< vector<int> > Bitmap::NF1(QPointF* goal){
  vector< vector<int> > bitmap;
  QPoint increX(1.0,0.0);
  QPoint increY(0.0,1.0);
  QPoint decreX(-1.0,0.0);
  QPoint decreY(0.0,-1.0);
  bitmap= _bitmap;
  QVector< QVector<QPointF> > list;

  for(int i = 0; i != 128; ++i){
    for(int j = 0; j != 128; ++j){
      if(bitmap[j][i] != -1){
        bitmap[j][i] = M;
      }
    }
  }

  bitmap[goal->y()][goal->x()] = 0;

  QVector<QPointF> v;
  v.push_back(QPoint(goal->x(), goal->y()));
  list.push_back(v);

  for(int i=0; i!=list.size(); ++i){
    QVector<QPointF> vec;
    for(int j=0; j!=list.at(i).size(); ++j){
      QPointF neig1 = list.at(i).at(j)+increX;
      if(neig1.x()<128 && neig1.y()<128 && neig1.x()> -1 && neig1.y()>-1&& 
         bitmap[neig1.y()][neig1.x()] == M){
        bitmap[neig1.y()][neig1.x()] = i+1;
        vec.push_back(neig1);
      }
      QPointF neig2 = list.at(i).at(j)+increY;
      if(neig2.x()<128 && neig2.y()<128 &&  neig2.x()> -1 && neig2.y()>-1&&
         bitmap[neig2.y()][neig2.x()] == M){
        bitmap[neig2.y()][neig2.x()] = i+1;
        vec.push_back(neig2);
      }
      QPointF neig3 = list.at(i).at(j)+decreX;
      if(neig3.x()<128 && neig3.y()<128 &&  neig3.x()> -1 && neig3.y()>-1&&
         bitmap[neig3.y()][neig3.x()] == M){
        bitmap[neig3.y()][neig3.x()] = i+1;
        vec.push_back(neig3);
      }
      QPointF neig4 = list.at(i).at(j)+decreY;
      if(neig4.x()<128 && neig4.y()<128 && neig4.x()> -1 && neig4.y()>-1&&
         bitmap[neig4.y()][neig4.x()] == M){
        bitmap[neig4.y()][neig4.x()] = i+1;
        vec.push_back(neig4);
      }
    }
    if(!vec.empty()){
      list.push_back(vec);
    }
  }
  return bitmap;
}
