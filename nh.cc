#include "nh.h"

using namespace std;

NH::NH(string name, Xwindow* w): Cell{name,w} {}

void NH::landOn(Player* p){
	srand(time(0));
	cout << "You Have Landed On Needle's Hall." << endl;
	int denom = rand()%100;

	if(denom == 0 && totalRim < 4){
		p->changeRimCup(1);
		totalRim++;
	}
	else{
		denom = rand()%18;
		p->setOnTurn(false); 
	}
	if(denom == 0){
		p->changeCash(-200);
		
	}
	else if(denom ==  1 && denom == 2) {
		p->changeCash(-100);
		
	}
	else if(denom >= 3 && denom < 6){
		p->changeCash(-50);
	}
	else if(denom >= 6 && denom < 12){
		p->changeCash(25);
	}
	else if(denom >= 12 && denom < 15){
		p->changeCash(50);
	}
	else if(denom >= 15 && denom < 17){
		p->changeCash(100);
	}
	else{
		p->changeCash(200);
	}
}

CellType NH::cType() {
    return CellType::Non_Property;
}

void NH::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
