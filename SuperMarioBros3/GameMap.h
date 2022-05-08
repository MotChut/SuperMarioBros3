#pragma once
#include <unordered_map>
#include "Tiles.h"

class GameMap
{
	int column;
	int row;
	int mapArr[300][300];
	LPTILES tiles;
	LPCWSTR filePath;
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

