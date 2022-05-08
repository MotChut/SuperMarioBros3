#include <iostream>
#include <fstream>
#include "GameMap.h"
#include "Debug.h"
#include "Tile.h"
#include "Game.h"
#include "Resources.h"

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

	DebugOut(L"[INFO] Start loading MAAPPPPPPPP resources from : %s \n", this->filePath);

	ifstream f;
	f.open(this->filePath);
	f >> this->row >> this->column;
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->column; j++) {
			f >> this->mapArr[i][j];
		}
	}
}

void GameMap::DrawMap() {
	CGame* game = CGame::GetInstance();

	float cam_x, cam_y;
	game->GetCamPos(cam_x, cam_y);


	int screenHeight = SCREEN_WIDTH;
	int screenWidth = SCREEN_HEIGHT;

	int frameWidth = tiles->GetWidth();
	int frameHeight = tiles->GetHeight();

	int startRow = cam_y / frameHeight;
	int endRow = (cam_y + screenHeight) / frameHeight + 1;

	int startColumn = cam_x / frameWidth;

	int endColumn = (cam_x + screenWidth) / frameWidth + 1;

	vector<LPTILE> tileset = tiles->GetTiles();

	for (int i = startRow; i < endRow; i++) {
		for (int j = startColumn; j < endColumn; j++) {
			int index = this->mapArr[i][j];
			if (index != 0) {
				tileset[index - 1]->Draw((j * frameWidth), (i)*frameHeight);
			}
		}
	}
}
void GameMap::ClearMap()
{
	//memset(mapArr, 0, sizeof(mapArr[0][0]) * 300 * 300);
}

