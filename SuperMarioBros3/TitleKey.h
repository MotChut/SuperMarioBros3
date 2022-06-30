#pragma once

#include "Scene.h"

class CTitleKey : public CSceneKeyHandler
{
public:
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {}
	virtual void KeyState(BYTE* states) {}
	CTitleKey(LPSCENE s) :CSceneKeyHandler(s) {};
};
