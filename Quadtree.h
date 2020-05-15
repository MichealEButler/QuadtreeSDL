#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <SDL2/SDL.h>
#include "DrawFunctions.h"
#include "Point.h"

using namespace std;

class Quadtree
{
public:
  Quadtree();
  Quadtree(int x, int y, int w, int h, int n);
  ~Quadtree();

  bool insert(Point *p);
  void subdivide();
  void search(int rx, int ry, int rw, int rh, vector<Point*> found);
  bool intersects(int rx, int ry, int rw, int rh); // range of search rectangle

  vector<Point*> getRectangles();
  bool inBoundary(Point *p);
  bool divided;

  void drawTree(SDL_Renderer * renderer);
  void clearQuad();

private:

  //Children of this tree
  Quadtree *topLeftTree;
  Quadtree *topRightTree;
  Quadtree *botLeftTree;
  Quadtree *botRightTree;

  vector<Point*> _points;
/*
  vector<int> _dx; // 2d array of rectangle to be drawn and called back in the main function
  vector<int> _dy;
  vector<int> _dw;
  vector<int> _dh;
*/

  int _counter;
  int _x;
  int _y;
  int _h;
  int _w;
  int _n;
};

#endif
