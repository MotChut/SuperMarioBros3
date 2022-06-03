#pragma once

#include "GameObject.h"

#define ID_ANI_QUESTIONBLOCK 100000
#define ID_ANI_QUESTIONBLOCK_STOP 100001
#define QUESTIONBLOCK_OFFSET	8
#define QUESTIONBLOCK_GRAVITY	0.005f
#define QUESTIONBLOCK_WIDTH 16
#define QUESTIONBLOCK_BBOX_WIDTH 16
#define QUESTIONBLOCK_BBOX_HEIGHT 16

class CQuestionBlock : public CGameObject {
	float base_y;
	int block_type;				// 0: coin, 1: mushroom, 2: leaf, 3: mush/leaf
	bool hasItem = true;
public:
	CQuestionBlock(float x, float y, int type = 0) : CGameObject(x, y) { this->block_type = type; this->base_y = y; }
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void SetHasItem(bool state) { this->hasItem = state; }
	bool HasItem() { return this->hasItem; }
	int GetBlockType() { return this->block_type; }
};