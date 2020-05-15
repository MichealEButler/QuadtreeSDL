#include "Point.h"

Point::Point()
{
  _x = 0;
  _y = 0;

}

Point::Point(int x, int y)
{
  _x = x;
  _y = y;
  moveDir = (rand() % 1) + 1;
}

Point::~Point()
{

}

void Point::move()
{

  //move east
  if(moveDir == 1)
  {
    if(_x <= 1)
    {
      setX(1);
      moveDir = 2;
    } else {
      setX(-1);
    }
    return;
  }
  //move west
  if(moveDir == 2)
  {
    if(_x >= 798)
    {
      setX(-1);
      moveDir = 1;
    } else {
      setX(1);
    }
    return;
  }
  //go one direction
  //if out of bounds turn around
}

void Point::setX(int x)
{
  _x = _x + x;
}

void Point::setY()
{
  _y++;
}

int Point::getX()
{
  return _x;
}

int Point::getY()
{
  return _y;
}
