#include "GameMap.h"
#include "Brick.h"
#include "PlayScene.h"
#include <fstream>

GameMap::GameMap() 
{ 
	
}

GameMap::~GameMap()
{

}

void GameMap::LoadMap(std::string path, int sizeX, int sizeY)
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			CPlayScene::AddTile(atoi(&tile), x * 16, y * 16);
			mapFile.ignore();
		}
	}

	mapFile.close();
}
