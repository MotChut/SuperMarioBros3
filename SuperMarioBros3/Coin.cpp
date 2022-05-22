#include "Coin.h"
#include "Debug.h"

void CCoin::OnNoCollision(DWORD dt)
{
	y -= vy;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;

	if (this->flyalbe && coin_type == 1) 
	{
		if (vy > COIN_MAX_SPEED) {	
			ay = -COIN_SPEED;
		}
		else if (vy < -COIN_MAX_SPEED) {
			this->Delete();
		}
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->coin_type == 0)
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
