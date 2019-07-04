#include "player.h"
#include "AB.h"


using namespace std;

//Constructor
Player::Player(string name, string n, Xwindow* w):
name{name}, n{n}, pos{0}, otherNum{0}, rimNum{0}, cash{1500}, asset{1500}, ownedNum{0},gymNum{0}, resNum{0}, 
bankrupt{false}, turnAtTim{0}, onTurn{false}, stuck{false}, ower{nullptr}, debt{false}, w{w}, SLC{false} {}
Player::~Player() {}

//Gym and Residence:
int Player::getGym(){
	return gymNum;
}
void Player::setGym(int n){
	gymNum = n;
}
int Player::getRes(){
	return resNum;
}
void Player::setRes(int n){
	resNum = n;
}
//Cash
int Player::getCash(){
	return cash;
}
void Player::setCash(int c){
	cash = c;
}
void Player::changeCash(int c){
	if(c >= 0){
		cash += c;
		asset += c;
		cout << "You Have Earned " << c << " Dollars!" << endl;
		return;
	}else{
		char r;
		int amount = -c;
		if(amount < cash) {
			cash += c;
			asset += c;
			cout << "You Have Lost " << amount << " Dollars!" << endl;
			return;
		}
		if(amount > asset)
			declareBankrupt();
		else{
			cout << "You Don't Have Enough Cash, But You Can Raise Money From Somewhere Else." << endl;
			cout << "Option 1: Declare Bankrupcy? (Y/N)" << endl;
			cin >> r;
			if(r == 'Y') {
				declareBankrupt();
			} 
			if (r == 'N') {
				debt = true;
				return;
			}
		}
	}
}
//Asset
int Player::getAsset(){
	return asset;
}
void Player::setAsset(int a){
	asset = a;
}
void Player::changeAsset(int a){
	asset += a;
}
void Player::displayAsset(){
	cout << "Player " << name << " has following assets:" << endl;
	cout << "Cash: " << cash << endl;
	cout << "Asset: " << asset << endl;
	cout << "Properties: ";
	if(ownedProp.size() == 0){
	    cout << "No properties found." << endl;
	}else{
	    for (int i = 0; i < ownedNum; ++i)
	    {
		    cout << ownedProp[i]->getName() << endl;
	    }
	}
}

//Move:
int Player::getPos(){
	return pos;
}
void Player::setPos(int i){
	pos = i;
}
bool Player:: fromSLC() {
    return SLC;
}
void Player::outSLC() {
    SLC = false;
}
void Player::Move(int n){
	if(n > 0) {
		for(int i = 0; i < n; ++i) {
			++pos;
			if(pos > 39) { pos = 0;}
			if(pos == 0) {
				asset+= 200;
				cash +=200;
			}
		}
	} else {
		for(int i = 0; i < -n; ++i) {
			--pos;
			if(pos < 0) {pos = 39;}
			if(pos == 0) {
				asset += 200;
				cash += 200;
			}
		}
	}
}

