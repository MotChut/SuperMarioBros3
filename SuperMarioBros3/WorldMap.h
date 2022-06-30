#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Hud.h"

class CWorldMap : public CScene
{
protected:
	LPGAMEOBJECT player;
	CHud* hud;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAPS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CWorldMap(int id, LPCWSTR filePath);

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
	LPGAMEOBJECT GetPlayer() { return player; }
};
typedef CWorldMap* LPWORLDMAP;

