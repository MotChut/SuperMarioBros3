#pragma once
#include "GameObject.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.04f


#define KOOPA_BBOX_WIDTH 16
#define KOOPA_BBOX_HEIGHT 24
#define KOOPA_BBOX_HEIGHT_SHELL 14

#define KOOPA_SHELL_TIMEOUT 500

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_SHELL 200

#define ID_ANI_KOOPA_WALKING 90010
#define ID_ANI_KOOPA_SHELL	90020
#define ID_ANI_KOOPA_SHELL_WAKE 90030

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int type;		// 0: green normal, 1: green fly, 2: red normal, 3: red fly

	ULONGLONG shell_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CKoopa(float x, float y, int type = 0);
	virtual void SetState(int state);
};