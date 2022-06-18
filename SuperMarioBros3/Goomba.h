#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_JUMP_SPEED	0.6f

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 12
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_BBOX_WIDTH_RED 16
#define GOOMBA_BBOX_HEIGHT_RED 14
#define GOOMBA_BBOX_HEIGHT_DIE_RED 5

#define GOOMBA_BBOX_WIDTH_RED_FLY 16
#define GOOMBA_BBOX_HEIGHT_RED_FLY 15

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_JUMP_TIMEOUT 2000

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLIPPED	300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001
#define ID_ANI_GOOMBA_FLIP 5002
#define ID_ANI_GOOMBA_WALKING_RED	5100
#define ID_ANI_GOOMBA_DIE_RED	5101
#define ID_ANI_GOOMBA_FLIP_RED	5102
#define ID_ANI_GOOMBA_WAKING_RED_WING	5200

class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;			//0: normal, 1: red, 2: red wing
	bool jumpable = true;

	ULONGLONG die_start;
	ULONGLONG jump_start;
	BOOLEAN isOnPlatform = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return (state != GOOMBA_STATE_FLIPPED); };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);
	virtual int GetType() { return type; }
	virtual void SetType(int level) { type = level; }
};