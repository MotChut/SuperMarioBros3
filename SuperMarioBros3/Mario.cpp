#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Koopa.h"
#include "Coin.h"
#include "Portal.h"
#include "Platform.h"
#include "QuestionBlock.h"
#include "Mushroom.h"
#include "Leaf.h"

#include "Collision.h"
#include "PlayScene.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx))	vx = maxVx;

	// Stop Mario leaving the left-edge of the screen
	if (x <= Left_Edge)
	{
		vx = 0;
		x += Left_Push;
	} 
	else if (x >= Right_Edge - 32)
	{
		vx = 0;
		x -= Left_Push;
	}
	else if (y <= Top_Edge)
	{
		vy = 0;
		y += Left_Push;
	}

	if (shell != NULL && shell->GetState() == KOOPA_STATE_CARRIED)
	{
		if (vx > 0)
		{
			shell->SetPosition(x + 16.0f, y - 1.0f);
			shell->SetDir(-1);
		}
		else if (vx < 0)
		{
			shell->SetPosition(x - 16.0f, y - 1.0f);
			shell->SetDir(1);
		}
		else
		{
			float koox, kooy;
			shell->GetPosition(koox, kooy);
			shell->SetPosition(koox, y - 1.0f);
		}
	}

	//DebugOut(L"Player: %f", vx);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	if (GetTickCount64() - kickable_start > MARIO_KICKABLE_TIME)
	{
		kickable_start = 0;
		kickable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CPlatform*>(e->obj) && dynamic_cast<CPlatform*>(e->obj)->getType() != 0)
		OnCollisionWithPlatform(e);

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CQuestionBlock*>(e->obj))
		OnCollisionWithQuestionBlock(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
	shell = koopa;
	float koox, kooy;
	koopa->GetPosition(koox, kooy);
	
	// Jump on top >> Koopa turns into shell and Mario deflects a bit 
	if (e->ny < 0)
	{
		// Red Koopa
		if (koopa->GetType() == 2)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL)				// When Koopa is in turtle form
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if (koopa->GetState() == KOOPA_STATE_SHELL)		// When Koopa is in shell form
			{
				float koox, kooy;
				koopa->GetPosition(koox, kooy);

				if (this->x < koox)
					koopa->SetDir(-1);
				else
					koopa->SetDir(1);

				koopa->SetState(KOOPA_STATE_SHELL_MOVING);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
			else if (koopa->GetState() == KOOPA_STATE_SHELL_MOVING)	// When Koopa is in shell form and moving
			{
				koopa->SetState(KOOPA_STATE_SHELL);
				vy = -MARIO_JUMP_DEFLECT_SPEED;
			}
		}
	}
	else // Collide X with Koopa
	{
		if (koopa->GetState() == KOOPA_STATE_SHELL || koopa->GetState() == KOOPA_STATE_SHELL + 1 || koopa->GetState() == KOOPA_STATE_CARRIED)
		{
			if (abs(ax) == abs(MARIO_ACCEL_RUN_X))
			{
				isCarrying = true;
				koopa->SetState(KOOPA_STATE_CARRIED);
			}
			else if (abs(ax) == abs(MARIO_ACCEL_WALK_X))
			{
				StartKickable();

				if (e->nx < 0)
					koopa->SetDir(-1);
				else
					koopa->SetDir(1);

				koopa->SetState(KOOPA_STATE_SHELL_MOVING);
			}
		}

		if (untouchable == 0)
		{
			if (koopa->GetState() != KOOPA_STATE_SHELL && koopa->GetState() != KOOPA_STATE_SHELL + 1 
				&& kickable != 1 && koopa->GetState() != KOOPA_STATE_CARRIED)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	CCoin* objcoin = dynamic_cast<CCoin*>(e->obj);
	if (objcoin->GetCoinType() == 0)
	{
		objcoin->Delete();
		coin++;
	}
}

void CMario:: OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* objmushroom = dynamic_cast<CMushroom*>(e->obj);

	if (level == MARIO_LEVEL_SMALL)
	{
		y = y - Push_Up_Platform * 2;
		level = MARIO_LEVEL_BIG;
	}

	objmushroom->Delete();
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* objleaf = dynamic_cast<CLeaf*>(e->obj);

	if (level == MARIO_LEVEL_BIG)
	{
		DebugOut(L"Fuck");
		y = y - Push_Up_Platform * 2;
		level = MARIO_LEVEL_TAIL;
	}

	objleaf->Delete();
}

