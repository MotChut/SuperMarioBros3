#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 
	float desx;
	float desy;		// if destination return -1, it would be portal scene to scene
	float width;
	float height; 
public:
	CPortal(float l, float t, float r, float b, float desx, float desy, int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	void RenderBoundingBox(void);
	
	int GetSceneId() { return scene_id;  }
	int IsBlocking() { return 0; }
	void GetDesPos(float& desx, float& desy) { 
		desx = this->desx;
		desy = this->desy;
	};
};