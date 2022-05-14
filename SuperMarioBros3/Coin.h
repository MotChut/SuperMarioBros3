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
#define COIN_SPEED	0.004f
#define COIN_MAX_HEIGHT	0.08f

class CCoin : public CGameObject {
protected: 
	float ay = COIN_GRAVITY;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnNoCollision(DWORD dt);
	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

	virtual int IsCollidable() { return 1; };
public:
	CCoin(float x, float y) : CGameObject(x, y) { state = COIN_STATE_NORMAL; }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	void SetState(int st) { this->state = st; }
};