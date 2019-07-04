#include "tuition.h"
#include "player.h"
using namespace std;

Tuition::Tuition(string name, Xwindow *w): Cell{name,w} {}

void Tuition::landOn(Player *p) {
  cout << "Now You Need To Pay Your Tuition" << endl;
  cout << "Choose:" << endl;
  cout << "A: " << "pay 300 tuition." << endl;
  cout << "B: " << "pay 10% of your total worth." << endl;
  char c;
  cin >> c;
  if ( c == 'A') {
    p->changeCash(-300);
  }
  if ( c == 'B') {
    int x = p->getAsset();
    p->changeCash(-x);
  }
}

CellType Tuition::cType(){
  return  CellType::Non_Property;
}

void Tuition::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
