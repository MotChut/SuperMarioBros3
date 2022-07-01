#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Hud.h"
#include "WorldMap.h"
#include "InfoHud.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;	
	CHud* hud;
	InfoHud* info;
	bool bonusMys = false;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void AddNewObject(LPGAMEOBJECT o) { this->objects.push_back(o); }

	void SetBonus(bool state) { bonusMys = state; }
	void SetCoin(int c) { this->hud->SetCoin(c); }
	void SetLife(int l) { this->hud->SetLife(l); }
	void SetScore(int s) { this->hud->SetScore(s); }
	void SetBonusGift(int g) { this->hud->SetBonusGift(g); }
	void SetInfoHud(int c, int l, int s, int b1, int b2, int b3, int level)
	{
		InfoHud* ifo = new InfoHud(c, l, s, b1, b2, b3, level);
		info = ifo;
	}
	void GetInfo(int& c, int& l, int& s, int& b1, int& b2, int& b3, int& level)
	{
		c = info->GetCoin();
		l = info->GetLife();
		s = info->GetScore();
		b1 = info->GetB1();
		b2 = info->GetB2();
		b3 = info->GetB3();
		level = info->GetLevel();
	}
};

typedef CPlayScene* LPPLAYSCENE;

