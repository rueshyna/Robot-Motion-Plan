#include "MotionPlan.h"
#include <algorithm>
#include <cstdlib>
#include <map>

using std::max;
using std::abs;

Bitmap:: Bitmap(){
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
          _bitmap[_x][_y] = 1;

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
          _bitmap[i][yMax[i]-j] = 1;
        }
      }
    }
  }
}
