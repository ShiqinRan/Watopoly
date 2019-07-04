#ifndef __AUCTION_H__
#define __AUCTION_H__
#include <iostream>
#include "property.h"
#include "player.h"
#include "cell.h"

class Property;

class Auction {
	int numPlayer;
	int bid;
	std::vector <Player*> aucPlayer;
	Property* aucProp;
public:
	Auction(Property* p, int numPlayer);
	~Auction();
	void addPlayer(Player* p);
	void startAuc();
};

#endif
