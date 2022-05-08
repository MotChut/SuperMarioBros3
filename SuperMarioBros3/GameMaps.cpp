#include "GameMaps.h"

GameMaps* GameMaps::__instance = NULL;

GameMaps* GameMaps::GetInstance() {
	if (__instance == NULL) __instance = new GameMaps();
	return __instance;
}

GameMaps::GameMaps() {};

GameMaps::~GameMaps() {};

void GameMaps::AddMap(int id, LPCWSTR filePath) {
	LPMAP map = new GameMap(filePath);
	maps[id] = map;
}

LPMAP GameMaps::GetMap(int id) {
	return maps[id];
}

void GameMaps::RenderMap(int id) {
	maps[id]->DrawMap();
}

void GameMaps::ClearMap(int id)
{
	maps[id]->ClearMap();
	maps[id]->GetTiles()->ClearTileset();
}

void GameMaps::LoadMap(int id) {
	maps[id]->LoadMap();
}
