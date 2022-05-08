#include "GameMap.h"
#include "Brick.h"

int lvl1[10][10] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

GameMap::GameMap() 
{ 
	LoadMap(lvl1);
}

void GameMap::LoadMap(int arr[10][10])
{
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			map[row][col] = arr[row][col];
		}
	}
}

void GameMap::DrawMap()
{
	int posx, posy;
	int size = 16;

	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			posx = col * size;
			posy = row * size;

			obj = new CBrick(posx, posy);
		}
	}
}