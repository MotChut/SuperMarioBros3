#include "Coin.h"
#include "Debug.h"

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (state == COIN_STATE_NORMAL + 2)
		y += vy;
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::OnNoCollision(DWORD dt)
{
	//DebugOut(L"This is coin!!!!!!!!!!!!!!!!!!!! \n");
	y += vy * dt;
}

//void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//
//}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == COIN_STATE_NORMAL)
		animations->Get(ID_ANI_COIN)->Render(x, y);
	else if (state == COIN_STATE_NORMAL + 1)
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

