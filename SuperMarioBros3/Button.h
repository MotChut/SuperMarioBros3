#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_BUTTON 14000
#define ID_ANI_BUTTON_DOWNED 14001
#define BUTTON_WIDTH 16
#define BUTTON_BBOX_WIDTH 16
#define BUTTON_BBOX_HEIGHT 16

#define BUTTON_BBOX_HEIGHT_DOWN 6

#define BUTTON_OFFSET	4

class CButton : public CGameObject {
protected:
	bool isDowned = false;
public:
	CButton(float x, float y) : CGameObject(x, y) { }
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void SetDown(bool state) { isDowned = state; }
	bool GetDown() { return isDowned; }
};