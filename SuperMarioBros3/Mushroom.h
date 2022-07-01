#pragma once

#include "GameObject.h"
#include "QuestionBlock.h"
#include "Platform.h"

#define ID_ANI_MUSHROOM 110000
#define ID_ANI_LIFE_UP	110001

#define	MUSHROOM_WIDTH 16
#define MUSHROOM_BBOX_WIDTH 14
#define MUSHROOM_BBOX_HEIGHT 14

#define MUSHROOM_SPEED	0.09f
#define MUSHROOM_GRAVITY 0.2f

class CMushroom : public CGameObject {
	int type = 0;	//0: mushroom, 1: life up
public:
	CMushroom(float x, float y, int type = 0);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	int GetType() { return type; }
};