#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 16
#define COIN_BBOX_WIDTH 16
#define COIN_BBOX_HEIGHT 16
#define COIN_SPEED	0.03f
#define COIN_MAX_SPEED	5


class CCoin : public CGameObject {
	int coin_type = 0;			// 0: normal, 1: in question block
	float ay = COIN_SPEED;
	bool flyalbe = false;
public:
	CCoin(float x, float y, int type = 0) : CGameObject(x, y) { this->coin_type = type; this->vy = 0; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void OnNoCollision(DWORD dt);
	virtual int GetCoinType() { return this->coin_type; }
	virtual void SetFlyable(bool state) { this->flyalbe = state; }
	virtual int IsBlocking() { return 0; }
};