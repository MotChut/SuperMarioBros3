#include "QuestionBlock.h"
#include "Mario.h"
#include "Debug.h"

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (this->hasItem == true)
		animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
	else 
		animations->Get(ID_ANI_QUESTIONBLOCK_STOP)->Render(x, y);
}

void CQuestionBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	y += vy * dt;

	if (y < base_y && this->hasItem == false)
	{
		vy = QUESTIONBLOCK_GRAVITY * dt;
	}
	else
	{
		vy = 0;
		y = base_y;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

/*void CQuestionBlock::OnCollisionWith(LPCOLLISIONEVENT e)
{
	DebugOut(L"Hey! \n");
	if (dynamic_cast<CMario*>(e->obj))
		OnCollisionWithMario(e);
}

void CQuestionBlock::OnCollisionWithMario(LPCOLLISIONEVENT e)
{
	CMario* player = dynamic_cast<CMario*>(e->obj);

	if (this->hasItem && e->ny < 0)
	{
		this->SetHasItem(false);
	}
}
*/

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}
