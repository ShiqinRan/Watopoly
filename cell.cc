#include "cell.h"
using namespace std;

const int Cell::CellL = 50;
const int Cell::CellH = 70;
const int Cell::PCellH = 20;

Cell::Cell(string name, Xwindow *w) : name{name}, w{w} {
}

Cell::~Cell(){};

void Cell::landOn(Player *p) {
  cout << "You have landed on " << name << endl;
}

void Cell::notify(Player *p) {
  landOn(p);
}

void Cell::draw(int x, int y, int color) {
cout << "1" << endl;
  w->fillRectangle(x * CellL, y * CellH, CellL, CellH, color);
  cout << "2" << endl;
  w->drawString(x * CellL, y * CellH + 15, getName());
  cout << "3" << endl;
}

string Cell::getName() {
  return name;
}
