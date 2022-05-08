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
	LPTILE tile = new Tile(left, top, height, width, NULL);
	tiles.push_back(tile);
}

void Tiles::ClearTileset()
{
	for (auto tile : tiles) {
		delete tile;
	}

	tiles.clear();
}
