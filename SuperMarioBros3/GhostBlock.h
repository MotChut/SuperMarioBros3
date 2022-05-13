#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_GHOSTBLOCK 90000
#define GHOSTBLOCK_WIDTH 16
#define GHOSTBLOCK_PASSABLE 91000

class CGhostBlock : public CGameObject {
public:
	CGhostBlock(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	virtual int IsBlocking();
	virtual void SetState(int st);
};