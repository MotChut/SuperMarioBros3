#include "Hud.h"
#include "Debug.h"

CHud::CHud(float x, float y, int speed, int flyable, int coin, int life, int score, int time) : CGameObject(x, y)
{
	this->speed = speed;
	this->flyable = flyable;
	this->coin = coin;
	this->life = life;
	this->score = score;
	this->time = time;
	properties = {};

	time_start = GetTickCount64();
}

void CHud::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float ccx, ccy;
	CGame::GetInstance()->GetCamPos(ccx, ccy);

	x = ccx + 144;
	y = ccy + 210;

	float cvx = 0, cvy = 0;
	LPGAMEOBJECT p = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	if (p->GetState() != 100 && p->GetState() != 200)
		p->GetSpeed(cvx, cvy);

	//SPEED
	if (abs(cvx) >= MARIO_RUNNING_SPEED && ( p->GetState() == 400 || p->GetState() == 500) 
		|| (p->GetState() == 1000 || abs(cvx) == MARIO_FLY_SPEED))
	{
		for (int i = 0; i < 6; i++)
			properties[i]->SetVisible(1);

		properties[6]->SetVisible(1);
		properties[6]->SetPosition(ccx + 134, ccy + 206);
	}
	else if(abs(cvx) >= MARIO_RUNNING_SPEED * 5/6)
	{
		for (int i = 0; i < 5; i++)
			properties[i]->SetVisible(1);

		for (int i = 5; i < 6; i++)
			properties[i]->SetVisible(0);
	}
	else if (abs(cvx) >= MARIO_RUNNING_SPEED * 4/6)
	{
		for (int i = 0; i < 4; i++)
			properties[i]->SetVisible(1);

		for (int i = 4; i < 6; i++)
			properties[i]->SetVisible(0);
	}
	else if (abs(cvx) >= MARIO_RUNNING_SPEED * 3/6)
	{
		for (int i = 0; i < 3; i++)
			properties[i]->SetVisible(1);

		for (int i = 3; i < 6; i++)
			properties[i]->SetVisible(0);
	}
	else if (abs(cvx) >= MARIO_RUNNING_SPEED * 2 / 6)
	{
		for (int i = 0; i < 2; i++)
			properties[i]->SetVisible(1);

		for (int i = 2; i < 6; i++)
			properties[i]->SetVisible(0);
	}
	else if (abs(cvx) >= MARIO_RUNNING_SPEED * 1 / 6)
	{
		for (int i = 0; i < 1; i++)
			properties[i]->SetVisible(1);

		for (int i = 1; i < 6; i++)
			properties[i]->SetVisible(0);
	}
	else
	{
		for (int i = 0; i < 6; i++)
			properties[i]->SetVisible(0);

		properties[6]->SetVisible(0);
	}

	for (int i = 0; i < 6; i++)
		properties[i]->SetPosition(ccx + 81 + 8 * i, ccy + 206);



	//COIN
	for (int i = 7; i < 9; i++)
	{
		int dozen, unit;
		unit = coin % 10;
		dozen = coin / 10;

		if (i == 7) properties[i]->SetType(dozen);
		else if (i == 8) properties[i]->SetType(unit);

		properties[i]->SetPosition(ccx + 162 + 8 * (i - 7), ccy + 206);
	}
	
	//LIFE
	for (int i = 9; i < 11; i++)
	{
		int dozen, unit;
		unit = life % 10;
		dozen = life / 10;

		if (dozen == 0) properties[9]->SetVisible(0);

		if (i == 9) properties[i]->SetType(dozen);
		else if (i == 10) properties[i]->SetType(unit);

		properties[i]->SetPosition(ccx + 58 + 8 * (i - 9), ccy + 214);
	}

	//SCORE
	int stemp, sunit, si = 17;
	stemp = score;

	while (stemp != 0)
	{
		sunit = stemp % 10;
		properties[si--]->SetType(sunit);
		stemp /= 10;
	};

	for (int i = 11; i < 18; i++)
		properties[i]->SetPosition(ccx + 82 + 8 * (i - 11), ccy + 214);
	
	//TIME
	
	int timepass = (int)(GetTickCount64() / 1000 - time_start / 1000);
	//timepass = timepass % 10;
	int tin = 0, ti = 20;

	int timeleft = time - timepass;
	while (timeleft != 0)
	{
		tin = timeleft % 10;
		properties[ti--]->SetType(tin);
		timeleft /= 10;
	}

	for (int i = 18; i < 21; i++)
		properties[i]->SetPosition(ccx + 154 + 8 * (i - 18), ccy + 214);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CHud::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	animations->Get(ANI_HUD)->Render(x, y);
	//RenderBoundingBox();
}

void CHud::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - HUD_BBOX_WIDTH / 2;
	t = y - HUD_BBOX_HEIGHT/ 2;
	r = l + HUD_BBOX_WIDTH;
	b = t + HUD_BBOX_HEIGHT;
}