#include <iostream>
#include "property.h"
using namespace std;

Property::Property(int cost, string name, Xwindow* w) : Cell(name, w) {
  this->cost = cost;
  owned = false;
  mortgaged = false;
  owner = nullptr;
}

Property::~Property() {}

int Property::getCost() {return cost;}

bool Property::isOwned() {return owned;}

bool Property::isMortgaged() {return mortgaged;}

Player* Property::getOwner() {return owner;}

void Property::setOwner(Player* p) {
	owner = p;
	owned = true;
}

void Property::changeOwner(Player* p) {
	owner->removeProperty(this);
	owner = p;
	owner->addProperty(this);
}

void Property::mortgage() {
	cout <<  name << " Is Mortgaged For " << cost/2 << "  Dollars!" << endl;
	mortgaged = true;
	owner->changeCash(cost / 2);
}

void Property::unMortgage() {
	int temp = cost * 0.6;
	if(owner->getCash() < temp) {
		cout << "Not Enough Money" << endl;
	}
	owner->changeCash(-temp);
	mortgaged = false;
}

void Property::setMortgage(bool m) {
	mortgaged = m;
}

CellType Property::cType() {
	return CellType::Property;
}

void Property::draw(int x, int y, int color) {
  w->fillRectangle(x * CellL, y * CellH, CellL, CellH, color);
  w->drawString(x * CellL, y * CellH + 15, getName());
}