void Player::gtOSAP(){
	asset+=200;
	cash+=200;
	pos = 0;
}
//Rim Cups:
int Player::getRimCup(){//Number of RimCup
	return rimNum;
}
void Player::setRimCup(int r){
	rimNum = r;
}
void Player::changeRimCup(int r){
	rimNum += r;
}
//Name:
string Player::getN(){
	return n;
}
string Player::getName(){
	return name;
}
//Turn:
bool Player::isOnTurn(){
	return onTurn;
}
void Player::setOnTurn(bool onturn){
	onTurn = onturn;
}
//Tims:
bool Player::isStuck(){
	return stuck;
}
int Player::getTimTurn(){ //Get turns already in Tims
	return turnAtTim;
}
void Player::setTim(bool tim, int turn){
	stuck = tim;
	turnAtTim = turn;
}
void Player::gtTims(){
	pos = 10;
	turnAtTim = 1;
	stuck = true;
}
void Player::outTims(){
    srand(time(0));
	char command;
	int move;
	int d1 = rand()% 6+1;
	int d2 = rand()% 6+1;

	if(turnAtTim == 3){
		stuck = false;
		changeCash(-50);

		cout << "Player " << name << " is forced to go out of DC Tims Line now." << endl;
		cout << "We do not want to see you again!" <<endl;
	}
	cout << "Player " << name << " has thrown " << d1 << ", " << d2  << " at DC Tims Line." << endl;
	if(d1==d2){
		stuck = false;
		cout << "Player " << name << " is out of DC Tims Line now." << endl;
		cout << "We hope to see him/her again!" <<endl;
		move = d1+d2;
		Move(move);
		onTurn = false;
	}
	else{
		cout << "BAD LUCK." << endl;
	}
	if(rimNum != 0){
		cout << "Player " << name << ", " << "Do you want to use one RollUp the Rim Cup?(Y/N)" << endl;
		cin >> command;
		if(command == 'y' || command == 'Y'){
			rimNum -= 1;
			stuck = false;
			cout << "Player " << name << " is out of DC Tims Line now." << endl;
			cout << "We hope to see you again!" <<endl;
		}
	}
	cout << "Player " << name << ", " << "Do you want to pay $50 to get out of here?(Y/N)" << endl;
	cin >> command;
	if(command == 'y' || command == 'Y'){
		cash -= 50;
		asset -= 50;
		stuck = false;
		cout << "Player " << name << " is out of DC Tims Line now." << endl;
		cout << "We hope to see you again!" <<endl;
	}
	else if(command == 'n' || command == 'N'){
		cout << "Player " << name << " is a cheapskate." << endl;
		cout << "Player " << name << " stays for one more turn" << endl;
		turnAtTim += 1;
	}
}
//Bankrupt
bool Player::isBankrupted(){//done
	if(asset < 0)
		bankrupt = true;
	return bankrupt;
}
void Player::setBankrupt(bool b){//done
	bankrupt = b;
}
void Player::declareBankrupt(){
	bankrupt = true;
	if(getOwer() == nullptr){
		for (int i = 0; i < ownedNum; ++i)
		{
			Auction temp{ownedProp[i], otherNum};
			for(int i = 0; i < otherNum; ++i){
		    temp.addPlayer(otherPlayer[i]);
		    }
			temp.startAuc();
		}
	}
	else{
		for (auto i = ownedProp.begin(); i != ownedProp.end(); ++i)
		{
			ower->addProperty(*i);
			ownedProp.erase(i);
		}
	}
}
void Player::addProperty(Property* newProperty){
	ownedProp.emplace_back(newProperty);
	ownedNum++;
}

void Player::addPlayer(Player* newPlayer){
	otherPlayer.emplace_back(newPlayer);
}
void Player::setOtherNum(int n){
    otherNum = n;
}

void Player::buyProperty(Property* p){
	cout << "Buy " << p->getName() << " will cost you " << p->getCost() << endl;
	cout << "Do you want to puchase this property? (Y/N): ";
	string command;
	cin >> command;
	if(command == "Y" || command == "y"){
		addProperty(p);
		changeCash(-(p->getCost()));
		asset+=(p->getCost());
		p->setOwner(this);
	}
	else if(command == "N" || command == "n"){
		Auction temp{p,otherNum};
		for(int i = 0; i < otherNum; ++i){
		    temp.addPlayer(otherPlayer[i]);
		}
		temp.startAuc();
	}
	else{
		cout << "Speak human language plz." <<endl;
		buyProperty(p);
	}
}

void Player::removeProperty(Property* p){
	for(auto i = ownedProp.begin(); i != ownedProp.end(); ++i){
		if((*i)->getName() == p->getName()){
			ownedProp.erase(i);
		}
	}
}

Player* Player::getOtherPlayer(int index){ 
	if(index > otherNum) {
		cout << "Incorrect Other Player Index." << endl;
	}
	return otherPlayer[index];
}

void Player::mortgage(Property* p) { //done
	if(p->getOwner()->getName() != name) {
		cout << "Sorry, You Cannot Mortgage Other Player's Property." << endl;
		return;
	}
	if(!p->canMortgage()) {
		cout << "You Must Sell All Your Improvments First." << endl;
		return;
	}
	p->mortgage();
}

void Player::unmortgage(Property* p) { //done
	if(p->getOwner()->getName() != name) {
		cout << "Sorry, You Cannot Un-Mortgage Other Player's Property." << endl;
		return;
	}
	p->unMortgage();
}

bool Player::isinDebt(){
	return debt;
}

Player* Player::getOwer(){
	return ower;
}

