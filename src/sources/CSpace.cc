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
  //        for(int d=0; d<obstacleVector.size(); ++d){
  //          cout << "o "<< obstacleVector[d].from()<<endl;
  //        }

          //vector<VectorFrom>::iterator start;
          int start(-1);
          QPolygonF newPolygon;
          double b(500);
          //find the min angle betreen vector of obastacle and vector  of robot
          //for(vector<VectorFrom>::iterator l = robotVector.begin(); l!=robotVector.end()-1; ++l){
          for(int l = 0; l!=robotVector.size()-1; ++l){
           // double a(abs(obstacleVector.at(0).angle()-l->angle()));
            double a(abs(obstacleVector.at(0).angle()-obstacleVector[l].angle()));
            if(a <= b){
              start = l;
              //b = abs(obstacleVector.at(0).angle()-l->angle());
              b = abs(obstacleVector.at(0).angle()-(robotVector)[l].angle());
            }
          }
  //        vector<VectorFrom>::iterator temp;
          //if(start == robotVector.begin()  ){
          //  start =robotVector.end()-1;
          //}else{
          //  start= start-1;
         // }
//          if(abs(obstacleVector.at(0).angle()-(start+1)->angle())<=abs(obstacleVector.at(0).angle()-temp->angle())){
        //   start=temp;
        //  }
//          QPointF p = oPolygon.at(obstacleVector.at(obstacleVector.size()-1).from())- rPolygon.at(robotVector.at(start).from());
  //                newPolygon << p;

          int count(1);
          int edgeCount(0);
//          for(vector<VectorFrom>::iterator l = obstacleVector.begin(); l!=obstacleVector.end(); ++l){
            for(int l = 0; l!=obstacleVector.size(); ++l){
             if(edgeCount < obstacleVector.size()+robotVector.size()){
              vector<VectorFrom> temp = robotVector;
              temp.push_back(obstacleVector.at(l));
              sortByAngle(&temp);
              int preIndex;
              int nextIndex;
              for(int m = 0; m <temp.size(); ++m){
                if(temp.at(m).Input() == OBSTACLE){
                  preIndex = ((m-1)==-1)?temp.size()-1:m-1;
                  nextIndex = ((m+1)==temp.size())?0:m+1;

                  if(abs(temp[m].angle()-temp[preIndex].angle())<abs(temp[m].angle()-temp[nextIndex].angle())){
                    QPointF p = oPolygon.at(temp[m].from())- rPolygon.at(temp[preIndex].from());
                    newPolygon << p;

                     p = oPolygon.at(temp[m].from())- rPolygon.at(temp[nextIndex].from());
                    newPolygon << p;
                    edgeCount++;
                    break;
                  }else{
                    QPointF p = oPolygon.at(temp[m].from())- rPolygon.at(temp[nextIndex].from());
                    newPolygon << p;
                     p = oPolygon.at(temp[m].from())- rPolygon.at(temp[preIndex].from());
                    newPolygon << p;
                    edgeCount++;
                    break;
                  }
                }
              }
              }else{break;}
  //          for(vector<VectorFrom>::iterator m = start; m!=robotVector.end(); (m == (robotVector.end()-1))?m=robotVector.begin():++m){
  /*
            for(int m = start; m!=robotVector.size(); (m == (robotVector.size()-1))?m=0:++m){
              if(count < 2){
                if(edgeCount < obstacleVector.size()+robotVector.size()){

//                  QPointF p = oPolygon.at(l->from())- rPolygon.at(m->from());
                  QPointF p = oPolygon.at(obstacleVector[l].from())- rPolygon.at(robotVector[m].from());
//                  cout<<"o " <<oPolygon.at(obstacleVector[l].from()).x() <<" "<<oPolygon.at(obstacleVector[l].from()).y()<<endl;
  //                cout <<"p " <<p.x() <<" " <<p.y()<<endl;
  cout<< l<<" " <<m<<endl;
                  newPolygon << p;

                  //if(m == (robotVector.end()-1)){
                  //  m=robotVector.begin();
                 // }

                  start = m;
                  ++edgeCount;
                  ++count;
                }else{
                  edgeCount=0;
                  break;
                }
              }else{
                count=0;
                break;
              }
            }
*/
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
