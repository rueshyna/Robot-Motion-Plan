#include "MotionPlan.h"

VectorFrom CSpace::edgeVector(QPointF* p1 , QPointF* p2, QPointF* center, INPUT object){
  qreal a(p2->y()-p1->y());
  qreal b(-(p2->x()-p1->x()));
  qreal c(p1->y()*b-p1->x()*a);
  qreal x(0);
  VectorFrom edge;
  if(b!=0){
    x = (2.0*center->x()-(2.0*a*c)/pow(b,2.0)+(2.0*a*center->y())/b)/2.0*(1.0+a/b);
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
  double angle(*cosAngle);
  if(*sinAngle < 0){
    angle = 360.0-*cosAngle;
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
      vectorFrom = edgeVector(&now, &next,&centerR, ROBOT);
    }

    double sinAngle((asin(vectorFrom.y()/sqrt(pow(vectorFrom.x(),2.0)+pow(vectorFrom.y(),2.0))))*180.0/M_PI);
    double cosAngle((acos(vectorFrom.x()/sqrt(pow(vectorFrom.x(),2.0)+pow(vectorFrom.y(),2.0))))*180.0/M_PI);

    vectorFrom.setAngle(countAngle(&sinAngle, &cosAngle));
    vectorFrom.setFrom(countFrom++);
    v->push_back(vectorFrom);
  }
  countFrom = 0;
}

QVector< QVector <QVector<int> > > CSpace::cObstacle(RobotData* robot, vector<ObstacleData>* obstacles){
   //for(size_t i = 0; i != 128; ++i){
//     QVector<int> temp1(0,128);
//     QVector< QVector<int> > temp2(temp1,128);
//     QVector< QVector <QVector<int> > > cspace(temp2, 360);
  // }
  //each polygons of robot
  for(QVector<QPolygonF>::iterator i = robot->polygons()->begin(); i != robot->polygons()->end(); ++i){
    vector<VectorFrom> robotVector;

    findVector(&robotVector, &*i, ROBOT);
    sortByAngle(&robotVector);

    //each obstacle
    for(vector<ObstacleData>::iterator j = obstacles->begin(); j != obstacles->end(); ++j){
      vector<VectorFrom> obstacleVector;
      //each polygons
      for(QVector<QPolygonF>::iterator k = j->polygons()->begin(); k!=j->polygons()->end(); ++k){
        findVector(&obstacleVector, &*k, OBSTACLE);
        sortByAngle(&obstacleVector);
        vector<VectorFrom>::iterator start;
        
        double b(500);
        //find the min angle betreen vector of obastacle and vector  of robot
        for(vector<VectorFrom>::iterator k = obstacleVector.begin(); k!=obstacleVector.end()-1; ++k){
          double a(abs(robotVector.at(0).angle()-k->angle()));
          if(a <= b){
            start = k;
            b = abs(robotVector.at(0).angle()-(k)->angle());
          }
        }

        for(vector<VectorFrom>::iterator k = start; k!=obstacleVector.end(); ++k){
        }
        cout <<"=============" <<endl;
        obstacleVector.clear();
      }


    }
    robotVector.clear();
  }
  QVector< QVector <QVector<int> > > a;
  return a;
}

VectorFrom::VectorFrom(){}
VectorFrom::VectorFrom(double _x, double _y):QPointF(_x,_y){}
VectorFrom::VectorFrom(double _x, double _y, int _from_): _from(_from_), QPointF(_x,_y){}
int VectorFrom::from(){return _from;}
void VectorFrom::setFrom(int _from_){_from = _from_;}
double VectorFrom::angle(){return _angle;}
void VectorFrom::setAngle(double _angle_){_angle = _angle_;}
