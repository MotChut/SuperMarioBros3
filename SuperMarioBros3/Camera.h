#pragma once
#include <stdio.h>

#include "Mario.h"
#include "Game.h"
#include "PlayScene.h"

class Camera
{
	static Camera* __instance;

	float cam_x = 0.0f;
	float cam_y = 0.0f;
	float cam_x_speed = 0.09f;
	float CAM_X_END_SCENE = 0.0f;
	
	bool canChangeCamY = false;
	bool isAutoMovingCamera = false;
	DWORD timeStartMoving = 0;
public:
	Camera();
	void SetLockCamY(bool canChange) { this->canChangeCamY = canChange; };
	void SetCamPos(float x, float y);
	void GetCamPos(float& x, float& y);
	void SetTimStartMoving() { this->timeStartMoving = GetTickCount64(); };
	void UpdateCamPos(DWORD dt);
	void SetCamXSpeed(float cam_x_speed) { this->cam_x_speed = cam_x_speed; };
	void SetCamXEndScene(float CAM_X_END_SCENE) { this->CAM_X_END_SCENE = CAM_X_END_SCENE; };
	float GetCamXEndScene() { return this->CAM_X_END_SCENE; };
	void SetIsAutoMovingCamera(bool isAutoMovingCamera) { this->isAutoMovingCamera = isAutoMovingCamera; };
	bool GetIsAutoMovingCamera() { return this->isAutoMovingCamera; };

	static Camera* GetInstance();
	~Camera();
};

typedef Camera* LPCAMERA;

