#include "Display.h"

using namespace std;

//SDL_Renderer* renderer = nullptr;
//DrawFunctions * drawFunctions = nullptr;

Display::Display()
{
    //drawFunctions = new DrawFunctions();
}

Display::~Display()
{

}

void Display::initDisplay(const char* title, int x, int y, int w, int h, bool isShown)
{

  isCPressed = false;

  if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    cout << endl << "Display initialised . . . " << endl;

    window = SDL_CreateWindow(title, x, y , w, h, SDL_WINDOW_SHOWN);
    if(window)
    {
      cout << "Window created . . . " << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer)
    {
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      cout << "Renderer created . . . " << endl;
    }

    isRunning = true;
  } else {
    isRunning = false;
  }

}

void Display::handleEvents()
{
  SDL_Event e;

  SDL_PollEvent(&e);

  if(e.type == SDL_KEYDOWN)
  {
    if (e.key.keysym.sym == SDLK_RETURN)
    {
      isRunning = false;
    }

    if (e.key.keysym.sym == SDLK_c)
    {
      isCPressed = true;
    }

    if (e.key.keysym.sym == SDLK_x)
    {
      isCPressed = false;
    }
  }

  if (e.type == SDL_QUIT)
  {
    isRunning = false;
  }
}

void Display::updateDisplay()
{

}

void Display::clearRenderer()
{
  SDL_RenderClear(renderer);
}

void Display::renderDisplay()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Display::renderPresent()
{
  SDL_RenderPresent(renderer);
}

void Display::cleanDisplay()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  SDL_Quit();

  cout << "Display cleaned . . . " << endl << endl;
}

bool Display::running()
{
  return isRunning;
}

bool Display::cPressed()
{
  return isCPressed;
}
