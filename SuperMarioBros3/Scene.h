#pragma once

#include "KeyEventHandler.h"
#include "Collision.h"

/*
*  Abstract class for a game scene
*/
class CScene
{
protected:
	LPKEYEVENTHANDLER key_handler;
	int id;
	LPCWSTR sceneFilePath;

public: 
	CScene(int id, LPCWSTR filePath);

	LPKEYEVENTHANDLER GetKeyEventHandler() { return key_handler; }
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0; 
	virtual void AddNewObject(LPGAMEOBJECT o) = 0;
	virtual void SetBonus(bool o) = 0;
	virtual void SetCoin(int c) = 0;
	virtual void SetLife(int l) = 0;
	virtual void SetScore(int s) = 0;
	virtual void SetBonusGift(int gift) = 0;
	virtual void SetInfoHud(int c, int l, int s, int b1, int b2, int b3, int level) = 0;
	virtual void GetInfo(int& c, int& l, int& s, int& b1, int& b2, int& b3, int& level) = 0;

	virtual LPGAMEOBJECT GetPlayer() = 0;
};
typedef CScene * LPSCENE;


class CSceneKeyHandler : public CKeyEventHandler
{
protected: 
	CScene * scence; 

public:
	virtual void KeyState(BYTE *states) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
	CSceneKeyHandler(LPSCENE s) :CKeyEventHandler() { scence = s; }
};

typedef CSceneKeyHandler* LPSCENEKEYHANDLER;