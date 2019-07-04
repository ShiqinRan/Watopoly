#include <cstdlib>
#include <unistd.h>
#include "Dice.h"

Dice::Dice():d1{0}, d2{0}, Double{false}{}

void Dice::roll() {
	srand(time(0));
	d1 = rand()% 6+1;
	d2 = rand()% 6+1;
}

int Dice::getSum(){
	return d1+d2;
}

bool Dice::isDouble() {
	return d1 == d2;
}

void Dice::clearDouble() {
	Double = false;
}

int Dice::getD1() {
	return d1;
}

int Dice::getD2() {
	return d2;
}
