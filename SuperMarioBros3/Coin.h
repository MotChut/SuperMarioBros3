#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_COIN 11000
#define COIN_STATE_NORMAL	-1	// -1: normal, 0: in the block, 1: up, 2: down
#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16
#define COIN_GRAVITY	0.002f
#define COIN_SPEED	4
#define COIN_MAX_S	64

class CCoin : public CGameObject {
protected: 
	float ay = COIN_GRAVITY;
	float s = 0;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	//virtual void OnNoCollision(DWORD dt);
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
public:
	CCoin(float x, float y, int state = COIN_STATE_NORMAL) : CGameObject(x, y) { this->state = state; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int st) { this->state = st; }
};