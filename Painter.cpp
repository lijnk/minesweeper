#include "Painter.h"

void Painter::drawOpen(int x, int y, int s)
{
  glEnable(GL_DEPTH_TEST);
  openFrame(x, y);

  switch(s)
  {
    case 0:
      break;
    case 9:
      drawMine(x, y, false);
      break;
    default:
      openFrame(x, y);
      drawNum(x, y, s);
      break;
  }
  glDisable(GL_DEPTH_TEST);
}

void Painter::drawClose(int x, int y, bool f)
{
  closedFrame(x, y);
  if(f)
    drawFlag(x, y);
}

void Painter::drawFlag(int x, int y)
{
  glColor3f(0.f, 0.f, 0.f);
  int _x = (x*CELL_D)+3;
  int _y = (y*CELL_D)+3;

  //platform
  glBegin(GL_POLYGON);
    glVertex2i(_x, _y+2);
    glVertex2i(_x+9, _y+2);
    glVertex2i(_x+9, _y+3);
    glVertex2i(_x+7, _y+3);
    glVertex2i(_x+7, _y+4);
    glVertex2i(_x+3, _y+4);
    glVertex2i(_x+3, _y+3);
    glVertex2i(_x, _y+3);
  glEnd();

  //mast
  glBegin(GL_LINES);
    glVertex2i(_x+4, _y+4);
    glVertex2i(_x+4, _y+7);
  glEnd();

  //flag
  glColor3f(1.f, 0.f, 0.f);
  glBegin(GL_TRIANGLES);
    glVertex2i(_x+5, _y+7);
    glVertex2i(_x+5, _y+12);
    glVertex2i(_x, _y+9);
  glEnd();
}

void Painter::drawMine(int x, int y, bool d)
{
  glEnable(GL_DEPTH_TEST);
  int _x = (x*CELL_D)+3;
  int _y = (y*CELL_D)+3;

  //shine
  glColor3f(1.f, 1.f, 1.f);
  glBegin(GL_QUADS);
    glVertex2i(_x+3, _y+8);
    glVertex2i(_x+5, _y+8);
    glVertex2i(_x+5, _y+6);
    glVertex2i(_x+3, _y+6);
  glEnd();

  //spikes
  glColor3f(0.f, 0.f, 0.f);
  glBegin(GL_LINES);
    glVertex2i(_x+5, _y-1);
    glVertex2i(_x+5, _y+12);

    glVertex2i(_x-1, _y+5);
    glVertex2i(_x+12, _y+5);

    glVertex2i(_x+1, _y+1);
    glVertex2i(_x+10, _y+10);

    glVertex2i(_x+1, _y+10);
    glVertex2i(_x+10, _y+1);
  glEnd();

  //ball
  glBegin(GL_POLYGON);
    glVertex2i(_x+3, _y+1);
    glVertex2i(_x+1, _y+4);
    glVertex2i(_x+1, _y+7);
    glVertex2i(_x+3, _y+10);
    glVertex2i(_x+8, _y+10);
    glVertex2i(_x+10, _y+7);
    glVertex2i(_x+10, _y+4);
    glVertex2i(_x+8, _y+1);
  glEnd();

  //dead
  if(d)
  {
    glColor3f(1.f, 0.f, 0.f);
    glBegin(GL_QUADS);
      glVertex2i(x*CELL_D, y*CELL_D);
      glVertex2i((x+1)*CELL_D, y*CELL_D);
      glVertex2i((x+1)*CELL_D, (y+1)*CELL_D);
      glVertex2i(x*CELL_D, (y+1)*CELL_D);
    glEnd();
  }
  glDisable(GL_DEPTH_TEST);
}

void Painter::drawNum(int x, int y, int v)
{
  switch(v)
  {
    case 1:
      glColor3f(0.f, 0.f, 1.f);
      break;
    case 2:
      glColor3f(0.f, 1.f, 0.f);
      break;
    case 3:
      glColor3f(1.f, 0.f, 0.f);
      break;
    case 4:
      glColor3f(0.f, 0.f, .5f);
      break;
    case 5:
      glColor3f(.5f, 0.f, 0.f);
      break;
    case 6:
      glColor3f(.5f, .5f, 1.f);
      break;
    case 7:
      glColor3f(0.f, 0.f, .0f);
      break;
    case 8:
      glColor3f(.5f, .5f, .5f);
      break;
  }
  glRasterPos2i(x*CELL_D + 4, y*CELL_D + 4);
  glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + v);
}

void Painter::closedFrame(int x, int y)
{
  glColor3f(1.f, 1.f, 1.f);
  glBegin(GL_LINE_LOOP);
    glVertex2i(x*CELL_D, y*CELL_D);
    glVertex2i(x*CELL_D, (y+1)*CELL_D-1);
    glVertex2i((x+1)*CELL_D-1, (y+1)*CELL_D-1);
    glVertex2i((x+1)*CELL_D-2, (y+1)*CELL_D-2);
    glVertex2i(x*CELL_D+1, (y+1)*CELL_D-2);
    glVertex2i(x*CELL_D+1, y*CELL_D+1);
  glEnd();

  glColor3f(.2f, .2f, .2f);
  glBegin(GL_LINE_LOOP);
    glVertex2i(x*CELL_D, y*CELL_D+1);
    glVertex2i((x+1)*CELL_D-1, y*CELL_D+1);
    glVertex2i((x+1)*CELL_D-1, (y+1)*CELL_D);
    glVertex2i((x+1)*CELL_D-2, (y+1)*CELL_D-1);
    glVertex2i((x+1)*CELL_D-2, y*CELL_D+2);
    glVertex2i(x*CELL_D+1, y*CELL_D+2);
  glEnd();

}

void Painter::openFrame(int x, int y)
{
  glColor3f(.2f, .2f, .2f);
  glBegin(GL_LINE_STRIP);
    glVertex2i(x*CELL_D, y*CELL_D);
    glVertex2i(x*CELL_D, (y+1)*CELL_D);
    glVertex2i((x+1)*CELL_D, (y+1)*CELL_D);
  glEnd();
}


