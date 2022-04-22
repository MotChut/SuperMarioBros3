#pragma once

#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#define BRICK_WIDTH 16
#define BRICK_HEIGHT 16

class CBrick : public CGameObject {
public:
	CBrick();
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render() {
		LPANIMATION ani = CAnimations::GetInstance()->Get(510);

		ani->Render(x, y);
	};
	void Update(DWORD dt) {}
};

