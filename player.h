#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include "window.h"
#include "property.h"
#include "cell.h"
#include "auction.h"

class AB;
class Property;

class Player{
protected:
	Xwindow* w;
	//Names:
	std::string name;
	std::string n;
	//Game related:
	int number; //The [number]th player
	int pos; //Position
	int otherNum; //nunber of other players
	int rimNum; //Store the number of Rim Cups of this player
	int cash, asset, ownedNum; //Store financial information
	int gymNum, resNum; 
	int turnAtTim; //The number of turns they have in DC Tims
	std::vector<Player*> otherPlayer; 
	std::vector<Property*> ownedProp;
	Player* ower;
	bool onTurn, bankrupt; // Is the player in tims, on turn, or bankrupted?
	bool stuck;
	bool debt;
	bool SLC;
	
public:
	Player(std::string name, std::string n , Xwindow* w);

//Public Methods:
	//Property related:
	int getGym(); //done
	int getRes(); //done
	void setGym(int n); 
	void setRes(int n);
	//Cash
	int getCash(); //done
	void setCash(int c);
	void changeCash(int c);
	//Asset
	int getAsset(); //done
	void setAsset(int a);
	void changeAsset(int a);
	void displayAsset(); //??
	//Position
	int getPos(); //done
	void setPos(int i);
	void Move(int n);
	void gtOSAP();
	bool fromSLC();
	void outSLC();
	//Rim Cups
	int getRimCup(); //Number of RimCup (done)
	void setRimCup(int r); //Will need RimCup (done)
	void changeRimCup(int r); //Will need RimCup (done)
	//Name related:
	std::string getName(); //done
	std::string getN(); //done
	//Turn:
	bool isOnTurn(); //done
	void setOnTurn(bool onturn); //done
	//Tims:
	bool isStuck();
	int getTimTurn(); //Number of turns in Tim already (done)
	void setTim(bool tim, int turn); //tim: is player stuck, turn: number of turns stuck already
	void gtTims();
	void outTims();
	//Bankrupt:
	bool isBankrupted(); //done
	void setBankrupt(bool b);
	void declareBankrupt();
	//Set:
	void addPlayer(Player* newPlayer); //done
	void setOtherNum(int n);
	Player* getOtherPlayer(int index);
	Player* getOwer();
	void setOwer(Player* p);
	bool isinDebt();
	bool setinDebt(bool debt);
	//Property
	void addProperty(Property* newProperty); //done
	void buyProperty(Property* p);
	void removeProperty(Property* p);
	Property* findProp(std::string name);
	void improve(AB* ab, std::string name);
	void mortgage(Property* p);
	void unmortgage(Property* p);
	void trade(Player* receiver, std::string give, std::string receive);
	void drawPlayer();
	~Player();
};

#endif
