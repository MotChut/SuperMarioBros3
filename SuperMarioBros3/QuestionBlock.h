#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTIONBLOCK 100000
#define ID_ANI_QUESTIONBLOCK_STOP 100001

#define STATE_QUESTIONBLOCK_ACTIVE	1

#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

class CQuestionBlock : public CGameObject {
public:
	CQuestionBlock(float x, float y, int state = STATE_QUESTIONBLOCK_ACTIVE) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	
	virtual void SetState(int st);
};