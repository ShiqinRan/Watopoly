#include <iostream>
#include "gameboard.h"

//need more include 

using namespace std;

Gameboard::Gameboard(Xwindow *w): boardSize{40}, playernum{0}, dice{nullptr}, w{w} {}

Gameboard::~Gameboard() {
	for(int i = 0; i < boardSize; ++i) {
		delete theBoard[i];
	}
	for(int i =0; i < playernum; ++i) {
		delete Players[i];
	}
	theBoard.clear();
	Players.clear();
}

void Gameboard::saveGame(ofstream& out) {
//save numplayers
	out << getNumPlayer() << endl;
//save players pos, name, timcup, char and money
	for(int i=0; i < playernum; ++i) {
		out << Players[i]->getName() << " " <<Players[i]->getN() << " ";
		out << Players[i]->getRimCup() << " " << Players[i]->getCash() << " " << Players[i]->getPos();
		if(Players[i]->getPos()==10) {
			if(Players[i]->isStuck()) {
				out << "1 " << Players[i]->getTimTurn();
			}
			else {
				out << "0";
			}
		}
		out << endl;
	}
//save each cell, its owner and its improvements
	for(int i=0; i < boardSize; ++i) {
		if(i == 0 || i == 10 || i == 20 || i == 30 || i == 4 || i == 38) continue;
		if(theBoard[i]->getName() == "SLC" || theBoard[i]->getName() == "NeedlesHall") continue;
		out << theBoard[i]->getName() << " ";
		if(static_cast<Property*> (theBoard[i]) ->isOwned()) {
			out << static_cast<Property*>(theBoard[i])->getOwner()->getName() << " ";
		
		} else { 
			out << "BANK ";
		}
		if(theBoard[i]->getName() == "MKV" || theBoard[i]->getName() == "UWP" || theBoard[i]->getName() == "V1" || theBoard[i]->getName() == "REV" ||theBoard[i]->getName() == "PAC" || theBoard[i]->getName() == "CLV") 
		{	out << "0 "<< endl;

		} else if (static_cast<Property*>(theBoard[i])->isMortgaged()) {
			out << "-1 "<<  endl; }

		else {
			out << static_cast<AB*>(theBoard[i])->getImpLevel() << endl;
		}
	}
}

void Gameboard::loadGame(ifstream& in) {
	in >> playernum;
//load Players
	string name;
	string c;
	int rimcup, cash, pos;
	Player* p;
	for(int i = 0; i < playernum; ++i) {
		in >> name;
		in >> c;
		in >> rimcup >> cash >> pos;
		p = new Player(name, c, w);
		p->setRimCup(rimcup);
		p->setCash(cash);
		p->setPos(pos);
		if(pos == 10) {
			int tim;
			in >> tim;
			if(tim == 1) {
				int turn;
				in >> turn;
				p->setTim(true, turn); //set how many turns player has been in DC Time Line
			}
		}
		else {
			p->setTim(false, 0);
		}
		Players.emplace_back(p);
	}

	string cname;
	string owner;
	int imp;
//load Cells, init in main
	for(int i = 0; i < boardSize; ++i) {
		in >> cname;
		in >> owner;
		if(theBoard[i]->getName() == cname) {
			if(owner != "BANK") {
				Player* p = findPlayer(owner);
				Property* temp = static_cast<Property*>(theBoard[i]);
				temp->setOwner(p); 
				p->addProperty(temp);
			}
			if(imp == -1) {
				static_cast<Property*>(theBoard[i])->setMortgage(true);
			} else if(imp > 0){
				static_cast<AB*>(theBoard[i])->setImpLevel(imp);
				static_cast<AB*>(theBoard[i])->setMonopoly();
			}				
		}
	}
}

