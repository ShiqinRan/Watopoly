#ifndef _GOOSE_H_
#define _GOOSE_H_

#include "cell.h"
#include <iostream>
#include <string>

class Goose : public Cell {
public:
  Goose(std::string, Xwindow* w);
  void landOn(Player *p);
  CellType cType() override;
  void draw(int x, int y, int color) override;
};
#endif
