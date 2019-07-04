#ifndef _COOPFEE_H_
#define _COOPFEE_H_

#include "player.h"
#include "cell.h"
#include <iostream>
#include <string>


class CoopFee : public Cell {
public:
   CoopFee(std::string name, Xwindow *w);
   void landOn(Player *p);
   CellType cType() override;
   void draw(int x, int y, int color) override;
};
#endif