void Gameboard::init() {
//------------Cell initialization-------------
		//OSAP
		Cell* osap = new OSAP{"OSAP", w};				//need ctor
		theBoard.emplace_back(osap);
		//AL
		int ALTuit[6] = {2, 10, 30, 90, 160, 250};
		Cell* AL = new AB {40, 50, "AL", "Arts1", ALTuit, w};
		theBoard.emplace_back(AL);
		//SLC1
		Cell* slc1 = new SLC {"SLC", w};			//need ctor
		theBoard.emplace_back(slc1);
		//ML
		int MLTuit[6] = {4, 20, 60, 180, 320, 450};
		Cell* ML = new AB {60, 50, "ML", "Arts1", MLTuit, w};
		theBoard.emplace_back(ML);
		//TUITION
		Cell* tuition = new Tuition {"TUITION", w};		//need ctor
		theBoard.emplace_back(tuition);
		//MKV
		Cell* MKV = new Residence {200, "MKV", w};
		theBoard.emplace_back(MKV);
		//ECH
		int ECHTuit[6] = {6, 30, 90, 270, 400, 550};
		Cell* ECH = new AB {100, 50, "ECH", "Arts2", ECHTuit, w};
		theBoard.emplace_back(ECH);
		//Needles Hall1
		Cell* nh1 = new NH {"NH",w};			// need ctor
		theBoard.emplace_back(nh1);
		//PAS
		int PASTuit[6] = {6, 30, 90, 270, 400, 550};
		Cell* PAS = new AB {100, 50, "PAS", "Arts2", PASTuit, w};
		theBoard.emplace_back(PAS);
		//HH
		int HHTuit[6] = {8, 40, 100, 300, 450, 600};
		Cell* HH = new AB {120, 50, "HH", "Arts2", HHTuit, w};
		theBoard.emplace_back(HH);
		// DC Time Line
		Cell* dctl = new Tim {"DCTL",w}; // need ctor
		theBoard.emplace_back(dctl);
		//RCH
		int RCHTuit[6] = {10, 50, 150, 450, 625, 750};
		Cell* RCH = new AB {140, 100, "RCH", "Eng", RCHTuit, w};
		theBoard.emplace_back(RCH);
		//PAC
		Dice* d = new Dice(); //remember to delete the dice
		Cell* PAC = new Gym {150, "PAC", d, w};
		theBoard.emplace_back(PAC);
		//DWE
		int DWETuit[6] = {10, 50, 150, 450, 625, 750};
		Cell* DWE = new AB {140, 100, "DWE", "Eng", DWETuit, w};
		theBoard.emplace_back(DWE);
		//CPH
		int CPHTuit[6] = {12, 60, 180, 500, 700, 900};
		Cell* CPH = new AB {160, 100, "CPH","Eng", CPHTuit, w};
		theBoard.emplace_back(CPH);
		//UWP
		Cell* UWP = new Residence {200, "UWP", w};
		theBoard.emplace_back(UWP);
		//LHI
		int LHITuit[6] = {14, 70, 200, 550, 750,950};
		Cell* LHI = new AB {180, 100, "LHI", "Health", LHITuit, w};
		theBoard.emplace_back(LHI);
		//SLC2
		Cell* slc2 = new SLC {"SLC", w};
		theBoard.emplace_back(slc2);
		//BMH
		int BMHTuit[6] = {14, 70, 200, 550, 750, 950};
		Cell* BMH = new AB {180, 100, "BMH", "Health", BMHTuit, w};
		theBoard.emplace_back(BMH);
		//OPT
		int OPTTuit[6] = {16, 80, 220, 600, 800, 1000};
		Cell* OPT = new AB {200, 100, "OPT", "Health", OPTTuit, w};
		theBoard.emplace_back(OPT);
		//Goose Nesting
		Cell* GN = new Goose {"Goose Nesting", w};			//need ctor
		theBoard.emplace_back(GN);
		//EV1
		int EV1Tuit[6] = {18, 90, 250, 700, 875, 1050};
		Cell* EV1 = new AB {220, 150, "EV1","ENV", EV1Tuit, w};
		theBoard.emplace_back(EV1);
		//Needles Hall 2
		Cell* nh2 = new NH {"NH",w};			// need ctor
		theBoard.emplace_back(nh2);
		//EV2
		int EV2Tuit[6] = {18, 90, 250, 700, 875, 1050};
		Cell* EV2 = new AB {220, 150, "EV2", "ENV", EV2Tuit, w};
		theBoard.emplace_back(EV2);
		//EV3
		int EV3Tuit[6] = {20, 100, 300, 750, 925, 1100};
		Cell* EV3 = new AB {240, 150, "EV3", "ENV", EV3Tuit, w};
		theBoard.emplace_back(EV3);
		//V1
		Cell* V1 = new Residence {200, "V1", w};
		theBoard.emplace_back(V1);
		//PHYS
		int PHYSTuit[6] = {22, 110, 330, 800, 975, 1150};
		Cell* PHYS = new AB {260, 150, "PHYS", "Sci1", PHYSTuit, w};
		theBoard.emplace_back(PHYS);
		//B1
		int B1Tuit[6] = {22, 110, 330, 800, 975, 1150};
		Cell* B1 = new AB {260, 150, "B1", "Sci1", B1Tuit, w};
		theBoard.emplace_back(B1);
		//CIF
		Cell* CIF = new Gym {200, "CIF",d, w};
		theBoard.emplace_back(CIF);
		//B2
		int B2Tuit[6] = {24, 120, 360, 850, 1025, 1200};
		Cell* B2 = new AB {280, 150, "B2", "Sci1", B2Tuit, w};
		theBoard.emplace_back(B2);
		//Go To Tims
		Cell* GT = new gtTims{"Go to Tims",w};		//need ctor
		theBoard.emplace_back(GT);
		//EIT
		int EITTuit[6] = {26, 130, 390, 900, 1100, 1275};
		Cell* EIT = new AB {300, 200, "EIT", "Sci2", EITTuit, w};              
		theBoard.emplace_back(EIT);
		//ESC
		int ESCTuit[6] = {26, 130, 390, 900, 1100, 1275};
		Cell* ESC = new AB {300, 200, "ESC", "Sci2", ESCTuit, w};
		theBoard.emplace_back(ESC);
		//SLC3
		Cell* slc3 = new SLC {"SLC", w};		//need ctor
		theBoard.emplace_back(slc3);
		//C2
		int C2Tuit[6] = {28, 150, 450, 1000, 1200, 1400};
		Cell* C2 = new AB {320, 200, "C2", "Scie2", C2Tuit, w};
		theBoard.emplace_back(C2);
		//REV
		Cell* Rev = new Residence {200, "REV", w};
		theBoard.emplace_back(Rev);
		//Needles Hall
		Cell* nh3 = new NH {"NH",w};			// need ctor
		theBoard.emplace_back(nh3);
		//MC
		int MCTuit[6] = {35, 175, 500, 1100, 1300, 1500};
		Cell* MC = new AB {350, 200, "MC", "Math", MCTuit, w};
		theBoard.emplace_back(MC);
		//COOP
		Cell* coop = new CoopFee {"COOP FEE", w};			//need ctor
		theBoard.emplace_back(coop);
		//DC
		int DCTuit[6] = {50, 200, 600, 1400, 1700, 2000};
		Cell* DC = new AB {400, 200, "DC", "Math", DCTuit, w};
		theBoard.emplace_back(DC);
}

