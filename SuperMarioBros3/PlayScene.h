#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Hud.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;	
	CHud* hud;
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
};

typedef CPlayScene* LPPLAYSCENE;

