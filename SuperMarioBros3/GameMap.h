#pragma once
#include <unordered_map>
#include "Tiles.h"

class GameMap
{
	int column = 0;
	int row = 0;
	int mapArr[300][300] = {};
	LPTILES tiles = NULL;
	LPCWSTR filePath = NULL;
public:
	GameMap(LPCWSTR filePath);
	~GameMap();

	void AddTiles(LPTILES tiles);
	LPTILES GetTiles();
	void LoadMap();
	void DrawMap();
	void ClearMap();
	int GetColumn() { return this->column; };
};
typedef GameMap* LPMAP;

