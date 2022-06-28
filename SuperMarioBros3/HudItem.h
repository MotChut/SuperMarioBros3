#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ANI_ZERO	250000
#define ANI_ONE	250001
#define ANI_TWO	250002
#define ANI_THREE	250003
#define ANI_FOUR	250004
#define ANI_FIVE	250005
#define ANI_SIX	250006
#define ANI_SEVEN	250007
#define ANI_EIGHT	250008
#define ANI_NINE	250009

#define ANI_SPEED	250010
#define ANI_FLYABLE	250020

#define ANI_MUSHROOM	250030
#define ANI_FLOWER	250040
#define ANI_STAR	250050

#define HUD_ITEM_BBOX_WIDTH	8
#define HUD_ITEM_BBOX_HEIGHT	7

#define HUD_GIFT_SIZE	16

class CHudItem : public CGameObject {
protected:
	int type = 0;	//0->9: numbers, 10: speed, 11: flyable, 12: mushroon, 13: flower, 14: star
	int visible = 1;
public:
	CHudItem(float x, float y, int type);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetType() { return type; }
	void SetVisible(int sta) { visible = sta; }
	void SetType(int type) { this->type = type; }
};
typedef CHudItem* LPHUDITEM;