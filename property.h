#ifndef __PROPERTY_H__
#define __PROPERTY_H__
#include <iostream>
#include "cell.h"
#include "player.h"


enum class PropertyType {Gym, Residence, AB};
class Player;
class Property : public Cell {
protected:
	std::string name;
	int cost;
	bool owned;
	bool mortgaged;
	Player* owner;
	Xwindow* w;
public:
	Property(int cost, std::string name, Xwindow* w); //ctor 
	virtual ~Property(); //virtual dtor
	virtual PropertyType pType() = 0; //determine the type
	CellType cType() override; //determine the cell type
	int getCost(); //return the cost of the property 
	bool isOwned(); // if the property is owned
	bool isMortgaged(); // if the property is mortgaged
	virtual bool canMortgage()=0; // the property can be mortgaged
	Player* getOwner(); //return the owner of the property
	void setOwner(Player* p); //set initial owner
	void changeOwner(Player* p); //change to another owner
	void mortgage(); //mortgage the property
	void unMortgage(); //unmortgage the property 
	void setMortgage(bool m); //set mortgage status when loading game
	virtual void draw(int x, int y, int color);
};


#endif
