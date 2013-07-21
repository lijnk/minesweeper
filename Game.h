#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Painter.h"

#define CELL_C 20
#define MINE_C 30

class Game
{
  typedef struct
  {
    int type;
    bool flag, open;
  } cell;
  static cell _board[CELL_C*CELL_C]; //game board
  int _active; //active cell
  int _death; //death cell
public:
  enum {MINE = 9}; //0-8 are free states
  Game();

  void render(Painter &p); //renders board
  int getState(int x, int y); //returns state
  int getNeighbours(int x, int y); //returns neighbour count
  void setState(int x, int y, int v); //set state
  bool isMine(int x, int y); //returns if mine is there
  bool isOpen(int x, int y); //returns if cell is open
  bool isFlag(int x, int y); //returns flag state
  bool isDead(); //returns whether game is dead
  void makeActive(int x, int y); //makes selection active
  bool getActive(int x, int y); //compares active cell
  void resetActive(); //resets active cell
  void openCell(int x, int y); //opens cell
  void toggleFlag(int x, int y); //toggle's flag state
  void endGame(); //ends game

  void debugCell(int x, int y); //returns debug info for the cell
  int boardNum(int x, int y); //returns board num for X and Y
};


