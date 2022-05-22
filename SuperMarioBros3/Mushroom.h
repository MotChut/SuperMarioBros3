#pragma once

#include "GameObject.h"

#define ID_ANI_MUSHROOM 110000
#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 16
#define MUSHROOM_APPEAR_SPEED	0.2f
#define MUSHROOM_SPEED	0.2f
#define MUSHROOM_GRAVITY 0.4f

class CMushroom : public CGameObject {
protected:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
public:
	CMushroom(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt) {}
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};