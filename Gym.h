#ifndef __Gym_H__
#define __Gym_H__
#include <iostream>
#include "property.h"
#include "Dice.h"

class Auction;
class Player;

class Gym:public Property {
	Dice *d;
public:
	Gym(int cost, std::string name, Dice* d, Xwindow* w); //ctor
	~Gym(); //dtor
	bool canMortgage() override; // determine if this property can be mortgaged
	void landOn(Player* p) override; //make player take action when landing on the cell
	void draw(int x, int y, int color) override; // draw the Cell
	PropertyType pType() override; //return the type of property
	CellType cType() override; //determine the cell type
};

#endif
