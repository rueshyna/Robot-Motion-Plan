#include "MotionPlan.h"

Smooth::Smooth(){}
bool Smooth::checkPath(vector< vector < vector<int> > >* cspace, vector< PointAndAngle >* path, vector< PointAndAngle >* oPath, int  begin, int last){
  PointAndAngle delta = oPath->at(begin)-oPath->at(last);
  double d = max(abs(delta.x()), abs(delta.y()));
  d = max(abs(delta.z()), d);
  delta.setX(delta.x()/d);
  delta.setY(delta.y()/d);
  delta.setZ(delta.z()/d);


  for(int i=0; i!=static_cast<int>(d+1); ++i){
    PointAndAngle p = oPath->at(begin)-(delta*i);
    p.setZ((p.z()>360)?p.z()-360:p.z());
    p.setZ((p.z()<0)?360+p.z():p.z());
    p.setY((p.y()>=128)?127:p.y());
    p.setY((p.y()<0)?0:p.y());
    p.setX((p.x()>=128)?127:p.x());
    p.setX((p.x()<0)?0:p.x());
    if((*cspace)[(int)(p.z())][(int)(p.y())][(int)(p.x())] == -1){
      return false;
    }
  }

  for(int i=0; i!=static_cast<int>(d+1); ++i){
    PointAndAngle p = oPath->at(begin)-(delta*i);
    path->push_back(p);
  }
  return true;
}

void Smooth::smooth(vector< vector < vector<int> > >* cspace, vector< PointAndAngle >* path, vector< PointAndAngle >* p, int begin, int last){
  if(!(last-begin) || checkPath(cspace, path, p, begin, last)){
    return;
  }
  smooth(cspace, path, p, begin, begin+(last-begin)/2);
  smooth(cspace, path, p, begin+((last-begin)/2)+1, last);
}
