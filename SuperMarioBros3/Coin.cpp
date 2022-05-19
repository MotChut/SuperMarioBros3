#include "Coin.h"
#include "Debug.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == COIN_STATE_NORMAL + 2)
	{
		y -= COIN_SPEED;
		s -= COIN_SPEED;
		if (abs(s) >= (float)COIN_MAX_S) {
			state = COIN_STATE_NORMAL + 3;
			s = 0;
		}
	}
	else if (state == COIN_STATE_NORMAL + 3)
	{
		y += COIN_SPEED;
		s += COIN_SPEED;
		if (abs(s) >= (float)COIN_MAX_S * 0.75)
			this->Delete();
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == COIN_STATE_NORMAL)
		animations->Get(ID_ANI_COIN)->Render(x, y);
	else 
		animations->Get(ID_ANI_COIN + 1)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}
