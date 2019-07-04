#ifndef _OSAP_H_
#define _OSAP_H_

#include "cell.h"

class OSAP : public Cell {
public:
  OSAP(std::string name, Xwindow* w);
  void landOn(Player *p);
  void draw(int x, int y, int color) override;
  CellType cType() override;
};
#endif
