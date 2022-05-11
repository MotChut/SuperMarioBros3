#include "Tile.h"
#include "Game.h"
#include "Debug.h"
Tile::Tile() {
	texture = NULL;
	left = 0;
	top = 0;
	height = 0;
	width = 0;
}

Tile::Tile(int left, int top, int height, int width, LPTEXTURE texture) {
	this->left = left;
	this->top = top;
	this->height = height;
	this->width = width;
	this->texture = texture;
}

Tile::~Tile() {}

void Tile::Draw(float x, float y) {
	CGame* game = CGame::GetInstance();
	/*RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + this->width;
	rect.bottom = top + this->height;
	game->Draw(x, y, texture, &rect, 1.0f, this->width, this->height);*/
	game->Draw(x, y, texture, left, top, left + this->width, top + this->height);
}


