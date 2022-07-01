#pragma once

class InfoHud {
	int level;
	int coin;
	int life;
	int score;
	int bonusitem1;
	int bonusitem2;
	int bonusitem3;
public:
	InfoHud();
	InfoHud(int coin, int life, int score, int b1, int b2, int b3, int level);
	~InfoHud() {}
	
	int GetCoin() { return coin; }
	int GetLife() { return life; }
	int GetScore() { return score; }
	int GetB1() { return bonusitem1; }
	int GetB2() { return bonusitem2; }
	int GetB3() { return bonusitem3; }
	int GetLevel() { return level; }
};