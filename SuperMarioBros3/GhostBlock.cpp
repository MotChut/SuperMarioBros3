#include "GhostBlock.h"

void CGhostBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GHOSTBLOCK)->Render(x, y);
}

void CGhostBlock::SetState(int st)
{
	state = st;
}

int CGhostBlock::IsBlocking()
{
	return (state == GHOSTBLOCK_PASSABLE);
}

