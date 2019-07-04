#include <iostream>
#include "gotoTims.h"
#include "player.h"

gtTims::gtTims(std::string name, Xwindow *w): Cell{name, w} {}
gtTims::~gtTims() {}

void gtTims::landOn(Player *p) {
	p->gtTims();
}

CellType gtTims::cType(){
  return  CellType::Non_Property;
}

void gtTims::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
