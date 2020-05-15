#include <iostream>
#include <ctime>
#include <time.h>
#include <vector>
#include "Display.h"
#include "Quadtree.h"
#include "Point.h"

using namespace std;

Display * display;
Quadtree * qt = NULL;
vector<Point*> points;
vector<Point*> found;

const int NUM_POINTS = 100;

int main(int argc, char** argv)
{
  int width = rand() % 800;
  int height = rand() % 800;
  int min = 100;
  int max = 700;

  srand(time(NULL));
  unsigned long seconds = 10;
  unsigned long begTime = clock();

  display = new Display();

  //declare outside loop uncomment below line
  qt = new Quadtree(400,400,400,400, 2);

  points = vector<Point*>(NUM_POINTS);
  cout << "Size of points vector = " << points.size() << endl;

  for(int i = 0; i < points.size(); i++)
  {
    int range = max - min;
    int w = rand() % range + min;
    int h = rand() % range + min;
    points[i] = new Point(50, h);

    //fill decalred here
    qt->insert(points[i]);
  }

  cout << "Number of points = " << points.size() << endl;

  display->initDisplay(" ", 0,0,800,800,true);

  while(display->running())
  {
    //when declaring outside loop comment out below line
    qt = new Quadtree(400,400,400,400, 2);

    cout << "Created new QT " << endl;
    for(int i = 0; i < points.size(); i++)
    {
      points[i]->move();
      //cout << "Point " << i << " x = " << points[i]->getX() << " y = " << points[i]->getY() << endl;

      //when declaring outside loop comment out below line
      qt->insert(points[i]);
    }
    display->updateDisplay();
    qt->drawTree(display->renderer);
    cout << "All points added " << endl;
    display->renderDisplay();
    display->renderPresent();
    display->clearRenderer();
    display->handleEvents();

    cout << "Broke loop " << endl;

    //when declaring outside loop comment out below line
    delete qt;
  }

  display->cleanDisplay();

  unsigned long elapsedTime = ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
  cout << "Elapsed time: " << elapsedTime << " secs." << endl;

  delete display;

  return 0;
}
