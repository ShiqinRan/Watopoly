#include "osap.h"
#include "player.h"

using namespace std;

OSAP::OSAP(string name, Xwindow *w): Cell{name, w} {}

void OSAP::landOn(Player *p) {
  cout << "Collect $200 OSAP!!!" << endl;
  p->changeCash(200);
}

CellType OSAP::cType(){
  return  CellType::Non_Property;
}

void OSAP::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
