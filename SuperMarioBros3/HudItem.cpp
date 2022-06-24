#include "HudItem.h"

CHudItem::CHudItem(float x, float y, int type) : CGameObject(x, y)
{
	this->type = type;
}

void CHudItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (type)
	{
	case 0:
		
		break;
	case 1:
		
		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		
	case 6:
		
	case 7:
		
	case 8:
		
	case 9:
		
		break;
	case 10:
		
		break;

	case 11:
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CHudItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = -1;

	switch (type)
	{
	case 0:
		ani = ANI_ZERO;
		break;
	case 1:
		ani = ANI_ONE;
		break;
	case 2:
		ani = ANI_TWO;
		break;
	case 3:
		ani = ANI_THREE;
		break;
	case 4:
		ani = ANI_FOUR;
		break;
	case 5:
		ani = ANI_FIVE;
		break;
	case 6:
		ani = ANI_SIX;
		break;
	case 7:
		ani = ANI_SEVEN;
		break;
	case 8:
		ani = ANI_EIGHT;
		break;
	case 9:
		ani = ANI_NINE;
		break;
	case 10:
		ani = ANI_SPEED;
		break;
	case 11:
		ani = ANI_FLYABLE;
		break;
	case 12:
		break;
	case 13:
		break;
	case 14:
		break;
	}

	if (visible == 1)
		animations->Get(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CHudItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	switch (type)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
		l = x - HUD_ITEM_BBOX_WIDTH / 2;
		t = y - HUD_ITEM_BBOX_HEIGHT / 2;
		r = l + HUD_ITEM_BBOX_WIDTH;
		b = t + HUD_ITEM_BBOX_HEIGHT;
		break;
	case 11:
	case 12:
	case 13:
	case 14:
		l = x - HUD_GIFT_SIZE / 2;
		t = y - HUD_GIFT_SIZE / 2;
		r = l + HUD_GIFT_SIZE;
		b = t + HUD_GIFT_SIZE;
		break;
	case 15:
		break;
	}
}