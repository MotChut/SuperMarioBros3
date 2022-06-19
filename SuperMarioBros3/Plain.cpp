#include "Plain.h"

CPlain::CPlain(float x, float y, int type) :CGameObject(x, y)
{
	this->type = type;
	base_y = y;
	shoot_start = -1;
	isShooting = false;
	dir = -1;
}

void CPlain::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (type == 0)
	{
		left = x - PLAIN_BBOX_WIDTH / 2;
		top = y - PLAIN_BBOX_HEIGHT / 2;
		right = left + PLAIN_BBOX_WIDTH;
		bottom = top + PLAIN_BBOX_HEIGHT;
	}
	else if (type == 1)
	{

	}
}

void CPlain::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}

void CPlain::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
	LPGAMEOBJECT player = thisscene->GetPlayer();
	
	float px, py;
	player->GetPosition(px, py);

	if (abs(x - px) < DETECTZONE)
	{
		if (x - px <= 0) dir = 1; else dir = -1;
		shoot_start = GetTickCount64();
	}

	if (GetTickCount64() - shoot_start > SHOOT_TIME)
	{

	}
}


void CPlain::Render()
{
	int aniId = NULL;

	switch (type)
	{
	case 0:
		if (dir == -1)
		{
			if (isShooting)
				aniId = ID_ANI_PLAIN_SHOOTING_LEFT;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_LEFT;
		}
		else
		{
			if (isShooting)
				aniId = ID_ANI_PLAIN_SHOOTING_RIGHT;
			else
				aniId = ID_ANI_PLAIN_SHOOTING_MOVING_RIGHT;
		}
		break;
	case 1:
		
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

