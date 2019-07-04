#ifndef __SLC_H__
#define __SLC_H__

#include <iostream>
#include "cell.h"
#include "player.h"

extern int totalRim;
class SLC : public Cell{
public:
	SLC(std::string name, Xwindow* w);
	void landOn(Player* p);
	CellType cType() override;
	void draw(int x, int y, int color) override;
};

#endif
