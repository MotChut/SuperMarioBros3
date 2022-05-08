#include "Tile.h"
#include "game.h"

Tile::Tile() {}

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
	game->Draw(x, y, texture, left, top, left + this->width, top + this->height);
}


