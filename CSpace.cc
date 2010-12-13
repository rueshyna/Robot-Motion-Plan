#include "MotionPlan.h"

QPointF CSpace::edgeVector(QPointF* p1 , QPointF* p2, QPointF* center){
  qreal a(p2->y()-p1->y());
  qreal b(-(p2->x()-p1->x()));
  qreal c(p1->y()/(a*p1->x()+b));
  a = a*c;
  b = b*c;

  qreal x = (2.0*center->x()-2.0*a*b+2.0*a*center->y())/(2.0*(1.0+pow(a,2.0)));
  //cout <<x <<endl;
  return QPointF(x, a*x+b);
}

int CSpace::countAngle(double* sinAngle, double*cosAngle){
  double angle(0);
  if(*sinAngle >= 0 && *cosAngle >= 0){
    angle = *sinAngle;
  }else if(*sinAngle > 0 && *cosAngle < 0){
    angle = 180.0-*sinAngle;
  }else if(*sinAngle < 0 && *cosAngle > 0){
    angle = 360.0-*sinAngle;
  }else if(*sinAngle < 0 && *cosAngle < 0){
    angle = 360.0-*cosAngle;
  }

  return angle;
}

bool CSpace::sortF(const QPointF a,const QPointF b){
  double aSinAngle(asin(a.y()/sqrt(pow(a.x(),2.0)+pow(a.y(),2.0))));
  double aCosAngle(acos(a.x()/sqrt(pow(a.x(),2.0)+pow(a.y(),2.0))));
  double bSinAngle(asin(b.y()/sqrt(pow(b.x(),2.0)+pow(b.y(),2.0))));
  double bCosAngle(acos(b.x()/sqrt(pow(b.x(),2.0)+pow(b.y(),2.0))));

  return countAngle(&aSinAngle, &aCosAngle) < countAngle(&bSinAngle, &bCosAngle);
}

void CSpace::sortByAngle(vector<QPointF>* v){
  sort(v->begin(),v->end(),sortF);
}

QVector< QVector <QVector<int> > > CSpace::cObstacle(RobotData* robot, vector<ObstacleData>* obstacles){
   //for(size_t i = 0; i != 128; ++i){
    // QVector<int> temp1(0,128);
  //   QVector< QVector<int> > temp2(temp1,128);
  //   QVector< QVector <QVector<int> > > cspace(temp2, 360);
   //}

  vector<QPointF> robotVector;
  vector<QPointF> obstacleVector;

  for(QVector<QPolygonF>::iterator i = robot->polygons()->begin(); i != robot->polygons()->end(); ++i){
    qreal x(0);
    qreal y(0);

    for(QPolygonF::iterator j = i->begin(); j != i->end(); ++j){
      x += j->x();
      y += j->y();
    }

    QPointF center(x/i->size(),y/i->size());

    for(QPolygonF::iterator j = i->begin(); j != i->end(); ++j){
      QPointF now, next;
      if(j!=i->end()+1){
        now = *j;
        next = *(j+1);
      }else{
        now = *j;
        next = *i->begin();
      }
      robotVector.push_back(edgeVector(&now, &next,&center));
    }
    sortByAngle(&robotVector);

    for(vector<QPointF>::iterator k = robotVector.begin(); k != robotVector.end(); ++k){
     cout << k->x() <<" "<< k->y() <<endl;
    }
cout << "===============" <<endl;
    //for(vector<ObstacleData>::iterator i = obstacles.begin(); i != obstacles.end(); ++i){
   // 
   // }
   robotVector.clear();
  }
  cout << " end"<<endl;
};
