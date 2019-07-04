#ifndef _GOTOTIMS_H_
#define _GOTOTIMS_H_

#include <iostream>
#include "cell.h"

class gtTims: public Cell{
public:
	gtTims(std::string name, Xwindow *w);
	~gtTims();
	void landOn(Player *p);
	CellType cType() override;
	void draw(int x, int y, int color) override;
};

#endif
