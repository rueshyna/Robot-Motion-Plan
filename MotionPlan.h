#ifndef MP_H
#define MP_H
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <QtGui>
#include <vector>
#include <cstring>
#include <string>
#define SCREEN_WIDTH 128*SCALE
#define SCREEN_HIGHT 128*SCALE
#define SCALE 3
#define PF_WIDTH 128*PF_SCALE
#define PF_HIGHT 128*PF_SCALE
#define PF_SCALE 3
#define M 255

using namespace std;

enum STATE { NUM_OF_OBJECTS=0, NUM_OF_POLYGONS, NUM_OF_VERTICES, VERTICE_POINT, INIT, GOAL, NUM_OF_CONTROL_POINTS,  CONTROL_POINT };

enum INPUT { ROBOT, OBSTACLE };

enum ROBOT_POS {R_INIT, R_GOAL, NONE};

class ObjectData;
class BitmapItem;
class RobotData;
class Parser;
typedef ObjectData ObstacleData;
class Bitmap;
class Window;
class ObjectItem;
class BitmapItem;
class PainterWidge;
#include "Data.h"
#include "Algorithm.h"
#include "View.h"

#endif
