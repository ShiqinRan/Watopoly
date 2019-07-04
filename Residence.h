#ifndef __RESIDENCE_H__
#define __RESIDENCE_H__
#include <iostream>
#include "property.h"

class Player;
class Auction;

class Residence:public Property{
	int initRent;
public:
	Residence(int cost, std::string name, Xwindow* w); //ctor
	~Residence(); //dtor
	int getRent(); //return the rent of the residence
	void landOn(Player* p) override; // make player take action when landing on the cell
	bool canMortgage() override; //see if this can be mortgaged
	void draw(int x, int y, int color) override; // draw the cell
	PropertyType pType() override; // return the type of property
	CellType cType() override; //determine the cell type
};

#endif
