#ifndef _TUITION_H_
#define _TUITION_H_

#include <string>
#include <iostream>
#include "cell.h"

class Tuition : public Cell {
public:
 Tuition(std::string name, Xwindow *w);
 void landOn(Player *p);
 CellType cType() override;
 void draw(int x, int y, int color) override;
};

#endif
