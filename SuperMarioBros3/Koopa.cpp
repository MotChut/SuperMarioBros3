#include "Koopa.h"
#include "Goomba.h"
#include "Mushroom.h"
#include  "Leaf.h"
#include "QuestionBlock.h"
#include "TransparentBlock.h"
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
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CTransparentBlock*>(e->obj))
	{
		if (type == 2 && e->obj->GetState() != KOOPA_STATE_SHELL_MOVING) vx = -vx;
	}
		

	if (!e->obj->IsBlocking()) return;

	if ((type == 1 || type == 3) && e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		ay = -ay;
		
		if (e->ny < 0) isOnPlatform = true;
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopa::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	if (goomba->GetState() != GOOMBA_STATE_FLIPPED && (state == KOOPA_STATE_SHELL_MOVING || state == KOOPA_STATE_CARRIED))
	{
		if (state == KOOPA_STATE_CARRIED)
		{
			isFlipped = true;
			state = KOOPA_STATE_SHELL;
		}

		goomba->SetState(GOOMBA_STATE_FLIPPED);
	}
}

void CKoopa::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	if (state == KOOPA_STATE_SHELL_MOVING)
	{
		koopa->SetStateFlipped(true);
	}
}

void CKoopa::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* qblock = dynamic_cast <CQuestionBlock*> (e->obj);
	if (state != KOOPA_STATE_SHELL_MOVING) return;

	if (e->nx > 0)
	{
		if (qblock->GetBlockType() == 1)		//Mushroom
		{
			qblock->SetHasItem(false);
			float qblock_x, qblock_y;
			qblock->GetPosition(qblock_x, qblock_y);

			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			CQuestionBlock* newquestionblock = new CQuestionBlock(qblock_x, qblock_y);

			qblock->Delete();
			newquestionblock->SetPosition(qblock_x, qblock_y - QUESTIONBLOCK_OFFSET);


			CMushroom* newmushroom = new CMushroom(qblock_x, qblock_y - 32);
			newquestionblock->SetHasItem(false);

			thisscene->AddNewObject(newmushroom);
			thisscene->AddNewObject(newquestionblock);
		}
		else if (qblock->GetBlockType() == 2)		//Leaf
		{
			qblock->SetHasItem(false);
			float qblock_x, qblock_y;
			qblock->GetPosition(qblock_x, qblock_y);

			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();
			CQuestionBlock* newquestionblock = new CQuestionBlock(qblock_x, qblock_y);

			qblock->Delete();
			newquestionblock->SetPosition(qblock_x, qblock_y - QUESTIONBLOCK_OFFSET);


			CLeaf* newleaf = new CLeaf(qblock_x + 16, qblock_y - 32);
			newquestionblock->SetHasItem(false);

			thisscene->AddNewObject(newleaf);
			thisscene->AddNewObject(newquestionblock);
		}
	}
}

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (type == 1 || type == 3)
	{
		if (vy <= -KOOPA_JUMP_SPEED)
		{
			vy = 0;
			ay = -ay;
		}
	}
	
	if (isFlipped)
	{
		ax = 0;
		vx = 0;
		ay = KOOPA_GRAVITY;
	}
	else if (state == KOOPA_STATE_AWAKE)
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
	else if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_SHELL + 1 || state == KOOPA_STATE_CARRIED)
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

	isOnPlatform = false;
	//ay = KOOPA_GRAVITY;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopa::Render()
{
	int aniId = -1;
	
	switch (type)
	{
	case 0:				//Normal Green
		if (state == KOOPA_STATE_WALKING)
			aniId = ID_ANI_KOOPA_NORMAL_GREEN_WALKING_LEFT;
		else if (state == KOOPA_STATE_WALKING + 1)
			aniId = ID_ANI_KOOPA_NORMAL_GREEN_WALKING_RIGHT;
		break;
	case 1:
		if (state == KOOPA_STATE_WALKING)
			aniId = ID_ANI_KOOPA_FLY_GREEN_WALKING_LEFT;
		else if (state == KOOPA_STATE_WALKING + 1)
			aniId = ID_ANI_KOOPA_FLY_GREEN_WALKING_RIGHT;
		break;
		break;
	case 2:				//Normal Red
		if (state == KOOPA_STATE_WALKING)
			aniId = ID_ANI_KOOPA_NORMAL_RED_WALKING_LEFT;
		else if (state == KOOPA_STATE_WALKING + 1)
			aniId = ID_ANI_KOOPA_NORMAL_RED_WALKING_RIGHT;
		break;
	case 3:
		break;
	}
	


	//SHELL
	if (type == 0 || type == 1) 
	{
		if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_CARRIED)
			aniId = ID_ANI_KOOPA_GREEN_SHELL;
		else if (state == KOOPA_STATE_SHELL_MOVING)
			aniId = ID_ANI_KOOPA_GREEN_SHELL_MOVING;
		else if (state == KOOPA_STATE_AWAKE)
			aniId = ID_ANI_KOOPA_GREEN_SHELL_AWAKE;

		if (isFlipped)	aniId = ID_ANI_KOOPA_GREEN_SHELL_FLIPPED;
	}
	else if (type == 2 || type == 3)
	{
		if (state == KOOPA_STATE_SHELL || state == KOOPA_STATE_CARRIED)
			aniId = ID_ANI_KOOPA_RED_SHELL;
		else if (state == KOOPA_STATE_SHELL_MOVING)
			aniId = ID_ANI_KOOPA_RED_SHELL_MOVING;
		else if (state == KOOPA_STATE_AWAKE)
			aniId = ID_ANI_KOOPA_RED_SHELL_AWAKE;
	
		if (isFlipped)	aniId = ID_ANI_KOOPA_RED_SHELL_FLIPPED;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
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
		ay = KOOPA_GRAVITY;
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