void Gameboard::setNumPlayer(int n) {
	playernum = n;
}

void Gameboard::addPlayer(Player* p) {
	Players.emplace_back(p);
}

void Gameboard::removePlayer(Player* p) {
	for(auto i = Players.begin(); i < Players.end(); ++i) {
		if((*i)->getName() == p->getName()) {
			delete *i;
			Players.erase(i);
		}
	}
	playernum--;
}

Player* Gameboard::findPlayer(string name) {
	int pos = -1;
	for(int i = 0; i < playernum; ++i) {
		if(name == Players[i]->getName()) {
			pos = i;
		}
	}
	if(pos == -1) {
		return nullptr;
	}
	return Players[pos];
}

int Gameboard::getNumPlayer() {return playernum;}

Player* Gameboard::getInxPlayer(int inx) {
	return Players[inx-1];
}

Cell* Gameboard::getCell(int inx) {
	return theBoard[inx];
}

Cell* Gameboard::findCell(string name) {
	int pos = -1;
	for(int i = 0; i < boardSize; ++i) {
		if(theBoard[i]->getName() == name) {
			pos = i;
		}
	}
	if(pos == -1) {
		return nullptr;
	}
	return theBoard[pos];
}

void Gameboard::setDice(Dice* dice) {
	dice = dice;
}

