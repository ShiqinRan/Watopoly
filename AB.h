#ifndef __AB_H__
#define __AB_H__
#include <iostream>
#include "property.h"
#include "auction.h"
#include "player.h"
#include "window.h"

class AB : public Property {
	std::string block;
	int* tuition;
	bool monopoly;
	int ImpCost;
	int ImpLevel;
	int cpos; // cell pos
public:
	AB(int cost, int ImpCost, std::string name, std::string block, int tuition[], Xwindow* w); //ctor
	~AB(); //dtor
	int getTuition(); //return the tuition
	bool isMonopoly(); //if its monopoly
	void setMonopoly(); //set AB to monopoly
	void setImpLevel(int l); //set improvement level
	bool canMortgage() override; //determine if this AB can be mortgaged
	void landOn(Player* p) override; //make player take action when landing on the cell
	int getImpLevel(); //return the ImpLevel
	int getImpCost(); //return improvement cost
	void draw(int x, int y, int color) override; //draw the cell
	PropertyType pType() override; // return the type of property
	CellType cType() override; //determine the cell type
};

#endif
