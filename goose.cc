#include "goose.h"
#include "player.h"

using namespace std;

Goose::Goose(string name, Xwindow *w): Cell{name, w} {}

void Goose::landOn(Player *p) {
  cout << p->getName() << " Is Attackted by a goose" << endl;
}

CellType Goose::cType(){
  return  CellType::Non_Property;
}

void Goose::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
