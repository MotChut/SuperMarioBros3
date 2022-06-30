#include "TitleKey.h"

#include "debug.h"
#include "Game.h"
#include "Title.h"
#include "TitleItem.h"
#include "Mario.h"

void CTitleKey::OnKeyDown(int KeyCode)
{
	float vx, vy;
	vx = vy = -1;
	
	if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()))
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetSpeed(vx, vy);
	
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()) && vx == 0 && vy == 0)
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetSpeed(0, 0.1f);
		else if (dynamic_cast<CTitleItem*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer())) CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetPosition(64, 172);
		break;
	case DIK_UP:
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()) && vx == 0 && vy == 0)
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetSpeed(0, -0.1f);
		else if (dynamic_cast<CTitleItem*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer())) CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetPosition(64, 156);
		break;
	case DIK_RIGHT:
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()) && vx == 0 && vy == 0)
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetSpeed(0.1f, 0);
		break;
	case DIK_LEFT:
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()) && vx == 0 && vy == 0)
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetSpeed(-0.1f, 0);
		break;
	case DIK_W:
	{
		if (!dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()))
		{
			float x, y;
			CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetPosition(x, y);

			if (y == 156)
			{
				CGame::GetInstance()->InitiateSwitchScene(7);
			}
		}
		break;
	}
	case DIK_S:	
	{
		if (dynamic_cast<CMario*>(CGame::GetInstance()->GetCurrentScene()->GetPlayer()))
		{
			if (vx == 0 && vy == 0 && CGame::GetInstance()->GetCurrentScene()->GetPlayer()->GetState() == MARIO_STATE_MAP_TRANS)
				CGame::GetInstance()->InitiateSwitchScene(5);
		}
		break;
	}
	}
}
