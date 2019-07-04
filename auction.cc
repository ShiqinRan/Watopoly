#include <iostream>
#include "auction.h"
using namespace std;

Auction::Auction(Property* p, int numPlayer): aucProp{p}, numPlayer{numPlayer}, bid{0} {}

Auction:: ~Auction() {};

void Auction::addPlayer(Player* p) {
	aucPlayer.emplace_back(p);
}

void Auction::startAuc() {
	int initBid = aucProp->getCost() / 2;
	cout << aucProp->getName() << " Is Now For Auction." << endl;
	cout << "The Bid Starts From: " << initBid << endl;
	int count=0;
	while(true) {
	    if(count >= numPlayer) count = 0;
	    char b;
	    if(numPlayer == 1) break;
	    if(aucPlayer[count]->isBankrupted()) {
	        cout << aucPlayer[count]->getName() << " Is Bankrupted." << endl;
	        continue;
	    }
	    cout << aucPlayer[count]->getName() << " Bid? (Y/N): " << endl;
	    cin >> b;
	    if(b == 'Y' || b == 'y') {
			int bid;
			while(true) {
			    cout << "Please Enter Your Bid:" << endl;
				cin >> bid;
				if(bid <= initBid) {
					cout << "Why So Cheap? Please Enter A Higher Bid:" << endl;
					continue;
				}
				break;
			}
				initBid = bid;
				cout << "Current Bid is: " << initBid << " By: " << aucPlayer[count]->getName() << endl;
		} else if (b == 'N' || b == 'n') {
		    cout << aucPlayer[count]->getName() << " Is Withdrawed From Auction." << endl;
		    aucPlayer.erase(aucPlayer.begin()+count);
		    numPlayer--;
		}
		count++;
	}
	cout << aucProp->getName() << " is sold for " << initBid << endl;
	aucPlayer[0]->changeCash(-initBid);
	if(!aucPlayer[0]->isBankrupted()) {
		aucProp->setOwner(aucPlayer[0]);
		aucPlayer[0]->addProperty(aucProp);
	}
}
