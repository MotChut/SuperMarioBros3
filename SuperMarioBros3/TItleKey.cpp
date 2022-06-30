#include "TitleKey.h"

#include "debug.h"
#include "Game.h"
#include "Title.h"

void CTitleKey::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_DOWN:
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetPosition(64, 172);
		break;
	case DIK_UP:
		CGame::GetInstance()->GetCurrentScene()->GetPlayer()->SetPosition(64, 156);
		break;
	case DIK_RETURN:
		CGame::GetInstance()->InitiateSwitchScene(1);
		CGame::GetInstance()->SwitchScene();
		break;
	}
}
