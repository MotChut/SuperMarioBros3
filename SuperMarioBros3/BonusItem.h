#pragma once

#include "GameObject.h"

#define ANI_MUSHROOM	250030
#define ANI_FLOWER	250040
#define ANI_STAR	250050

#define HUD_GIFT_SIZE	16

#define RANDOM_TIME	100

class CBonusItem : public CGameObject {
protected:
	int type;					//0: mush, 1: flow, 2: star
	int isRandomzing;
	ULONGLONG time_start;
public:
	CBonusItem(float x, float y, int type = 0) : CGameObject(x, y) { this->type = type; time_start = GetTickCount64(); isRandomzing = 1; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	int GetType() { return type; }
	int GetRanState() { return isRandomzing; }
	void SetRanState(int st) { isRandomzing = st; }
};