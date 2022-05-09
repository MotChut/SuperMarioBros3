#include <iostream>
#include <fstream>

#include "Tiles.h"
#include "Textures.h"
#include "Debug.h"
#include "Game.h"
#include "Resources.h"

Tiles::Tiles() {
	this->tileHeight = Tile_Height;
	this->tileWidth = Tile_Weight;
};

Tiles::~Tiles() {};

void Tiles::AddTile(int left, int top, int height, int width) {
	wstring src = Tileset_1_1;
	CTextures::GetInstance()->Add(30, src.c_str());
	//LPTEXTURE tilesetsrc.
	//LPTILE tile = new Tile(left, top, height, width, src.c_str());
	//tiles.push_back(tile);
}

void Tiles::LoadTileset(LPCWSTR config, LPCWSTR tileset) {
	ifstream f;
	f.open(config);

	int row, col;
	f >> row >> col;
	
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			AddTile(j * this->tileWidth, i * this->tileHeight, this->tileHeight, this->tileWidth);
		}
	}
}
void Tiles::ClearTileset()
{
	for (auto tile : tiles) {
		delete tile;
	}

	tiles.clear();
}
