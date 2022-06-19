#pragma once
#include "GameObject.h"

#define PLAIN_SPEED	0.002f

#define PLAIN_BBOX_WIDTH 16
#define PLAIN_BBOX_HEIGHT 24

#define DETECTZONE	80
#define SHOOT_TIME	3000

#define ID_ANI_PLAIN_SHOOTING_LEFT	5500
#define ID_ANI_PLAIN_SHOOTING_MOVING_LEFT 5600
#define ID_ANI_PLAIN_SHOOTING_RIGHT	5550
#define ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT	5650

class CPlain : public CGameObject
{
protected:
	int type;			//0: shooting, 1:  biting
	float base_y;
	int dir;			//-1: left, 1: right
	bool isShooting;
	ULONGLONG shoot_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsBlocking() { return 0; }

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPlain(float x, float y, int type);

	virtual int GetType() { return type; }
};