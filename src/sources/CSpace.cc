#include "MotionPlan.h"

VectorFrom CSpace::edgeVector(QPointF* p1 , QPointF* p2, QPointF* center, INPUT object){
  qreal a(p2->y()-p1->y());
  qreal b(p2->x()-p1->x());
  qreal c(p1->y()*b-p1->x()*a);
  qreal x(0);
  VectorFrom edge;
  if(b!=0){
    x = (2.0*center->x()-(2.0*a*c)/pow(b,2.0)+(2.0*a*center->y())/b)/(2.0*(1.0+pow(a/b,2.0)));
     edge = VectorFrom(x-center->x(), (a*x+c)/b-center->y());
  }else{
    x = p1->x();
    edge = VectorFrom(x-center->x(), 0);
  }
  if(object == ROBOT){
    edge.setX(0.0-edge.x());
    edge.setY(0.0-edge.y());
    return edge;
  }else if(object == OBSTACLE){
    return edge;
  }
}

double CSpace::countAngle(double* sinAngle, double*cosAngle){
  double angle(*sinAngle);
  if(*sinAngle >= 0){
    angle = *cosAngle;
  }else if(*sinAngle < 0 && *cosAngle >= 0 && *cosAngle <= 90){
    angle = 360.0+*sinAngle;
  }else if(*sinAngle < 0 && *cosAngle > 90 && *cosAngle <= 180){
    angle = 180.0-*sinAngle;
  }
  return angle;
}

bool CSpace::sortF(VectorFrom a,VectorFrom b){
  return a.angle() < b.angle();
}

void CSpace::sortByAngle(vector<VectorFrom>* v){
  sort(v->begin(),v->end(),sortF);
}

void CSpace::findVector(vector<VectorFrom>* v, QPolygonF* p, INPUT object){
  qreal x(0);
  qreal y(0);

  for(QPolygonF::iterator i = p->begin(); i != p->end(); ++i){
    x += i->x();
    y += i->y();
  }
  QPointF centerR(x/p->size(),y/p->size());

  int countFrom(0);
  for(QPolygonF::iterator i = p->begin(); i != p->end(); ++i){
    QPointF now, next;
    if(i==p->end()-1){
      now = *i;
      next = *p->begin();
    }else{
      now = *i;
      next = *(i+1);
    }
    VectorFrom vectorFrom;

    if(object == ROBOT){
      vectorFrom = edgeVector(&now, &next,&centerR, ROBOT);
    }else if(object == OBSTACLE){
      vectorFrom = edgeVector(&now, &next,&centerR, OBSTACLE);
    }

    double sinAngle((asin(vectorFrom.y()/sqrt(pow(vectorFrom.x(),2.0)+pow(vectorFrom.y(),2.0))))*180.0/M_PI);
    double cosAngle((acos(vectorFrom.x()/sqrt(pow(vectorFrom.x(),2.0)+pow(vectorFrom.y(),2.0))))*180.0/M_PI);
    vectorFrom.setAngle(countAngle(&sinAngle, &cosAngle));
    vectorFrom.setFrom(countFrom++);
    vectorFrom.setInput(object);
    v->push_back(vectorFrom);
  }
}

int CSpace::delta(double angle1, double angle2){
  int temp = angle1-angle2;
  temp = (temp <= 180)? temp: 360-temp;
  temp = (temp > 0)? temp : 0-temp;
  return temp;
}

