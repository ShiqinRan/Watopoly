#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "gameboard.h"
#include "player.h"
#include "Dice.h"
#include "window.h"
#include "cell.h"
#include "auction.h"
#include <unistd.h>

using namespace std;

int totalRim = 0;

int main(int argc, char* argv[]) {	
	//Parameters
	cin.exceptions(ios::failbit | ios::eofbit);
	bool Test = false;
	bool testIn = false;
	bool newGame = true;
	int numPlayer;
	bool exit = false;
	Player* currPlayer;

	// initialize a new gameboard
	Xwindow w;
	Gameboard* GB = new Gameboard(&w);
	GB->init();

	// Testing Mode
	if((argc == 2) && (argv[1] == "-testing")) {
	    cout << "In Testing Mode......." << endl;
		Test = true;
	}

	// Loading File
	if(argc == 3 && argv[1] == "-load") {
		newGame = false;
		ifstream file {argv[2]};
		GB->loadGame(file);
		cout << "Loading Game....." << endl;
	}

	//NewGame
	if(newGame) {
		cout << "WELCOME TO WATOPOLY!!!" << endl;
		cout << "Please Enter The Number Of Players:" << endl;
		cin >> numPlayer;
		GB->setNumPlayer(numPlayer);
		for(int i = 0; i < numPlayer; ++i) {
			string name;
			string c;
			cout << "Player" << i+1 << " Name: " << endl;
			cin.ignore();
			getline(cin,name);
			cout << "Player" << i+1 << " Character: " << endl;
			cin >> c;
			Player* p = new Player(name, c, &w); //initialize Players
			GB->addPlayer(p);
		}
	}
	    
	GB->linkPlayer();
	cout << endl;
	
	//Starts Playing
	cout << "LET'S START!" << endl;
	int count = 1; //count the index of player
	Dice* d = new Dice(); //initiate a Dice
	GB->setDice(d);
	currPlayer = GB->getInxPlayer(count);
	currPlayer->setOnTurn(true);
	
	//draw board
	GB->drawBoard();
	
	//Take in commands
	char cmd;
	while(true) {
		if(exit) {
			delete GB;
			delete d;
			break;
		}
		if(GB->getNumPlayer() == 1) {
			cout << currPlayer->getName() << "WINS!!!!!!" << endl;
			delete GB;
			delete d;
			break;
		}
		if(currPlayer->isBankrupted()) {
		    GB->removePlayer(currPlayer);
		    GB->setNumPlayer(GB->getNumPlayer()-1);
		    currPlayer = GB->getInxPlayer(count);
		}
		cout << endl;
		cout << currPlayer->getName() << endl; //prints the name of current player on turn
		cout << "Please Enter Your Command:" << endl;
		if(currPlayer->isOnTurn()) {
			cout << "r (roll) "<< endl;
			cout << "t (trade <name> <give> <recieve>)" << endl;
			cout << "i (improve <property> buy/sell)" << endl;
			cout << "m (mortgage <property>)" << endl;
			cout << "u (unmortgage <property>)" << endl;
			cout << "a (Display Your Assets)" << endl;
			cout << "l (Display All Player's Assets)" << endl;
			cout << "s (Save Game)" << endl;
		} else if (currPlayer->isinDebt()){
			cout << "t (trade <name> <give> <recieve>)" << endl;
			cout << "i (improve <property> buy/sell)" << endl;
			cout << "m (mortgage <property>)" << endl;
			cout << "s (Save Game)" << endl;
			cout << "b (Declare Bankrupcy)" << endl;
		} else {
			cout << "n (Next Player) "<< endl;
			cout << "t (trade <name> <give> <recieve>)" << endl;
			cout << "i (improve <property> buy/sell)" << endl;
			cout << "m (mortgage <property>)" << endl;
			cout << "u (unmortgage <property>)" << endl;
			cout << "a (Display Your Assets)" << endl;
			cout << "l (Display All Player's Assets)" << endl;
			cout << "s (Save Game)" << endl;
		}
		

		//Read in Commands
		try {
			cin >> cmd;
		} catch (ios::failure&) {
			cin.clear();
			cin.ignore();
			cout << "Incorrect Input" << endl;
			continue;
		}

		switch(cmd) {
			//roll dice and make move 
			case 'r': {
			if(currPlayer->isinDebt()){
				cout << "You Need To Pay First." << endl;
				break;
			}
			if(currPlayer->isOnTurn()) {
				int d1, d2;
				if(Test) {
					try{
					    cout << "Input two numbers to move: " << endl;
						cin >> d1;
						cin >> d2;
						testIn = true;
						currPlayer->Move(d1+d2);
					} catch (ios::failure&) {
						cin.ignore();
						cin.clear();
					}
				}
				//roll dice
				if(!testIn){
					int rollNum = 1;
					d->roll();
					cout << "Dice 1: " << d->getD1() << " Dice 2: " << d->getD2() << endl;
					while(d->isDouble() && rollNum < 3) {
						rollNum ++;
						sleep(1);
						d->roll();
						cout<<"You've Rolled Another Double!" << endl;
						cout << "Dice 1: " << d->getD1() << " Dice 2: " << d->getD2() << endl;
					}
					if(rollNum == 3) {
						currPlayer->gtTims();
						currPlayer->setOnTurn(false);
					} else {
					//make move
					currPlayer->Move(d->getSum());
					}
				}
				
				//take action
				Cell* currCell = GB->getCell(currPlayer->getPos());
				currCell->landOn(currPlayer);
				if(currPlayer->fromSLC()) {
				    currCell = GB->getCell(currPlayer->getPos());
				    currCell->landOn(currPlayer);
				    currPlayer->outSLC();
				}
				currPlayer->setOnTurn(false);
			} else {
				cout << "You Cannot Roll." << endl;
			}
			}
			GB->drawBoard();
			break;

			//next 
			case 'n':{
			if(currPlayer->isinDebt()) {
				cout << "You Need To Pay First." << endl;
				break; 
			}
			count++;
			if(count > GB->getNumPlayer()) {count = 1;}
			currPlayer = GB->getInxPlayer(count);
			if(currPlayer->isBankrupted()) {
				numPlayer--;
				GB->setNumPlayer(numPlayer);
				GB->removePlayer(currPlayer);
				currPlayer = GB->getInxPlayer(count);
			}
			currPlayer->setOnTurn(true);
			}
			GB->drawBoard();
			break;

			//trade properties
			case 't': {
			string name, give, receive;
			try{
				cin >> name >> give >> receive;
			} catch (ios::failure&) {
				cin.clear();
				cin.ignore();
				cout << "Incorrect Input." << endl;
				break;
			}
			if(name == currPlayer->getName()) {
				cout << "You Cannot Do This" << endl;
				break;
			}
			Player* receiver = GB->findPlayer(name);
			if(receiver == nullptr) {
				cout << "This Player Does Not Exist." << endl;
				break;
			}
			currPlayer->trade(receiver, give, receive);
			}
			GB->drawBoard();
			break;

			//improve property
			case 'i': {
			string ImpProp, action;
			try {
				cin >> ImpProp >> action;
			} catch (ios::failure&) {
				cin.clear();
				cin.ignore();
				cout << "Incorrect Input." << endl;
				break;
			}
			Cell* temp = GB->findCell(ImpProp);
			if(temp->cType()==CellType::Non_Property) {
				cout << "Cannot Improve Non-Property." << endl;
				break;
			} 
			Property* p = static_cast<Property*> (temp);
			if(p->pType()!=PropertyType::AB) {
				cout << "Cannot Improve Residences & Gyms." << endl;
				break;
			}
			AB * ab = static_cast<AB*> (p);
			currPlayer->improve(ab, action);
			}
			GB->drawBoard();
			break;

			//mortgage property
			case 'm': {
			string mortProp;
			try{
				cin >> mortProp;
			} catch (ios::failure&) {
				cin.clear();
				cin.ignore();
				cout << "Incorrect Input." << endl;
				break;
			}
			Cell* temp2 = GB->findCell(mortProp);
			if(temp2->cType() != CellType::Property) {
				cout << "Cannot Mortgage Non-Property." << endl;
				break;
			}
			Property* p1 = static_cast<Property*> (temp2);
			currPlayer->mortgage(p1);
			}
			break;

			//unmortgage property
			case 'u': {
			string unMortProp;
			if(currPlayer->isinDebt()) {
				cout << "You Don't Have Money!" << endl;
				break;
			}
			try {
				cin >> unMortProp;
			} catch (ios::failure&) {
				cin.clear();
				cin.ignore();
				cout << "Incorrect Input." << endl;
				break;
			}
			Cell* temp3 = GB->findCell(unMortProp);
			if(temp3->cType() != CellType::Property) {
				cout << "Cannot Un-Mortgage Non-Property." << endl;
				break;
			}
			Property* p2 = static_cast<Property*> (temp3);
			currPlayer->unmortgage(p2);
			}
			break;		

			//display assets
			case 'a': {
			if(currPlayer->isinDebt()){
				cout << "You Need To Pay First." << endl;
			}
			currPlayer->displayAsset();
			}
			break;

			//display assets of every player
			case 'l': {
			if(currPlayer->isinDebt()){
				cout << "You Need To Pay First." << endl;
			}
			for(int i = 1; i <= numPlayer; ++i) {
				GB->getInxPlayer(i)->displayAsset();
			}
			}
			break;

			//save game
			case 's': {
			string saveFile;
			try {
				cin >> saveFile;
			} catch (ios::failure&) {
				cin.clear();
				cin.ignore();
				cout << "Invalid File Name." << endl;
			}
			ofstream file {saveFile};
			GB->saveGame(file);
			cout << "Exit Game? (Y/N)" << endl;
			string e;
			cin >> e;
			if(e == "Y") {
				exit = true;
			} else if (e == "N") {
				exit = false;
			} else {
				cout << "Invalid Input." << endl;
			}
			}
			break;

			//bankrupcy
			case 'b': {
			if(currPlayer->isinDebt()) {
				currPlayer->declareBankrupt();
			} else {
				cout << "You Still Have Money. Don't Give Up!" << endl;
			}
			}
			break;

			default:
			cout << "Invalid Command." << endl;
			break;
		}
	}
	cout << "Thank You For Playing Watopoly. See You Next Time!" << endl;
}
