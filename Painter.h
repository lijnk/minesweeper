#pragma once

#include <iostream>
#include <GL/glut.h>

#define CELL_D 16

class Painter
{
public:
  void drawOpen(int x, int y, int s); //draws open cell
  void drawClose(int x, int y, bool f); //draws closed cell
  void drawFlag(int x, int y); //draws flag
  void drawMine(int x, int y, bool d); //draws Mine
  void drawNum(int x, int y, int v); //draws number
  void closedFrame(int x, int y); //draws closed cell frame
  void openFrame(int x, int y); //draws open cell frame
};


