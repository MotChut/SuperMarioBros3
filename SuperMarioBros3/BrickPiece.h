#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BRICK_PIECE_LEFT	12000
#define ID_ANI_BRICK_PIECE_RIGHT	12001
#define PIECE_WIDTH 8
#define PIECE_BBOX_WIDTH 8
#define PIECE_BBOX_HEIGHT 8
#define PIECE_X_SPEED	1.0f
#define PIECE_Y_SPEED	3.0f

#define PIECE_X_OFFSET	24
#define PIECE_Y_OFFSET	24

#define DELETE_TIME	2000

class CBrickPiece : public CGameObject {
protected:
	int type;	//0: left, 1:right
	ULONGLONG delete_start;

public:
	CBrickPiece(float x, float y, int type) : CGameObject(x, y) 
	{ 
		this->type = type; 
		delete_start = -1;

		if (this->type == 0) vx = -PIECE_X_SPEED;
		else vx = PIECE_X_SPEED;

		vy = PIECE_Y_SPEED;

		delete_start = GetTickCount64();
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};