#include "MotionPlan.h"
#include <cstdlib>

using std::max;
using std::abs;

Bitmap:: Bitmap(){
}

void Bitmap::setObstacle(vector< vector<int> >* _bitmap, QPolygonF* polygon, double angle, QPointF* pos){
  int xMin(127);
  int xMax(0);
  vector<int> yMin(128,127);
  vector<int> yMax(128,0);

  for(QPolygonF::iterator k = polygon->begin(); k != polygon->end(); ++k){

    QTransform matrix;
    matrix = matrix.rotate(angle);

    QPointF p1;
    QPointF p2;

    if( k != (polygon->end()-1)){
      p1 = matrix.map(*k)+ *pos;
      p2 = matrix.map(*(k+1))+ *pos;
    } else {
      p1 = matrix.map(*k)+ *pos;
      p2 = matrix.map(*polygon->begin())+ *pos;
    }

    if(p1.x() > 127){
      p1.setX(127);
    }
    if(p1.y() > 127){
      p1.setY(127);
    }
    if(p1.x() < 0){
      p1.setX(0);
    }
    if(p2.y() < 0){
      p2.setY(0);
    }
    if(p2.x() > 127){
      p2.setX(127);
    }
    if(p2.y() > 127){
      p2.setY(127);
    }
    if(p2.x() < 0){
      p2.setX(0);
    }
    if(p2.y() < 0){
      p2.setY(0);
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
    int _d(static_cast<int>(d+0.9));

    for(int l=0; l != _d; ++l){
      int _x = (p1.x())-(dx/d)*l;
      int _y = (p1.y())-(dy/d)*l;

      if(_x > 127){
        _x=127;
      }
      if( _y > 127){
        _y=127;
      }
      if(_x < 0) {
        _x=0;
      }
      if(_y < 0){
        _y=0;
      }
      (*_bitmap)[_y][_x] = -1;
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
        (*_bitmap)[yMax[i]-j][i] = -1;
    }
  }
}

vector< vector< int > > Bitmap::setObstacles(vector<ObstacleData>* obs){
  vector< vector<int> > _bitmap;
  for(int i = 0; i != 128; ++i){
    vector<int> i(128, M);
    _bitmap.push_back(i);
  }
  for(vector<ObstacleData>::iterator i = obs->begin(); i != obs->end(); ++i){
    for(QVector<QPolygonF>::iterator j = i->polygons()->begin(); j!= i->polygons()->end(); ++j){
      setObstacle(&_bitmap, &*j, i->initAngle(), i->initPos());
    }
  }
  return _bitmap;
}

vector< vector<int> > Bitmap::NF1(QPointF* goal, vector< vector<int> >* bitmap){
  QPoint increX(1.0,0.0);
  QPoint increY(0.0,1.0);
  QPoint decreX(-1.0,0.0);
  QPoint decreY(0.0,-1.0);
  QVector< QVector<QPointF> > list;

  for(int i = 0; i != 128; ++i){
    for(int j = 0; j != 128; ++j){
      if((*bitmap)[j][i] != -1){
        (*bitmap)[j][i] = M;
      }
    }
  }

  (*bitmap)[goal->y()][goal->x()] = 0;

  QVector<QPointF> v;
  v.push_back(QPoint(goal->x(), goal->y()));
  list.push_back(v);

  for(int i=0; i!=list.size(); ++i){
    QVector<QPointF> vec;
    for(int j=0; j!=list.at(i).size(); ++j){
      QPointF neig1 = list.at(i).at(j)+increX;
      if(neig1.x()<128 && neig1.y()<128 && neig1.x()> -1 && neig1.y()>-1&& 
         (*bitmap)[neig1.y()][neig1.x()] == M){
        (*bitmap)[neig1.y()][neig1.x()] = i+1;
        vec.push_back(neig1);
      }
      QPointF neig2 = list.at(i).at(j)+increY;
      if(neig2.x()<128 && neig2.y()<128 &&  neig2.x()> -1 && neig2.y()>-1&&
         (*bitmap)[neig2.y()][neig2.x()] == M){
        (*bitmap)[neig2.y()][neig2.x()] = i+1;
        vec.push_back(neig2);
      }
      QPointF neig3 = list.at(i).at(j)+decreX;
      if(neig3.x()<128 && neig3.y()<128 &&  neig3.x()> -1 && neig3.y()>-1&&
         (*bitmap)[neig3.y()][neig3.x()] == M){
        (*bitmap)[neig3.y()][neig3.x()] = i+1;
        vec.push_back(neig3);
      }
      QPointF neig4 = list.at(i).at(j)+decreY;
      if(neig4.x()<128 && neig4.y()<128 && neig4.x()> -1 && neig4.y()>-1&&
         (*bitmap)[neig4.y()][neig4.x()] == M){
        (*bitmap)[neig4.y()][neig4.x()] = i+1;
        vec.push_back(neig4);
      }
    }
    if(!vec.empty()){
      list.push_back(vec);
    }
  }
  return *bitmap;
}
