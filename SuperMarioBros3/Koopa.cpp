#include "Koopa.h"
#include "Game.h"
#include "Debug.h"

CKoopa::CKoopa(float x, float y, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPA_GRAVITY;
	this->type = type;
	shell_start = -1;
	SetState(KOOPA_STATE_WALKING);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_MOVING
		|| state == KOOPA_SHELL_TIMEOUT || state == KOOPA_SHELL_AWAKE)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else if (state == KOOPA_STATE_CARRIED)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT_SHELL;
	}
	else
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		top = y - KOOPA_BBOX_HEIGHT / 2;
		right = left + KOOPA_BBOX_WIDTH;
		bottom = top + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
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

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == KOOPA_STATE_AWAKE)
	{
		if (GetTickCount64() - shell_start > KOOPA_SHELL_TIMEOUT)
		{
			minusY_flag = true;
			y = y - (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
			SetState(KOOPA_STATE_WALKING);
			this->ay = KOOPA_GRAVITY;
			shell_start = -1;
		}
	}
	else if (state == KOOPA_STATE_SHELL_MOVING)
	{
		shell_start = -1;
	}
	else if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL + 1)
	{
		if (GetTickCount64() - shell_start > KOOPA_SHELL_AWAKE)
		{
			state = KOOPA_STATE_AWAKE;
		}
	}
	else if (state != KOOPA_STATE_SHELL && state != KOOPA_STATE_SHELL_MOVING)
	{
		if (vx > 0)
			state = KOOPA_STATE_WALKING + 1;
		else if (vx < 0)
			state = KOOPA_STATE_WALKING;
	}		

	if (state == KOOPA_STATE_CARRIED)
	{
		LPGAMEOBJECT player = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
		float pvx, pvy, px, py;
		player->GetSpeed(pvx, pvy);
		player->GetPosition(px, py);

		if (pvx > 0)
		{
			x = px + 14.0f;
			y = py - 4.0f;
		}
		else if (pvx < 0)
		{
			x = px - 14.0f;
			y = py - 4.0f;
		}
		else if (pvy != 0)
			y = py - 4.0f;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = -1;
	
	if (state == KOOPA_STATE_WALKING)
		aniId = ID_ANI_KOOPA_NORMAL_RED_WALKING_LEFT;
	else if (state == KOOPA_STATE_WALKING + 1)
		aniId = ID_ANI_KOOPA_NORMAL_RED_WALKING_RIGHT;


	if (type == 0 || type == 1) 
	{
		//aniId = ID_ANI_KOOPA_RED_SHELL;
	}
	else if (type == 2 || type == 3)
	{
		if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL_MOVING || state == KOOPA_STATE_CARRIED)
			aniId = ID_ANI_KOOPA_RED_SHELL;
		else if (state == KOOPA_STATE_AWAKE)
			aniId = ID_ANI_KOOPA_RED_SHELL_AWAKE;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_SHELL:
		vx = 0;
		vy = 0;
		ay = 0;
		shell_start = GetTickCount64();
		y -= 0.67f;
		DebugOut(L"1: %f \n", y);
		if (minusY_flag == true)
		{
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_SHELL) / 2;
			minusY_flag = false;
		}
		break;
	case KOOPA_STATE_AWAKE:
		shell_start = GetTickCount64();
		break;
	case KOOPA_STATE_SHELL_MOVING:
		vx = -KOOPA_SHELL_MOVING_SPEED * dir;
		break;
	case KOOPA_STATE_WALKING:
		vx = -KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_WALKING + 1:
		vx = KOOPA_WALKING_SPEED;
		break;
	}
}
