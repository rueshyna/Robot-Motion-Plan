#include "MotionPlan.h"

Smooth::Smooth(){}
bool Smooth::checkPath(vector< vector < vector<int> > >* cspace, vector< PointAndAngle >* path, vector< PointAndAngle >::iterator begin, int size){

  PointAndAngle delta = *begin-*(begin+size-1);
  double d = max(abs(delta.x()), abs(delta.y()));
  d = max(abs(delta.z()), d);
  delta.setX(delta.x()/d);
  delta.setY(delta.y()/d);
  delta.setZ(delta.z()/d);


  for(int i=0; i!=d+1; ++i){
    PointAndAngle p = (*begin)-(delta*i);
    p.setZ((p.z()>=360)?360-p.z():p.z());
    if((*cspace)[(int)(p.z())][(int)(p.y())][(int)(p.x())] == -1){
      path->push_back(*begin);
      return false;
    }
  }

  for(int i=0; i!=d+1; ++i){
    PointAndAngle p = (*begin)-(delta*i);
    path->push_back(p);
  }
  return true;
}

void Smooth::smooth(vector< vector < vector<int> > >* cspace, vector< PointAndAngle >* path, vector< PointAndAngle >::iterator begin, int size){
  if(!checkPath(cspace, path, begin, size)){
    smooth(cspace, path, begin, size/2);
    begin += size/2;
    smooth(cspace, path, begin, size);
  }
}
