#include "coopfee.h"

using namespace std;

CoopFee::CoopFee(string name, Xwindow *w) : Cell{name, w}{
}

void CoopFee::landOn(Player *p) {
  cout << "Collecting $150 to school" << endl;
  p->changeCash(-150);
}

CellType CoopFee::cType(){
  return  CellType::Non_Property;
}

void CoopFee::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
