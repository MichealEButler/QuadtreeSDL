#ifndef POINT_H
#define POINT_H

#include <iostream>

using namespace std;

class Point
{
public:
  Point();
  Point(int x, int y);
  ~Point();

  void move(); // increments x or y each tick

  void setX();
  void setY();

  int getX();
  int getY();

private:
  int moveDir; // 1 = n 2 = s 3 = e 4 = wf

  int _x;
  int _y;
};

#endif
