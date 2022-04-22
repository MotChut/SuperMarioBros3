#include "Game.h"
#include "Brick.h"

CBrick::CBrick(float x, float y) :CGameObject(x, y)
{
	
};

void CBrick::Update(DWORD dt)
{

}

void CBrick::Render()
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(510);

	ani->Render(x, y);
}
