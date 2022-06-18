#include "Button.h"

void CButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(!isDowned) animations->Get(ID_ANI_BUTTON)->Render(x, y);
	else animations->Get(ID_ANI_BUTTON_DOWNED)->Render(x, y);
	//RenderBoundingBox();
}

void CButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BUTTON_BBOX_WIDTH / 2;
	r = l + BUTTON_BBOX_WIDTH;
	
	if (!isDowned)
	{
		t = y - BUTTON_BBOX_HEIGHT / 2;
		b = t + BUTTON_BBOX_HEIGHT;
	}
	else
	{
		t = y - BUTTON_BBOX_HEIGHT_DOWN / 2;
		b = t + BUTTON_BBOX_HEIGHT_DOWN;
	}
}