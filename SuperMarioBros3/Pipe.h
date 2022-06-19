#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_PIPE 16000
#define ID_ANI_PIPE_BLACK 16001
#define PIPE_WIDTH 32
#define PIPE_BBOX_WIDTH 32
#define PIPE_BBOX_HEIGHT 32

class CPipe : public CGameObject {
protected:
	int type = 0;	//0: green, 1: black
public:
	CPipe(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
	int IsBlocking() { return 0; }
	int IsCollidable()
	{
		return 0;
	}
};