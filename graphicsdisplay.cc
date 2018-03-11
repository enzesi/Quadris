#include <iostream>
#include <string>
#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
using namespace std;

GraphicsDisplay::GraphicsDisplay(int gridSizex, int gridSizey,
                                 int winSizex, int winSizey):
gridSizex{gridSizex}, gridSizey{gridSizey},
winSizex{winSizex}, winSizey{winSizey}, xw{winSizey, winSizex} {
    xw.fillRectangle(0, 0, winSizey, winSizex, Xwindow::Orange);
    xw.drawBigString(50, 50, "Level", Xwindow::Black);
    xw.drawBigString(80, 100, "0", Xwindow::Black);
    xw.drawBigString(50, 180, "Score", Xwindow::Black);
    xw.drawBigString(80, 230, "0", Xwindow::Black);
    xw.drawBigString(30, 310, "Hi_Score", Xwindow::Black);
    xw.drawBigString(80, 370, "0", Xwindow::Black);
    xw.drawBigString(50, 440, "Next", Xwindow::Black);
    xw.fillRectangle(30, 480, 150, 105, Xwindow::White);
    xw.fillRectangle(210, 0, 5, winSizex, Xwindow::Black);
    xw.fillRectangle(215, 0, winSizey - 215, winSizex, Xwindow::White);
}

void GraphicsDisplay::notify(Subject &whoNotified) {
    auto info = whoNotified.getInfo();
    int cellSize = 35;
    if (info.empty && info.type != '?') {
        xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::White);
        return;
    }
    switch(info.type) {
        case '*':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Brown);
            break;
        case 'I':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Red);
            break;
        case 'J':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Blue);
            break;
        case 'L':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Green);
            break;
        case 'O':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Cyan);
            break;
        case 'S':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Yellow);
            break;
        case 'Z':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Magenta);
            break;
        case 'T':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Orange);
            break;
        case '?':
            xw.fillRectangle(info.y * cellSize + 215, info.x * cellSize, cellSize, cellSize, Xwindow::Black);
            break;
    }
}

void GraphicsDisplay::updatenext(char next) {
    xw.fillRectangle(30, 480, 150, 105, Xwindow::White);
    if (next == 'I') {
        xw.fillRectangle(35, 525, 140, 35, Xwindow::Red);
    } else if (next == 'O') {
        xw.fillRectangle(70, 500, 70, 70, Xwindow::Cyan);
    } else if (next == 'J') {
        xw.fillRectangle(55, 500, 35, 35, Xwindow::Blue);
        xw.fillRectangle(55, 535, 105, 35, Xwindow::Blue);
    } else if (next == 'L') {
        xw.fillRectangle(125, 500, 35, 35, Xwindow::Green);
        xw.fillRectangle(55, 535, 105, 35, Xwindow::Green);
    } else if (next == 'Z') {
        xw.fillRectangle(55, 500, 70, 35, Xwindow::Magenta);
        xw.fillRectangle(90, 535, 70, 35, Xwindow::Magenta);
    } else if (next == 'S') {
        xw.fillRectangle(90, 500, 70, 35, Xwindow::Yellow);
        xw.fillRectangle(55, 535, 70, 35, Xwindow::Yellow);
    } else if (next == 'T') {
        xw.fillRectangle(55, 500, 105, 35, Xwindow::Orange);
        xw.fillRectangle(90, 535, 35, 35, Xwindow::Orange);
    }
}

void GraphicsDisplay::updatescore(int score) {
    xw.fillRectangle(0, 180, 180, 100, Xwindow::Orange);
    string sco = to_string(score);
    xw.drawBigString(80, 230, sco, Xwindow::Black);
}

void GraphicsDisplay::updatehiscore(int hi_score) {
    xw.fillRectangle(0, 320, 180, 80, Xwindow::Orange);
    string sco = to_string(hi_score);
    xw.drawBigString(80, 370, sco, Xwindow::Black);
}

void GraphicsDisplay::updatelevel(int level) {
    xw.fillRectangle(0, 50, 180, 100, Xwindow::Orange);
    string lev = to_string(level);
    xw.drawBigString(80, 100, lev, Xwindow::Black);
}
