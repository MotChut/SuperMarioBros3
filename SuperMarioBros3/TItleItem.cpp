#include "TitleItem.h"
#include "Debug.h"

void CTitleItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = -1;

	switch (type)
	{
	case 0:
		ani = ANI_TITLE;
		break;
	case 1:
		ani = ANI_CURSOR;
		break;
	case 2:
		ani = ANI_VERSION;
		break;
	}

	animations->Get(ani)->Render(x, y);
}

void CTitleItem::Update(DWORD dt)
{
}


void CTitleItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (type == 0)
	{
		l = x - TITLE_ITEM_WIDTH / 2;
		t = y - TITLE_ITEM_HEIGHT / 2;
		r = l + TITLE_ITEM_WIDTH;
		b = t + TITLE_ITEM_HEIGHT;
	}
	else if (type == 1)
	{
		l = x - CURSOR_WIDTH / 2;
		t = y - CURSOR_HEIGHT / 2;
		r = l + CURSOR_WIDTH;
		b = t + CURSOR_HEIGHT;
	}
	else if (type == 2)
	{
		l = x - VERSION_WIDTH / 2;
		t = y - VERSION_HEIGHT / 2;
		r = l + VERSION_WIDTH;
		b = t + VERSION_HEIGHT;
	}
}
