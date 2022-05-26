#pragma once

#include "GameObject.h"
#include "QuestionBlock.h"

#define ID_ANI_LEAF 120000
#define	LEAF_WIDTH 16
#define LEAF_BBOX_WIDTH 16
#define LEAF_BBOX_HEIGHT 14
#define LEAF_GRAVITY 0.03f

class CLeaf : public CGameObject
{
public:
	CLeaf(float x, float y);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual int IsBlocking() { return 0; }
	virtual int IsCollidable() { return 1; };
};