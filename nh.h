#ifndef __NH_H__
#define __NH_H__

#include <iostream>
#include "cell.h"
#include "player.h"

extern int totalRim;
class NH : public Cell{
public:
	NH(std::string name, Xwindow* w);
	void landOn(Player* p);
	CellType cType() override;
	void draw(int x,  int y, int color) override;
};

#endif
