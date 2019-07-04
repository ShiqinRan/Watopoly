#include "dctimsline.h"
#include "player.h"

using namespace std;

//Ctor
Tim::Tim(string name, Xwindow* w):Cell{name, w} {}

void Tim::landOn(Player* p){
	if(p->isStuck()){
		cout << "Player " << p->getName() << " is now stuck at DC Tims Line." << endl;
		cout << "Your choice is ?" << endl; 
		p->outTims();
	}
	else{
		cout << "Player " << p->getName() << " has just passed DC Tims Line. Huehuehuehue" << endl;
	}
}

CellType Tim::cType() {
    return CellType::Non_Property;
}

void Tim::draw(int x, int y, int color) {
  w->fillRectangle(x * 50, y * 70, 50, 70, color);
  w->drawString(x * 50, y * 70 + 15, getName());
}
