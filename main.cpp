#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )

#include <iostream>
#include <GL/glut.h>
#include <windows.h>
#include "Game.h"
#include "Painter.h"

Game game;

void display()
{
  Painter p;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  game.render(p);
  glutSwapBuffers();
}

void mouse(int b, int s, int x, int y)
{
  y = (CELL_C*CELL_D) - y; //whoever decided it should be measured from the top should die
  if(!game.isDead())
  {
    switch(b)
    {
      case GLUT_LEFT_BUTTON:
        switch(s)
        {
          case GLUT_DOWN:
  	    game.makeActive(x/CELL_D, y/CELL_D);
	    break;
	  case GLUT_UP:
	    if(game.getActive(x/CELL_D, y/CELL_D))
	      game.openCell(x/CELL_D, y/CELL_D);
	    game.resetActive();
	    break;
        }
        break;
      case GLUT_RIGHT_BUTTON:
        if(s == GLUT_DOWN)
        {
          game.toggleFlag(x/CELL_D, y/CELL_D);
        }
        break;
    }
  }
  display();
}

int main(int argc, char **argv)
{
  std::cout<<"=> Window"<<std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(CELL_C*CELL_D, CELL_C*CELL_D);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Minesweeper");
  glClearColor(.8f, .8f, .8f, 1.f);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, CELL_C*CELL_D, 0, CELL_C*CELL_D, -1.f, 1.f);
  glutDisplayFunc(display);
  glutMouseFunc(mouse);

  glutMainLoop();
}


