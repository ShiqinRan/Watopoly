#include <iostream>
#include "AB.h"
using namespace std;

AB::AB(int cost, int ImpCost, string name, string block, int tuition[], Xwindow* w): Property{cost, name, w}, 
		block{block}, monopoly{false}, ImpCost{ImpCost}, ImpLevel{0}, tuition{tuition} {}

AB::~AB() {};

int AB::getTuition() {
	if(!monopoly) {
		return tuition[0];
	}
	if (ImpLevel = 0) {return 2 * tuition[0];}
	return tuition[ImpLevel];
}

bool AB::isMonopoly() {return monopoly;}

void AB::setMonopoly() {monopoly = true;}

void AB::setImpLevel(int l) {
	if(l > 5) {
		cout << "You Already Have All Improvements!" << endl;
		return;
	} 
	if(l < 0) {
		cout << "You Have No More Improvements To Sell!" << endl;
		return;
	}
	ImpLevel = l;
}

bool AB::canMortgage() {
	if(ImpLevel != 0) {return false;}
	return true;
}

void AB::landOn(Player* p) {
	if(!isOwned()){
		p->buyProperty(this);
	} else {
	    cout << "You Have Landed On " << owner->getName() << "'s Property." << endl;
	    cout << "You Have To Pay " << owner << getTuition() << " Dollars" << endl;
		p->changeCash(-(getTuition()));
	}
	if(p->isinDebt()) {
		p->setOwer(owner);
	}
}

int AB::getImpLevel() {return ImpLevel;}

int AB::getImpCost() {return ImpCost;}

void AB::draw(int x, int y, int color) {
        w->fillRectangle(x * CellL, y * CellH, CellL, 20, 0);
        w->drawString(x * CellL, y * CellH, getName());
        w->fillRectangle(x * CellL, y * CellH + 20, CellL, CellH, color);
}

PropertyType AB::pType() {
	return PropertyType::AB;
}

CellType AB::cType() {
	return CellType::Property;
}
