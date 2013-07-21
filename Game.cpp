#include "Game.h"

Game::cell Game::_board[CELL_C*CELL_C]; //replace 8s with game width and height

Game::Game()
{
  _active = -1;
  _death = -1;
  //init board
  for(int i = 0; i<CELL_C*CELL_C; i++)
  {
    _board[i].type = 0;
    _board[i].flag = false;
    _board[i].open = false;
  }
  //init mines
  srand(time(NULL));
  for(int i = 0; i<MINE_C; i++)
  {
    bool tmp = true;
    do
    {
      int x = rand() % CELL_C;
      int y = rand() % CELL_C;
      if(!isMine(x, y))
      {
        tmp = false;
        setState(x, y, MINE);
      }
    } while(tmp);
  }
  //set neighbours
  for(int y = 0; y<CELL_C; y++)
    for(int x = 0; x<CELL_C; x++)
      if(!isMine(x, y))
        setState(x, y, getNeighbours(x, y));

}

void Game::render(Painter &p)
{
  for(int y = 0; y < CELL_C; y++)
  {
    for(int x = 0; x < CELL_C; x++)
    {
      if(_death == boardNum(x, y))
        p.drawMine(x, y, true);
      else if(isOpen(x, y))
        p.drawOpen(x, y, getState(x, y));
      else if(getActive(x, y))
        p.drawOpen(x, y, 0);
      else
        p.drawClose(x, y, isFlag(x, y));
    }
  }
}

int Game::getNeighbours(int x, int y)
{
  return isMine(x-1, y-1) + isMine(x, y-1) + isMine(x+1, y-1) +
  	 isMine(x-1, y) + isMine(x+1, y) +
	 isMine(x-1, y+1) + isMine(x, y+1) + isMine(x+1, y+1);
}

int Game::getState(int x, int y)
{
  return _board[boardNum(x, y)].type;
}

void Game::setState(int x, int y, int v)
{
  _board[boardNum(x, y)].type = v;
}

bool Game::isMine(int x, int y)
{
  if(x < 0 || y < 0 || x > CELL_C-1 || y > CELL_C-1)
    return false;

  if(getState(x, y) == MINE)
    return true;
  return false;
}

bool Game::isOpen(int x, int y)
{
  return _board[boardNum(x, y)].open;
}

bool Game::isFlag(int x, int y)
{
  return _board[boardNum(x, y)].flag;
}

bool Game::isDead()
{
  return _death != -1;
}

void Game::makeActive(int x, int y)
{
  _active = boardNum(x, y);
}

bool Game::getActive(int x, int y)
{
  return (_active == boardNum(x, y));
}

void Game::resetActive()
{
  _active = -1;
}

void Game::openCell(int x, int y)
{
  if(x < 0 || y < 0 || y > CELL_C-1 || x > CELL_C-1)
    return;
  if(isOpen(x, y))
    return;

  _board[boardNum(x, y)].open = true;
  if(isMine(x, y))
  {
    _death = boardNum(x, y);
    endGame();
    return;
  }

  if(getState(x, y) == 0)
  {
    openCell(x-1, y+1); openCell(x, y+1); openCell(x+1, y+1);
    openCell(x-1, y); openCell(x+1, y);
    openCell(x-1, y-1); openCell(x, y-1); openCell(x+1, y-1);
  }
}

void Game::toggleFlag(int x, int y)
{
  _board[boardNum(x, y)].flag = !isFlag(x, y);
}

void Game::endGame()
{
  for(int _y=0; _y<CELL_C; _y++)
    for(int _x=0; _x<CELL_C; _x++)
      if(isMine(_x, _y))
        _board[boardNum(_x, _y)].open = true;

}

void Game::debugCell(int x, int y)
{
  std::cout<<"S: "<<_board[boardNum(x, y)].type<<" F: "<<_board[boardNum(x, y)].flag<<" O: "<<_board[boardNum(x, y)].open<<" X: "<<x<<" Y: "<<y<<std::endl;
}

int Game::boardNum(int x, int y)
{
  return x+(y*CELL_C); //replace 8 with game width
}


