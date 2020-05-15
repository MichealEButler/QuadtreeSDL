#include "Quadtree.h"

DrawFunctions * drawFunctions = nullptr;

Quadtree::Quadtree()
{
  //_x = 0;
  //_y = 0;
  //_w = 0;
  //_h = 0;
  //_n = 0;
  divided = false;
  _points.clear();
  _counter = 0;
  //_dx.clear();
  //_dy.clear();
  //_dw.clear();
  //_dh.clear();
}

Quadtree::Quadtree(int x, int y, int w, int h, int n)
{
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _n = n;
  cout << "Rectangle " << _x << " " << _y << " - " << _w << " " << _h << endl;
}

Quadtree::~Quadtree()
{
  _points.clear();

  if(divided)
  {
    delete topRightTree;
    delete topLeftTree;
    delete botLeftTree;
    delete botRightTree;
  }
}

void Quadtree::subdivide()
{
  topRightTree = new Quadtree(_x + (_w / 2), _y - (_h / 2), _w / 2, _h / 2, _n);
  topLeftTree = new Quadtree(_x - (_w / 2), _y - (_h / 2), _w / 2, _h / 2, _n);
  botRightTree = new Quadtree(_x + (_w / 2), _y + (_h / 2), _w / 2, _h / 2, _n);
  botLeftTree = new Quadtree(_x - (_w / 2), _y + (_h / 2), _w / 2, _h / 2, _n);
  divided = true;
}

bool Quadtree::insert(Point *p)
{
  if(!inBoundary(p))
  {
    return false;
  }

  if(_points.size() < _n)
  {
    _points.push_back(p);
    return true;
  } else {
    if(!divided)
    {
      subdivide();
      cout << "New Quad created! " << endl;
    }
    if(topRightTree->insert(p))
    {
      return true;
    }
    else if(topLeftTree->insert(p))
    {
      return true;
    }
    else if(botRightTree->insert(p))
    {
      return true;
    }
    else if(botLeftTree->insert(p))
    {
      return true;
    }
  }
}

bool Quadtree::inBoundary(Point *p)
{
  return (p->getX() >= _x - _w &&
        p->getX() < _x + _w &&
        p->getY() >= _y - _h &&
        p->getY() < _y + _h);
}

vector<Point*> Quadtree::getRectangles()
{
  return _points;
}

bool Quadtree::intersects(int rx, int ry, int rw, int rh)
{
  return !(rx - rw > _x + _w ||
    rx + rw < _x - _w ||
    ry - rh > _y + _h ||
    ry + rh < _y - _h);
}

void Quadtree::search(int rx, int ry, int rw, int rh, vector<Point*> found)
{
  if(!intersects(rx, ry, rw, rh))
  {
    return;
  } else {
    for(int i = 0; i < _points.size(); i++)
    {
      //cout << "Made to pre loop " << endl;
      if(_points[i]->getX() >= rx - rw && _points[i]->getX() <= rx + rw && _points[i]->getY() >= ry - rh && _points[i]->getY() <= ry + rh)
      {
        found.push_back(_points[i]);
        //cout << "Point found " << endl;
        _counter++;
      }

    }

    if(_counter > 0)
    {
      cout << "Counter = " << _counter << endl;
    }

    if(divided)
    {
      cout << "Yes divided " << endl;
      topRightTree->search(rx, ry, rw, rh, found);
      topLeftTree->search(rx, ry, rw, rh, found);
      botRightTree->search(rx, ry, rw, rh, found);
      botLeftTree->search(rx, ry, rw, rh, found);
    }
  }
}

void Quadtree::drawTree(SDL_Renderer * renderer)
{
  cout << "Drawing " << endl;
   SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
   SDL_Rect r;
   r.x = _x - _w;
   r.y = _y - _h;
   r.w = _w * 2;
   r.h = _h * 2;
   SDL_RenderDrawRect(renderer, &r);

   //drawFunctions->drawRect(renderer, _x, _y, _w, _h);
   for (int i = 0; i < _points.size(); i++)
   {
     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
     SDL_RenderDrawPoint(renderer, _points[i]->getX(), _points[i]->getY());
     //SDL_RenderDrawPoint(renderer, _points[i]->getX() + 1, _points[i]->getY());
     //SDL_RenderDrawPoint(renderer, _points[i]->getX(), _points[i]->getY() + 1);
     //SDL_RenderDrawPoint(renderer, _points[i]->getX() + 1, _points[i]->getY() + 1);
     cout << "Point rendered" << endl;
   }

   if(divided)
   {
     topRightTree->drawTree(renderer);
     cout << "Done NE " << endl;
     topLeftTree->drawTree(renderer);
     cout << "Done NW " << endl;
     botRightTree->drawTree(renderer);
     cout << "Done SE " << endl;
     botLeftTree->drawTree(renderer);
     cout << "Done SW " << endl;
   }
}

void Quadtree::clearQuad()
{
  if(_points.size() == 0)
  {
    return;
  } else {
    _points.clear();
  }

  if(divided)
  {
    topRightTree->clearQuad();
    topLeftTree->clearQuad();
    botRightTree->clearQuad();
    topRightTree->clearQuad();
  }
  //divided = false;
}

/*
void storeDrawArray(int x, int y, int w, int h)
{
  _dx.push_back(x);
  _dy.push_back(y);
  _dw.push_back(w);
  _dh.push_back(h);
}

vector<int> Quadtree::getDx()
{
  return _dx;
}

vector<int> Quadtree::getDy()
{
  return _dy;
}

vector<int> Quadtree::getDw()
{
  return _dw;
}

vector<int> Quadtree::getDh()
{
  return _dh;
}

*/
