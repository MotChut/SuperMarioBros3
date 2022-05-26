#include "Leaf.h"
#include "Debug.h"
#include "Platform.h"
CLeaf::CLeaf(float x, float y) :CGameObject(x, y)
{
	this->vx = 0;
	this->vy = LEAF_GRAVITY;
}

void CLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LEAF_BBOX_WIDTH / 2;
	top = y - LEAF_BBOX_HEIGHT / 2;
	right = left + LEAF_BBOX_WIDTH;
	bottom = top + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += LEAF_GRAVITY * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CLeaf::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_LEAF)->Render(x, y);
	RenderBoundingBox();
}

