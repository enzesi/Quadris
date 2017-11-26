#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "info.h"
class Cell;

class GraphicsDisplay: public Observer {
  const int gridSizex, gridSizey, winSizex, winSizey;
  Xwindow xw;
 public:
  GraphicsDisplay(int gridSizex, int gridSizey, int winSizex, int winSizey);

  void notify(Subject &whoNotified) override;
};
#endif
