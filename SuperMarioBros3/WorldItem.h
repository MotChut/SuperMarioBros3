#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ANI_TREE	480000
#define ANI_NODE	490000
#define ANI_NODE_ONE	490001
#define ANI_NODE_TWO	490002
#define ANI_NODE_THREE	490003
#define ANI_NODE_FOUR	490004
#define ANI_NODE_FIVE	490005
#define ANI_NODE_SIX	490006
#define ANI_NODE_TRANS	490007

#define ITEM_WIDTH	16
#define ITEM_HEIGHT	15

class CWorldItem : public CGameObject {
protected:
	int type = 0;	//0: start, 1->6: level, 7: tree, 8: transnode

public:
	CWorldItem(float x, float y, int type) : CGameObject(x, y) { this->type = type; }
	void Render();
	void Update(DWORD dt);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
	int IsBlocking() { return 0; }
};
