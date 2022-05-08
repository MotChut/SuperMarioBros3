#pragma once
#include "GameObject.h"

class GameMap
{
public: 
	GameMap();
	~GameMap();

	void LoadMap(int arr[][10]);
	void DrawMap();

private:
	RECT src, dest;

	CGameObject* obj;

	int map[10][10];
};