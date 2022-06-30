#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ANI_TITLE	470000
#define ANI_CURSOR	475000
#define ANI_VERSION	476000

#define TITLE_ITEM_WIDTH	179
#define TITLE_ITEM_HEIGHT	160		
#define CURSOR_WIDTH	7
#define CURSOR_HEIGHT	8
#define VERSION_WIDTH	42
#define VERSION_HEIGHT	41

class CTitleItem : public CGameObject {
protected:
	int type = 0;	//0: item, 1: cursor, 2: version
	
public:
	CTitleItem(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
	int IsBlocking() { return 0; }
};
