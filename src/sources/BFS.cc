#include "MotionPlan.h"

BFS::BFS(){};
vector< list<QPointF> > BFS::path(QPointF* goal, QPointF* init, vector< vector<int> >* bitmap, vector< vector< vector<int> > >* cspace){
  bool success(false);
  vector< list<QPointF> > paths;
  vector< vector<int> > map;

  for(int i=0; i<254; ++i){
    list<QPointF> temp;
    paths.push_back(temp);
  }

  for(int i=0; i<128; ++i){
    vector<int> temp(127, 0);
    map.push_back(temp);
  }

  map[init->y()][init->x()] = 1;

  list<QPointF> temp;
  temp.push_front(*init);
  paths.push_back(temp);

  QPointF x = *init;
  vector<QPointF> neighbor;

  while(success && !empty()){
    for(vector<QPointF>::iterator i = neighbor.begin(); i!=neighbor.end(); ++i){
      QPointF xPlus = x+(*i);
      if(((*cspace)[0][xPlus.y()][xPlus.x()] != -1) && (xPlus.y()<127 && xPlus.x()>=0) &&!(map[xPlus.y()][xPlus.x()])){
        paths[(*bitmap)[xPlus.y()][xPlus.x()]].push_front(xPlus);
        map[xPlus.y()][xPlus.x()]=1;
      }
      if(xPlus.x()==init->x() && xPlus.y()==init->y()){
        success=true;
      }
    }
  }
  if(success){
    return paths;
  }else{
    paths.clear();
    return paths;
  }
}

bool BFS::empty(){
  return true;
}

void BFS::whoIsneighbor(vector<QPointF>* neighbor){
  QPointF n0(0,1);
  QPointF n1(1,1);
  QPointF n2(1,0);
  QPointF n3(-1,1);
  QPointF n4(-1,0);
  QPointF n5(-1,-1);
  QPointF n6(0,-1);
  QPointF n7(0,-1);
  neighbor->push_back(n0);
  neighbor->push_back(n1);
  neighbor->push_back(n2);
  neighbor->push_back(n3);
  neighbor->push_back(n4);
  neighbor->push_back(n5);
  neighbor->push_back(n6);
  neighbor->push_back(n7);
}
