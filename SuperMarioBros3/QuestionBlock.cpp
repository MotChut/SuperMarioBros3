#include "QuestionBlock.h"

void CQuestionBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == STATE_QUESTIONBLOCK_ACTIVE)
		animations->Get(ID_ANI_QUESTIONBLOCK)->Render(x, y);
	else 
		animations->Get(ID_ANI_QUESTIONBLOCK_STOP)->Render(x, y);
}

void CQuestionBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - QUESTIONBLOCK_BBOX_WIDTH / 2;
	t = y - QUESTIONBLOCK_BBOX_HEIGHT / 2;
	r = l + QUESTIONBLOCK_BBOX_WIDTH;
	b = t + QUESTIONBLOCK_BBOX_HEIGHT;
}

void CQuestionBlock::SetState(int st)
{
	state = st;
}