bool CSpace::checkPreIndex(double obsAngle, double preAngle, vector<VectorFrom>* _obsVec){
  int count(0);
  bool over360(abs(obsAngle-preAngle)>180);
  for(vector<VectorFrom>::iterator i = _obsVec->begin(); i!=_obsVec->end(); ++i){
    if(!over360 && i->angle()>=preAngle && i->angle()<obsAngle){
      ++count;
    }
    if(over360 && i->angle()<=preAngle && i->angle()>obsAngle){
      ++count;
    }
  }
  if(over360){count = _obsVec->size()-count-1;}

  return (count < 1);
}
bool CSpace::checkNextIndex(double obsAngle, double nextAngle, vector<VectorFrom>* _obsVec){
  int count(0);
  bool over360(abs(obsAngle-nextAngle)>180);
  for(vector<VectorFrom>::iterator i = _obsVec->begin(); i!=_obsVec->end(); ++i){
    if(!over360 && i->angle()<=nextAngle && i->angle()>obsAngle){
      ++count;
    }
    if(over360 && i->angle()>=nextAngle && i->angle()<obsAngle){
      ++count;
    }
  }
  if(over360){count = _obsVec->size()-count-1;}
    return (count<2);
}
vector< vector < vector<int> > > CSpace::cObstacle(RobotData* robot, vector<ObstacleData>* obstacles){
  vector< vector <vector<int> > > cspace;
  for(size_t h = 0; h< 360; ++h){

    vector< vector<int> > temp2;
    for(int i = 0; i != 128; ++i){
      vector<int> temp1(128, 0);
      temp2.push_back(temp1);
    }

    QTransform rMatrix;
    rMatrix = rMatrix.rotate(h);

    //each polygons of robot
    for(QVector<QPolygonF>::iterator i = robot->polygons()->begin(); i != robot->polygons()->end(); ++i){
      vector<VectorFrom> robotVector;
      QPolygonF rPolygon;

      for(QPolygonF::iterator j=i->begin(); j!=i->end(); ++j){
        rPolygon << rMatrix.map(*j);
        QPointF rr = rMatrix.map(*j);
      }

      findVector(&robotVector, &rPolygon, ROBOT);
      sortByAngle(&robotVector);

      //each obstacle
      for(vector<ObstacleData>::iterator j = obstacles->begin(); j != obstacles->end(); ++j){
        vector<VectorFrom> obstacleVector;

        //each polygons
        for(QVector<QPolygonF>::iterator k = j->polygons()->begin(); k!=j->polygons()->end(); ++k){
          QPolygonF oPolygon;
          QTransform oMatrix;
          oMatrix = oMatrix.rotate(j->initAngle());
          for(QPolygonF::iterator l=k->begin(); l!=k->end(); ++l){
            oPolygon << oMatrix.map(*l);
          }

          findVector(&obstacleVector, &oPolygon, OBSTACLE);
          sortByAngle(&obstacleVector);

          QPolygonF newPolygon;
          int edgeCount(0);
          int totalEdge(obstacleVector.size()+robotVector.size());
            for(int l = 0; l!=obstacleVector.size(); ++l){
            if(edgeCount == obstacleVector.size()+robotVector.size()){break;}
              vector<VectorFrom> temp = robotVector;
              temp.push_back(obstacleVector.at(l));
              sortByAngle(&temp);

              int preIndex;
              int nextIndex;
              for(int m = 0; m <temp.size(); ++m){
                if(temp.at(m).Input() == OBSTACLE){
                  preIndex = ((m-1)==-1)?temp.size()-1:m-1;
                  nextIndex = ((m+1)==temp.size())?0:m+1;

                  if(temp[m].angle()-temp[preIndex].angle()==0 && temp[m].angle()-temp[nextIndex].angle()!=0){
                    nextIndex = ((nextIndex+1)==temp.size())?0:nextIndex+1;
                  }
                  if(temp[m].angle()-temp[nextIndex].angle()==0 &&temp[m].angle()-temp[preIndex].angle()!=0){
                    preIndex = ((preIndex-1)==-1)?temp.size()-1:preIndex-1;
                  }

                  QPointF p;
                  double preCount = delta(temp[m].angle(),temp[preIndex].angle());
                  double nextCount = delta(temp[m].angle(),temp[nextIndex].angle());
                  if((temp[preIndex].angle()<temp[nextIndex].angle() || (temp[preIndex].angle()-temp[nextIndex].angle())>=180) && (nextCount > preCount || totalEdge-edgeCount >= 2)){
                    if(checkPreIndex(temp[m].angle(),temp[preIndex].angle(), &obstacleVector)){
                      p = oPolygon.at(temp[m].from())- rPolygon.at(temp[preIndex].from());
                      newPolygon << QPointF(p.x(),p.y());
                      ++edgeCount;
                      if(edgeCount == totalEdge){
                        break;
                      }
                    }
                    if(checkNextIndex(temp[m].angle(),temp[nextIndex].angle(), &obstacleVector)){
                      p = oPolygon.at(temp[m].from())- rPolygon.at(temp[nextIndex].from());
                      newPolygon << QPointF(p.x(),p.y());
                      ++edgeCount;
                      if(edgeCount == totalEdge){
                        break;
                      }
                    }
                  }else{
                    if(checkNextIndex(temp[m].angle(),temp[nextIndex].angle(), &obstacleVector)){
                      p = oPolygon.at(temp[m].from())- rPolygon.at(temp[nextIndex].from());
                      newPolygon << QPointF(p.x(),p.y());
                      ++edgeCount;
                      if(edgeCount == totalEdge){
                        break;
                      }
                    }
                    if(checkPreIndex(temp[m].angle(),temp[preIndex].angle(), &obstacleVector)){
                      p = oPolygon.at(temp[m].from())- rPolygon.at(temp[preIndex].from());
                      newPolygon << QPointF(p.x(),p.y());
                      ++edgeCount;
                      if(edgeCount == totalEdge){
                        break;
                      }
                      break;
                    }
                  }
                }
              }
          }
          Bitmap::setObstacle(&temp2, &newPolygon, 0, j->initPos());
          obstacleVector.clear();
        }
      }
      robotVector.clear();
    }
    cspace.push_back(temp2);
  }
  return cspace;
}

VectorFrom::VectorFrom(){}
VectorFrom::VectorFrom(double _x, double _y):QPointF(_x,_y){}
VectorFrom::VectorFrom(double _x, double _y, int _from_): _from(_from_), QPointF(_x,_y){}
int VectorFrom::from(){return _from;}
void VectorFrom::setFrom(int _from_){_from = _from_;}
double VectorFrom::angle(){return _angle;}
void VectorFrom::setAngle(double _angle_){_angle = _angle_;}
INPUT VectorFrom::Input(){return _input;}
void VectorFrom::setInput(INPUT _input_){_input = _input_;}
