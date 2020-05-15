// SDL functions to display at varified points during simulation
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "DrawFunctions.h"

class Display
{
public:
  Display();
  ~Display();
  void initDisplay(const char* title, int x, int y, int w, int h, bool isShown);
  void handleEvents();
  void updateDisplay();
  void renderDisplay();
  void renderPresent();
  void clearRenderer();
  void cleanDisplay();

  bool running();
  bool cPressed();
  SDL_Renderer* renderer;

private:
  SDL_Window* window;
  SDL_Rect* srcR, destR;
  SDL_RendererInfo rendererInfo;

  bool isCPressed;
  bool isRunning;

};

#endif
