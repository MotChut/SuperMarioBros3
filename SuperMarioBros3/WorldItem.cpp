#include "WorldItem.h"
#include "Debug.h"

void CWorldItem::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int ani = -1;

	switch (type)
	{
	case 0:
		ani = ANI_NODE;
		break;
	case 1:
		ani = ANI_NODE_ONE;
		break;
	case 2:
		ani = ANI_NODE_TWO;
		break;
	case 3:
		ani = ANI_NODE_THREE;
		break;
	case 4:
		ani = ANI_NODE_FOUR;
		break;
	case 5:
		ani = ANI_NODE_FIVE;
		break;
	case 6:
		ani = ANI_NODE_SIX;
		break;
	case 7:
		ani = ANI_TREE;
		break;
	case 8:
		ani = ANI_NODE_TRANS;
		break;
	}

	animations->Get(ani)->Render(x, y);
}

void CWorldItem::Update(DWORD dt)
{
}


void CWorldItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - ITEM_WIDTH / 2;
	t = y - ITEM_HEIGHT / 2;
	r = l + ITEM_WIDTH;
	b = t + ITEM_HEIGHT;
}
