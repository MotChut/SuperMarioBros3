#include "InfoHud.h"

InfoHud::InfoHud()
{
	coin = 0;
	life = 0;
	score = 0;
	bonusitem1 = 0;
	bonusitem2 = 0;
	bonusitem3 = 0;
	level = 0;
}

InfoHud::InfoHud(int c, int l, int s, int b1, int b2, int b3, int level)
{
	coin = c;
	life = l;
	score = s;
	bonusitem1 = b1;
	bonusitem2 = b2;
	bonusitem3 = b3;
	this->level = level;
}