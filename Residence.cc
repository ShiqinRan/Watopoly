#include <iostream>
#include "Residence.h"
using namespace std;

Residence::Residence(int cost, string name, Xwindow* w): Property{cost,name,w}, initRent{25} {}

Residence::~Residence() {}

int Residence::getRent() {
	int numRes = owner->getRes();
	if(numRes = 1) {return 25;}
	if(numRes = 2) {return 50;}
	if(numRes = 3) {return 100;}
	if(numRes = 4) {return 200;}
}

void Residence::landOn(Player* p) {
	int pay= 0;
	if(!owned) {
		p->buyProperty(this);
		if(!p->isinDebt()) {
			p->setRes(p->getRes()+1);
		}
		return;
	}
	if(owner->getName() != p->getName()) {
	    cout << "You Have Landed On " << owner->getName() << "'s Residence" << endl;
	    pay = getRent();
	    cout << "You Have To Pay " << owner->getName() << pay << " Dollars" << endl;
	    p->changeCash(-pay);
	    if(p->isinDebt()) {
		    p->setOwer(owner);
	    }
	}  
}

bool Residence::canMortgage() {
    return true;
}
void Residence::draw(int x, int y, int color) {
        w->fillRectangle(x * CellL, y * CellH, CellL, CellH, color);
        w->drawString(x * CellL, y * CellH + 20, getName());
}

PropertyType Residence::pType() {
	return PropertyType::Residence;
}

CellType Residence::cType() {
    return CellType::Property;
}


