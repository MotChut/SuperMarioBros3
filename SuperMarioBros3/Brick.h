#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK 10000
#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject {
protected:
	int type = 0;	//0: default, 1: contain mystery
public:
	CBrick(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
};