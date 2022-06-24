#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "HudItem.h"

#define ANI_HUD	260000

#define HUD_BBOX_WIDTH	288
#define HUD_BBOX_HEIGHT	48

#define MARIO_RUNNING_SPEED		0.3f
#define MARIO_FLY_SPEED	0.12f

class CHud : public CGameObject {
protected:
	int speed;
	int flyable;
	int coin;
	int life; 
	int score;
	int time;

	ULONGLONG time_start;

	vector<LPHUDITEM> properties;	//0->5: speed, 6: flyable
									//7->8: coin, 9->10: life
									//11->17: score, 18->20: time
public:
	CHud(float x, float y, int speed, int flyable, int coin, int life, int score, int time);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void AddProperty(LPHUDITEM o) { properties.push_back(o); }
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }

	void SetFlyable(int st) { this->flyable = st; }
	void SetCoin(int coin) { this->coin = coin; }
	void SetLife(int life) { this->life = life; }
	void SetScore(int score) { this->score = score; }
};