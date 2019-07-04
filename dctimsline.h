#ifndef __DCTIMSLINE_H__
#define __DCTIMSLINE_H__

#include <iostream>
#include <string>
#include "cell.h"

class Tim : public Cell{
public:
	Tim(std::string name, Xwindow* w);
	void landOn(Player* p);
	CellType cType() override;
	void draw(int x, int y, int color) override;
};

#endif
