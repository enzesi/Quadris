#include <iostream>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSizex, int gridSizey,
   int winSizex, int winSizey):
 gridSizex{gridSizex}, gridSizey{gridSizey},
   winSizex{winSizex}, winSizey{winSizey}, xw{winSizey, winSizex} {
   xw.fillRectangle(0, 0, winSizey, winSizex, Xwindow::White);
}

void GraphicsDisplay::notify(Subject &whoNotified) {
  auto info = whoNotified.getInfo();
  int cellSize = 28;
  if (info.empty) {
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::White);
    return;
  }
  switch(info.type) {
      case 'I':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Red);
    break;
   case 'J':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Black);
    break;
   case 'L':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Green);
   case 'O':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Black);
   case 'S':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Blue);
   case 'Z':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Green);
   case 'T':
    xw.fillRectangle(info.y * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Red);
 /*  case 'L':
    xw.fillRectangle(info.x * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::White);
   case 'O':
    xw.fillRectangle(info.x * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Black);
   case 'S':
    xw.fillRectangle(info.x * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::White);
   case 'Z':
    xw.fillRectangle(info.x * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Black);
   case 'T':
    xw.fillRectangle(info.x * cellSize, info.x * cellSize, cellSize, cellSize, Xwindow::Black);*/
  }
}
