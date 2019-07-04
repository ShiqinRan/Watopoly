#include <iostream>
#include "Gym.h"
using namespace std;

Gym::Gym(int cost, string name, Dice* d, Xwindow* w):Property{cost, name, w}, d{d} {}

Gym::~Gym() {}

bool Gym::canMortgage() {
	return true;
}

void Gym::landOn(Player* p) {
	int pay, multiplier, numGym;
	if(!owned) {
		p->buyProperty(this);
		if(!p->isinDebt()) {
			p->setGym(p->getGym()+1);
		}
	} else {
		d->roll();
		multiplier = d->getSum();
		numGym = owner->getGym();
	}

	if(p->getName() != owner->getName()) {
		cout << "You Have Landed On" << owner->getName() << "'s Property" << endl;
	} else if (numGym == 1) {
		pay = multiplier * 4;
	} else {
		pay = multiplier * 10;
	}
	cout << "You Have To Pay " << pay << "Dollar" << endl;
	p->changeCash(-pay);
	if(p->isinDebt()) {
		p->setOwer(owner);
	}
}

void Gym::draw(int x, int y, int color) {
	w->fillRectangle(x * CellL, y * CellH, CellL, CellH, color);
	w->drawString(x * CellL, y * CellH + 15, getName());
}

PropertyType Gym::pType() {
	return PropertyType::Gym;
}

CellType Gym::cType() {
	return CellType::Property;
}
