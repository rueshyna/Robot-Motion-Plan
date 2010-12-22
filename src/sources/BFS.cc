#include "MotionPlan.h"

BFS::BFS(){}
vector< PointAndAngle > BFS::path(QPointF* init, double initAngle,  QPointF* goal, double goalAngle, vector< vector<int> >* bitmap, vector< vector< vector<int> > >* cspace){
  bool success(false);
  vector< stack<PointAndAngle* > > open;
  vector< vector< vector<int> > > map;
  for(int i=0; i<256; ++i){
    stack<PointAndAngle*> temp;
    open.push_back(temp);
  }

  for(int i=0; i<360; ++i){
    vector< vector<int> > temp1;
    for(int i=0; i<128; ++i){
      vector<int> temp(127, 0);
      temp1.push_back(temp);
    }
    map.push_back(temp1);
  }

  map[static_cast<int>(initAngle)][init->y()][init->x()] = 1;

  PointAndAngle* x = new PointAndAngle(init->x(), init->y(), initAngle);
  open[(*cspace)[static_cast<int>(initAngle)][init->y()][init->x()]].push(x);
  TreeNode *tree = new TreeNode(x,0);

  vector<PointAndAngle> neighbor;
  whoIsneighbor(&neighbor);

  vector< TreeNode* > sibling;
  while(!success && !empty(&open)){
    PointAndAngle *x = first(&open);
    for(vector< TreeNode* >::iterator i = sibling.begin(); i!= sibling.end(); ++i){
      if(x == (**i).point()){
        tree = *i;
        sibling.clear();
        break;
      }
    }
    //cout << "x " << x->x() <<" " <<x->y()<<" "<<x->z()<<endl;
    //cout <<(*bitmap)[x->y()][x->x()]<<endl;
    for(vector<PointAndAngle>::iterator i = neighbor.begin(); i!=neighbor.end(); ++i){
   // cout <<"here1"<<endl;
      PointAndAngle *xPlus = new PointAndAngle(*x+*i);

      xPlus->setZ((xPlus->z() == 360)?0:xPlus->z());
      xPlus->setZ((xPlus->z() == -1)?359:xPlus->z());
      if((xPlus->x()<128 && xPlus->x()>=0) && (xPlus->y()<128 && xPlus->y()>=0) &&((*cspace)[xPlus->z()][xPlus->y()][xPlus->x()] != -1) && !(map[xPlus->z()][xPlus->y()][xPlus->x()])){
        sibling.push_back(new TreeNode(xPlus, tree));
    //    cout <<"open " <<(*bitmap)[xPlus->y()][xPlus->x()] <<" " << xPlus->x() <<" " <<xPlus->y() <<endl;
        open[(*bitmap)[xPlus->y()][xPlus->x()]].push(xPlus);
        map[xPlus->z()][xPlus->y()][xPlus->x()]=1;
      }
      if(xPlus->x()==goal->x() && xPlus->y()==goal->y() && xPlus->z() == goalAngle){
        success=true;
      }
    }
  }

  vector<PointAndAngle> findpath;

  PointAndAngle *end = new PointAndAngle(goal->x(), goal->y(), goalAngle);
  findpath.push_back(*end);
  while(!(tree->parent()==0)){
    findpath.push_back(*tree->point());
    tree = tree->parent();
  }
  findpath.push_back(*x);

//  for(vector<PointAndAngle>::iterator i = findpath.begin(); i!=findpath.end(); ++i){
//    cout << i->x() <<" " <<i->y() <<" "<<i->z() <<endl;
//    }
  if(!success){
    findpath.clear();
  }
  return findpath;
}

PointAndAngle* BFS::first(vector< stack<PointAndAngle*> >* _open){
  PointAndAngle *x;
  for(vector< stack<PointAndAngle*> >::iterator i = _open->begin(); i != _open->end(); ++i){
    if(!(i->empty())){
//  cout << "first1"<< (i->top())->x()<<endl;
      x = i->top();
      i->pop();
      break;
    }
  }
  return x;
}
bool BFS::empty(vector< stack<PointAndAngle*> >* _open){
  for(vector< stack<PointAndAngle*> >::iterator i = _open->begin(); i != _open->end(); ++i){
    if(!(i->empty())){
      return false;
    }
  }
  return true;
}

void BFS::whoIsneighbor(vector<PointAndAngle>* _neighbor){
  PointAndAngle n0(0,1,0);
  PointAndAngle n1(1,0,0);
  PointAndAngle n2(-1,0,0);
  PointAndAngle n3(0,-1,0);
  PointAndAngle n4(0,0,1);
  PointAndAngle n5(0,0,-1);
  _neighbor->push_back(n0);
  _neighbor->push_back(n1);
  _neighbor->push_back(n2);
  _neighbor->push_back(n3);
  _neighbor->push_back(n4);
  _neighbor->push_back(n5);
}

TreeNode::TreeNode(PointAndAngle* _point_):_point(_point_){}
TreeNode::TreeNode(PointAndAngle* _point_, TreeNode* _parent_):_point(_point_), _parent(_parent_){}
PointAndAngle* TreeNode::point(){return _point;}
TreeNode* TreeNode::parent(){return _parent;}
void TreeNode::setPoint(PointAndAngle* _point_){ _point = _point_;}
void TreeNode::setTreeNode(TreeNode* _parent_){ _parent = _parent_;}
