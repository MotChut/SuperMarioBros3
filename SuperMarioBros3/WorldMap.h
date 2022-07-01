#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Hud.h"
#include "InfoHud.h"

class CWorldMap : public CScene
{
protected:
	LPGAMEOBJECT player;
	CHud* hud;
	InfoHud* info;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CWorldMap(int id, LPCWSTR filePath, InfoHud* info = NULL);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void SetBonus(bool state) {}
	void SetCoin(int c) {}
	void SetLife(int l) {}
	void SetScore(int s) {}
	void SetBonusGift(int g) {}
	void AddNewObject(LPGAMEOBJECT o) { this->objects.push_back(o); }
	void SetInfoHud(int c, int l, int s, int b1, int b2, int b3, int level)
	{
		InfoHud* ifo = new InfoHud(c, l, s, b1, b2, b3, level);
		info = ifo;
	}
	LPGAMEOBJECT GetPlayer() { return player; }
	void GetInfo(int &c, int &l, int &s, int& b1, int& b2, int& b3, int& level)
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
typedef CWorldMap* LPWORLDMAP;