void Player::setOwer(Player* p) {
	ower = p;
}
void Player::drawPlayer() {
	if(pos <= 10){
		w->drawString(550-(pos*50)-25, 750, n);
	}
	else if(pos >= 20 && pos <= 30){
		w->drawString((pos-19)*50-25,60,n);
	}
	else if(pos >= 11 && pos <= 19){
		w->drawString(25,(21-pos)*70-10,n);
	}
	else{
		w->drawString(525,(pos-29)*70-10,n);
	}
}

void Player::trade(Player* receiver, string give, string receive) {
	string response; //Yes or No
	bool isGivenCash = false;
	bool isReceiveCash = false;
	int g,r;
	Property* pgive;
	Property* preceive;
	if(give == "COLLECT OSAP" || give == "SLC" || give == "DC Tims Line" || give == "Goose Nesting" || give == "NEEDLES HALL" || give == "Go To Tims"|| receive == "COLLECT OSAP" || receive == "SLC" || receive == "DC Tims Line" || receive == "Goose Nesting" || receive == "NEEDLES HALL" || receive == "Go To Tims") {
		cout << "Cannot Trade Non-Property." << endl;
		return;
	}
	//Convert to Cash
	istringstream s1(give);
	istringstream s2(receive);
	if(s1 >> g){
		isGivenCash = true;
		if(g > getCash()){
			cout << "Sorry, You do not have enough cash to trade." <<endl;
			return;
		}
	}
	if(s2 >> r){
		isReceiveCash = true;
	}
    if(isGivenCash && isReceiveCash){
        cout << "Does not make any sense to trade cash." << endl;
        return;
    }
    else if(isGivenCash && !(isReceiveCash)){
    	//Given Cash
    	preceive = receiver->findProp(receive);
		if(preceive == nullptr) {
			cout << give << "(Received Property) Does Not Exist." << endl; 
			return;
		}
    }
    else if(!(isGivenCash) && isReceiveCash){
    	//Given Property
    	pgive = findProp(give);
    	if(pgive == nullptr) {
			cout << give << "(Given Property) Does Not Exist." << endl; 
			return;
		}
    }
    else if(!(isGivenCash) && !(isReceiveCash)){
    	//Exchange Property
    	pgive = findProp(give);
    	if(pgive == nullptr) {
			cout << give << "(Given Property) Does Not Exist." << endl; 
			return;
		}
		preceive = receiver->findProp(receive);
		if(preceive == nullptr) {
			cout << give << "(Received Property) Does Not Exist." << endl; 
			return;
		}
    }
	cout << "You Offer " << name << " " << give << "In Exchange For " << receive << endl;
	cout << receiver->getName() << "(Y/N):";
	while(true) {
		try {
			cin >> response;
			break;
		} catch (ios::failure&) {
			cin.ignore();
			cin.clear();
			cout << "Incorrect Input. Please Re-Enter:" << endl;
		}
	}
	if(response == "Y" || response == "y") {
		if(!isGivenCash && !isReceiveCash){
			cout << receiver->getName() << " Accepcts Your Offer." << endl;
			pgive->changeOwner(receiver);
			preceive->changeOwner(this);
		}
		else if(!isGivenCash){
			cout << receiver->getName() << " Accepcts Your Offer." << endl;
			pgive->changeOwner(receiver);
			receiver->changeCash(-r);
			changeCash(r);
		}
		else{
			cout << receiver->getName() << " Accepcts Your Offer." << endl;
			preceive->changeOwner(this);
			changeCash(-g);
			receiver->changeCash(g);
		}
		return;
	}
	else{
		cout << receiver->getName() << " Denied Your Offer." << endl;
		cout << "LOL." << endl;
		return;
	}
}

Property* Player::findProp(string name) {
    for(int i = 0; i < ownedNum; ++i) {
            if(ownedProp[i]->getName() == name){
                return ownedProp[i];
            }
        }
    cout << "Cannot find property." << endl;
    return nullptr;
}

void Player::improve(AB* ab, string action){
	if(name != ab->getOwner()->getName()) {
		cout << "Sorry, You Are Not The Owner." << endl;
		return;
	}
	if(!(ab->isMonopoly())) {
		cout << "Sorry, You Don't Have Monopoly." << endl;
		return;
	}
	if(action == "buy") {
		if(debt){
			cout << "Cannot Buy Anymore." << endl;
			return;
		}
		ab->setImpLevel(ab->getImpLevel()+1);
	} else if (action == "sell") {
		ab->setImpLevel(ab->getImpLevel()-1);
	}
}
