#include <iostream>
#include <fstream>
#include "GameMap.h"
#include "Debug.h"
#include "Tile.h"
#include "Game.h"
#include "Resources.h"
#include<string>  

GameMap::GameMap(LPCWSTR filePath) {
	this->filePath = filePath;
}

GameMap::~GameMap() {};

void GameMap::AddTiles(LPTILES tiles) {
	this->tiles = tiles;
}

LPTILES GameMap::GetTiles() {
	return tiles;
}

void GameMap::LoadMap() {

	DebugOut(L"Load map from: %s \n", this->filePath);

	ifstream f;
	f.open(this->filePath);

	f >> this->row >> this->column;
	
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->column; j++) {
			f >> this->mapArr[i][j];
		}
	}
	f.close();
}

void GameMap::DrawMap() {
	int frameWidth = tiles->GetWidth();
	int frameHeight = tiles->GetHeight();

	
	vector<LPTILE> tileset = tiles->GetTiles();

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->column; j++) {
			int index = this->mapArr[i][j];
			if (index != -1) {
				tileset[index]->Draw((float) j * frameWidth, (float) i * frameHeight);
			}
		}
	}
}
void GameMap::ClearMap()
{
	//memset(mapArr, 0, sizeof(mapArr[0][0]) * 300 * 300);
}

