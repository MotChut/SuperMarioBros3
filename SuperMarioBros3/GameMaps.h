#pragma once
#include "GameMap.h"

class GameMaps
{
	static GameMaps* __instance;
	unordered_map <int, LPMAP> maps;

public:
	GameMaps();
	~GameMaps();

	void AddMap(int id, LPCWSTR filePath);
	LPMAP GetMap(int id);
	void LoadMap(int id);
	void RenderMap(int id);
	void ClearMap(int id);

	static GameMaps* GetInstance();
};
