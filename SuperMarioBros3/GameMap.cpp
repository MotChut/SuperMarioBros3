#include <iostream>
#include <fstream>
#include "GameMap.h"
#include "Debug.h"
#include "Tile.h"
#include "Game.h"
#include "Resources.h"
#include "PlayScene.h"


GameMap::GameMap(LPCWSTR filePath, LPCWSTR frontfilePath) {
	this->filePath = filePath;
	this->frontfilePath = frontfilePath;
}

GameMap::~GameMap() {};

void GameMap::AddTiles(LPTILES tiles) {
	this->tiles = tiles;
}

LPTILES GameMap::GetTiles() {
	return tiles;
}

void GameMap::LoadMap() {

	DebugOut(L"[INFO] Load map from: %s \n", this->filePath);

	ifstream f;
	f.open(this->filePath);

	f >> this->row >> this->column;
	
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->column; j++) {
			f >> this->mapArr[i][j];
		}
	}
	f.close();

	//Load front map
	f.open(this->frontfilePath);

	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->column; j++) {
			f >> this->frontmapArr[i][j];
		}
	}
	f.close();
}

void GameMap::DrawMap() {
	float cam_x, cam_y;
	
	CGame* game = CGame::GetInstance();
	game->GetCamPos(cam_x, cam_y);
	int screenHeight = SCREEN_HEIGHT;
	int screenWidth = SCREEN_WIDTH;

	int frameWidth = tiles->GetWidth();
	int frameHeight = tiles->GetHeight();

	int startRow = (int)cam_y / frameHeight;
	int endRow = (int)(cam_y + screenHeight) / frameHeight + 1;

	int startColumn = (int)cam_x / frameWidth;

	int endColumn = (int)(cam_x + screenWidth) / frameWidth + 1;

	vector<LPTILE> tileset = tiles->GetTiles();

	int x = 0, y = 0;

	for (int i = startRow; i < endRow; i++) {
		for (int j = startColumn; j < endColumn; j++) {
			int index = this->mapArr[i][j];
			if (index != -1) {
				tileset[index]->Draw((float)y * frameWidth - (int)cam_x % Tile_Width, (float)x* frameHeight);
			}

			index = this->frontmapArr[i][j];
			if (index != -1) {
				tileset[index]->Draw((float)y * frameWidth - (int)cam_x % Tile_Width, (float)x * frameHeight);
			}
			y++;
		}
		x++;
		y = 0;
	}
}
void GameMap::ClearMap()
{
	//memset(mapArr, 0, sizeof(mapArr[0][0]) * 300 * 300);
}