void CMario::OnCollisionWithQuestionBlock(LPCOLLISIONEVENT e)
{
	CQuestionBlock* qblock = dynamic_cast <CQuestionBlock*> (e->obj);
	
	if (e->ny > 0 && qblock->HasItem())
	{
		if (qblock->GetBlockType() == 0)		// Coin
		{
			qblock->SetHasItem(false);
			float qblock_x, qblock_y;
			qblock->GetPosition(qblock_x, qblock_y);

			CCoin* newcoin = new CCoin(qblock_x, qblock_y - COIN_WIDTH, 1);
			LPSCENE thisscene = CGame::GetInstance()->GetCurrentScene();

			thisscene->AddNewObject(newcoin);

			newcoin->SetFlyable(true);
			qblock->SetPosition(qblock_x, qblock_y - QUESTIONBLOCK_OFFSET);

			coin++;
		}
		else if (qblock->GetBlockType() == 1)		//Mushroom
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

	//qblock->SetState(STATE_QUESTIONBLOCK_DISABLE);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithPlatform(LPCOLLISIONEVENT e)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(e->obj);

	switch (platform->getType()) 
	{
	case 1:
		if (e->ny < 0)
		{
			y -= Push_Up_Platform;
			platform->SetState(-1);
		}
		else
		{
			platform->SetState(PLATFORM_PASSABLE);
		}
		break;
	case 2:
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
		break;
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (isCarrying == false)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_CARRY_RIGHT_IDLE;
					else aniId = ID_ANI_MARIO_SMALL_CARRY_LEFT_IDLE;
				}
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && isCarrying == true)
					aniId = ID_ANI_MARIO_SMALL_CARRY_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
				{
					if (kickable == 1)
						aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
					else
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
				}
				
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && isCarrying == true)
					aniId = ID_ANI_MARIO_SMALL_CARRY_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
				{
					if (kickable == 1)
						aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
					else 
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTail()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (state == MARIO_STATE_FLY)
		{
			if (nx >= 0)
				aniId = ID_ANI_TAIL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_TAIL_JUMP_RUN_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_TAIL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_TAIL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_TAIL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_TAIL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_TAIL_SIT_RIGHT;
			else
				aniId = ID_ANI_TAIL_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_TAIL_IDLE_RIGHT;
				else aniId = ID_ANI_TAIL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_TAIL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
					aniId = ID_ANI_TAIL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
					aniId = ID_ANI_TAIL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_TAIL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
					aniId = ID_ANI_TAIL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
					aniId = ID_ANI_TAIL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_TAIL_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TAIL)
		aniId = GetAniIdTail();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_CARRY_RELEASE:
		if (isCarrying == true)
		{
			isCarrying = false;
			shell->SetState(KOOPA_STATE_SHELL_MOVING);
		}
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		if (vx < 0)
			ax = MARIO_ACCEL_RUN_X * 3;
		else
			ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		if (vx > 0)
			ax = -MARIO_ACCEL_RUN_X * 3;
		else
			ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_FLY:
		if (isOnPlatform)
			vy = -MARIO_JUMP_SPEED_Y;
		else if (abs(vx) == abs(MARIO_RUNNING_SPEED) || isFlying == true)
		{
			vy = -MARIO_JUMP_SPEED_Y;
			isFlying = true;
		}
		//vx = MARIO_RUNNING_SPEED;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG || level == MARIO_LEVEL_TAIL)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