void Gameboard::linkPlayer() {
	int otherNum = playernum-1;
	for(int i = 0; i < playernum; ++i) {
		int currplayer = i;
		Players[i]->setOtherNum(otherNum);
		for(int j = 0; j < playernum; ++j) {
			int otherPlayer = j;
			if(i != j) {
				Players[i]->addPlayer(Players[j]);
			}
		}
	}
}

void Gameboard::drawBoard() {
	theBoard[0]->draw(10, 10, 6); //osap
	//theBoard[1]->draw(9, 10, 4); //AL
	w->fillRectangle(9*50, 10*70, 50, 20, 0);
        w->fillRectangle(9*50, 10*70+20, 50, 50, 4);
	w->drawString(9*50, 10*70+35, "AL");
	theBoard[2]->draw(8, 10, 7); //SLC
	//theBoard[3]->draw(7, 10, 4); //ML
	w->fillRectangle(7*50, 10*70, 50, 20, 0);
        w->fillRectangle(7*50, 10*70+20, 50, 50, 4);
	w->drawString(7*50, 10*70+35, "ML");
	theBoard[4]->draw(6, 10, 7); //TUITION
	//theBoard[5]->draw(5, 10, 8); //MKV
	w->fillRectangle(5*50, 10*70, 50, 70, 8);
        w->drawString(5*50, 10*70+15, "MKV");
	//theBoard[6]->draw(4, 10, 4); //ECH
	w->fillRectangle(4*50, 10*70, 50, 20, 0);
        w->fillRectangle(4*50, 10*70+20, 50, 50, 4);
	w->drawString(4*50, 10*70+35, "ECH");
	theBoard[7]->draw(3, 10, 7); //NEEDLES HALL
	//theBoard[8]->draw(2, 10, 4); //PAS
	w->fillRectangle(2*50, 10*70, 50, 20, 0);
        w->fillRectangle(2*50, 10*70+20, 50, 50, 4);
	w->drawString(2*50, 10*70+35, "PAS");
	//theBoard[9]->draw(1, 10, 4); //HH
	w->fillRectangle(1*50, 10*70, 50, 20, 0);
        w->fillRectangle(1*50, 10*70+20, 50, 50, 4);
	w->drawString(1*50, 10*70+35, "HH");
	theBoard[10]->draw(0, 10, 6); //DC TIMS LINE

	//theBoard[11]->draw(0, 9, 2); //RCH
	w->fillRectangle(0*50, 9*70, 50, 20, 0);
        w->fillRectangle(0*50, 9*70+20, 50, 50, 2);
	w->drawString(0*50, 9*70+35, "RCH");
	//theBoard[12]->draw(0, 8, 5); //PAC
	w->fillRectangle(0*50, 8*70, 50, 70, 5);
        w->drawString(0*50, 8*70+15, "PAC");
	//theBoard[13]->draw(0, 7, 2); //DWE
	w->fillRectangle(0*50, 7*70, 50, 20, 0);
        w->fillRectangle(0*50, 7*70+20, 50, 50, 2);
	w->drawString(0*50, 7*70+35, "DWE");
	//theBoard[14]->draw(0, 6, 2); //CPH
	w->fillRectangle(0*50, 6*70, 50, 20, 0);
        w->fillRectangle(0*50, 6*70+20, 50, 50, 2);
	w->drawString(0*50, 6*70+35, "CPH");
	//theBoard[15]->draw(0, 5, 8); //UWP
	w->fillRectangle(0*50, 5*70, 50, 70, 8);
        w->drawString(0*50, 5*70+15, "UWP");
	//theBoard[16]->draw(0, 4, 3); //LHI
	w->fillRectangle(0*50, 4*70, 50, 20, 0);
        w->fillRectangle(0*50, 4*70+20, 50, 50, 3);
	w->drawString(0*50, 4*70+35, "LHI");
	theBoard[17]->draw(0, 3, 7); //SLC
	//theBoard[18]->draw(0, 2, 3); //BMH
	w->fillRectangle(0*50, 2*70, 50, 20, 0);
        w->fillRectangle(0*50, 2*70+20, 50, 50, 3);
	w->drawString(0*50, 2*70+35, "BMH");
	//theBoard[19]->draw(0, 1, 3); //OPT
	w->fillRectangle(0*50, 1*70, 50, 20, 0);
        w->fillRectangle(0*50, 1*70+20, 50, 50, 3);
	w->drawString(0*50, 1*70+35, "OPT");
	theBoard[20]->draw(0, 0, 7); //Goose

	//theBoard[21]->draw(1, 0, 5); //EV1
	w->fillRectangle(1*50, 0*70, 50, 20, 0);
        w->fillRectangle(1*50, 0*70+20, 50, 50, 5);
	w->drawString(1*50, 0*70+35, "EV1");
	theBoard[22]->draw(2, 0, 7); //NEEDLS HALL
	//theBoard[23]->draw(3, 0, 5); //EV2
	w->fillRectangle(3*50, 0*70, 50, 20, 0);
        w->fillRectangle(3*50, 0*70+20, 50, 50, 5);
	w->drawString(3*50, 0*70+35, "EV2");
	//theBoard[24]->draw(4, 0, 5); //EV3
	w->fillRectangle(4*50, 0*70, 50, 20, 0);
        w->fillRectangle(4*50, 0*70+20, 50, 50, 5);
	w->drawString(4*50, 0*70+35, "EV3");
	//theBoard[25]->draw(5, 0, 8); //V1
	w->fillRectangle(5*50, 0*70, 50, 70, 8);
        w->drawString(5*50, 0*70+35, "V1");
	//theBoard[26]->draw(6, 0, 9); //PHYS
	w->fillRectangle(6*50, 0*70, 50, 20, 0);
        w->fillRectangle(6*50, 0*70+20, 50, 50, 9);
	w->drawString(6*50, 0*70+35, "PHYS");
	//theBoard[27]->draw(7, 0, 9); //B1
	w->fillRectangle(7*50, 0*70, 50, 20, 0);
        w->fillRectangle(7*50, 0*70+20, 50, 50, 9);
	w->drawString(7*50, 0*70+35, "B1");
	//theBoard[28]->draw(8, 0, 5); //CIF
	w->fillRectangle(8*50, 0*70, 50, 70, 5);
        w->drawString(8*50, 0*70+35, "CIF");
	//theBoard[29]->draw(9, 0, 9); //B2
	w->fillRectangle(9*50, 0*70, 50, 20, 0);
        w->fillRectangle(9*50, 0*70+20, 50, 50, 9);
	w->drawString(9*50, 0*70+35, "B2");
	theBoard[30]->draw(10, 0, 6); //GO TO TIMS

	//theBoard[31]->draw(10, 1, 9); //EIT
	w->fillRectangle(10*50, 1*70, 50, 20, 0);
        w->fillRectangle(10*50, 1*70+20, 50, 50, 9);
	w->drawString(10*50, 1*70+35, "EIT");
	//theBoard[32]->draw(10, 2, 9); //ESC
	w->fillRectangle(10*50, 2*70, 50, 20, 0);
        w->fillRectangle(10*50, 2*70+20, 50, 50, 9);
	w->drawString(10*50, 2*70+35, "ESC");
	theBoard[33]->draw(10, 3, 7); //SLC
	//theBoard[34]->draw(10, 4, 9); //C2
	w->fillRectangle(10*50, 4*70, 50, 20, 0);
        w->fillRectangle(10*50, 4*70+20, 50, 50, 9);
	w->drawString(10*50, 4*70+35, "C2");
	//theBoard[35]->draw(10, 5, 8); //REV
	w->fillRectangle(10*50, 5*70, 50, 70, 8);
        w->drawString(10*50, 5*70+15, "REV");
	theBoard[36]->draw(10, 6, 7); //NEEDLES HALL
	//theBoard[37]->draw(10, 7, 3); //mc
	w->fillRectangle(10*50, 7*70, 50, 20, 0);	
        w->fillRectangle(10*50, 7*70+20, 50, 50, 3);
	w->drawString(10*50, 7*70+35, "MC");
	theBoard[38]->draw(10, 8, 7); //COOP FEE
	//theBoard[39]->draw(10, 9, 3); //DC
	w->fillRectangle(10*50, 9*70, 50, 20, 0);
        w->fillRectangle(10*50, 9*70+20, 50, 50, 3);
	w->drawString(10*50, 9*70+35, "DC");

        for(int i = 0; i < playernum; ++i) {
                Players[i]->drawPlayer();
        }

}
