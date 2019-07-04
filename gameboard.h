 #ifndef __GAMEBOARD_H__
 #define __GAMEBOARD_H__
 #include <iostream>
 #include <fstream>
 #include <vector>
	
 #include <string>
 #include "cell.h"
 #include "player.h"
 #include "coopfee.h"
 #include "AB.h"
 #include "property.h"
 #include "Residence.h"
 #include "Gym.h"
 #include "goose.h"
 #include "tuition.h"
 #include "osap.h"
 #include "slc.h"
 #include "Dice.h"
 #include "window.h"
 #include "auction.h"
 #include "nh.h"
 #include "gotoTims.h"
 #include "dctimsline.h"
 #include "player.h"
 
 //class Xwindow;
 
 class Gameboard {
 	std::vector<Cell*> theBoard; //the actual gameboard
 	std::vector<Player*> Players; // the players on gameboard
 	int boardSize; // size of the gameboard
 	int playernum; //number of players on board
 	Dice *dice;
 	Xwindow *w;
 public:
 	Gameboard(Xwindow* w);
 	~Gameboard();
 	void setDice (Dice* dice); // set the dice for gameboard
 	void loadGame(std::ifstream &in); //load game from file
 	void saveGame(std::ofstream &out); //save game from file 
 	void init(); // initialize the gameboard 
 	void setNumPlayer(int n);
 	void addPlayer(Player* p); //add a player to the board
 	void removePlayer(Player* p); //remove a player from the board
 	void linkPlayer(); //fill in the other player array in each player
 	Player* findPlayer(std::string name); //return the player with the name
 	Player* getInxPlayer(int inx);
 	int getNumPlayer(); //get the number of players on the board
 	Cell* getCell(int inx); // return the Cell in inx
 	Cell* findCell(std::string name); //return the Cell with name
 	void drawBoard(); // display the board
 };
 
 #endif
