#include "BrickPiece.h"
#include "Debug.h"

void CBrickPiece::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	
	if (type == 0)
		animations->Get(ID_ANI_BRICK_PIECE_LEFT)->Render(x, y);
	else 
		animations->Get(ID_ANI_BRICK_PIECE_RIGHT)->Render(x, y);
	
	//RenderBoundingBox();
}

void CBrickPiece::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx;
	y += vy;
	DebugOut(L"%f", vy);

	if (GetTickCount64() - delete_start > DELETE_TIME)
	{
		delete_start = -1;
		this->Delete();
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrickPiece::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PIECE_BBOX_WIDTH / 2;
	t = y - PIECE_BBOX_HEIGHT / 2;
	r = l + PIECE_BBOX_WIDTH;
	b = t + PIECE_BBOX_HEIGHT;
}