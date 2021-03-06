#pragma once
#include <vector>
#include "Tile.h"

class Tiles
{
private:
	int tileHeight;
	int tileWidth;
	static Tiles* __instance;
	LPTEXTURE texture;
	vector<LPTILE> tiles;

public:
	Tiles();
	~Tiles(); 

	void AddTile(int left, int top, int height, int width);
	void LoadTileset(LPCWSTR config, LPCWSTR tileset);
	void ClearTileset();
	int GetWidth() { return tileWidth; };
	int GetHeight() { return tileHeight; };

	vector<LPTILE> GetTiles() { return this->tiles; }
};
typedef Tiles* LPTILES;
