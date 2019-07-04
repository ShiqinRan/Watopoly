#include "slc.h"

using namespace std;

SLC::SLC(string name, Xwindow* w):Cell{name, w} {}

void SLC::landOn(Player* p){
	srand(time(NULL));
	cout << "You Have Landed On SLC." << endl;
	int denom = rand()%100;

	if(denom == 0 && totalRim < 4){
		p->setRimCup(1);
		totalRim++;
	}
	else{
		denom = rand()%24;
		p->setOnTurn(false); 
	}
	if(denom < 3){
		p->Move(-3);
	}
	else if(denom >=  3 && denom < 7) {
		p->Move(-2);
	}
	else if(denom >= 7 && denom < 11){
		p->Move(-1);
	}
	else if(denom >= 11 && denom < 14){
		p->Move(1);
	}
	else if(denom >= 14 && denom < 18){
		p->Move(2);
	}
	else if(denom >= 18 && denom < 22){
		p->Move(3);
	}
	else if(denom == 22){
		p->gtOSAP();
	}
	else{
		p->gtTims();
	}
}

CellType SLC::cType() {
    return CellType::Non_Property;
}

void SLC::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
