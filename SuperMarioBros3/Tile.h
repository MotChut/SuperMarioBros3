#pragma once
#include "Textures.h"

class Tile
{
private:
	int left;
	int top;
	int height;
	int width;
	LPTEXTURE texture;

public:
	Tile();
	Tile(int left, int top, int height, int width, LPTEXTURE texture);
	~Tile();

	void Draw(float x, float y);
	int GetHeight() { return this->height; };
	int GetWidth() { return this->width; };
	//void ClearTexture();
};
typedef Tile* LPTILE;
