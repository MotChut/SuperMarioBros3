#include "Mushroom.h"
#include "Debug.h"

CMushroom::CMushroom(float x, float y, int type) :CGameObject(x, y)
{
	this->vx = MUSHROOM_SPEED;
	this->vy = MUSHROOM_GRAVITY;
	this->type = type;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatform*>(e->obj))
	{
		CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);

		if (platform->getType() == 2) return;

		if (e->ny < 0)
		{
			y -= Push_Up_Platform;
			platform->SetState(-1);
		}
	}

	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	this->vy = MUSHROOM_GRAVITY;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CMushroom::Render()
{
	if (type == 0)
		CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM)->Render(x, y);
	else 
		CAnimations::GetInstance()->Get(ID_ANI_LIFE_UP)->Render(x, y);
	//RenderBoundingBox();
}

