#ifndef __DICE_H__
#define __DICE_H__
#include <cstdlib>
#include <ctime>

class Dice {
	int d1, d2;
	bool Double;
public:
	Dice();
	void roll();
	int getSum();
	bool isDouble();
	void clearDouble();
	int getD1();
	int getD2();
};

#endif
