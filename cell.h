#ifndef _CELL_H_
#define _CELL_H_

#include <string>
#include <iostream>
#include "window.h"


class Player;

enum class CellType {Property, Non_Property};

class Cell {
protected:
  int index;
  std::string name;
  Xwindow* w;
  const static int CellL;
  const static int CellH;
  const static int PCellH;
public:
  Cell(std::string name, Xwindow* w);
  virtual ~Cell();
  virtual void landOn(Player *p);
  void notify(Player *p);
  virtual void draw(int x, int y, int color);
  std::string getName();
  virtual CellType cType() = 0;
};

#endif
