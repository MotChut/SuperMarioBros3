#include "BonusItem.h"
#include "Debug.h"

void CBonusItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = ANI_MUSHROOM;

	switch (type)
	{
	case 0:
		ani = ANI_MUSHROOM;
		break;
	case 1:
		ani = ANI_FLOWER;
		break;
	case 2:
		ani = ANI_STAR;
		break;
	}

	animations->Get(ani)->Render(x, y);
}

void CBonusItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type > 2) type = 0;
	
	if (GetTickCount64() - time_start > RANDOM_TIME && isRandomzing == 1)
	{
		time_start = -1;
		type++;
		time_start = GetTickCount64();
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CBonusItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_GIFT_SIZE / 2;
	t = y - HUD_GIFT_SIZE / 2;
	r = l + HUD_GIFT_SIZE;
	b = t + HUD_GIFT_SIZE;
}
