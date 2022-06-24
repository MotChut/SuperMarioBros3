#pragma once
//Window
#define WINDOW_CLASS_NAME L"MarioGame"
#define MAIN_WINDOW_TITLE L"Super Mario Bros 3"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 272



//FPS and Input
#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256



//Tilesets
#define Tile_Height 16
#define Tile_Width 16

#define Push_Up_Platform	8.0f

//Camera
#define Cam_Y_Middle	240
#define Cam_Y_Top	64
#define Cam_Y_Bottom	448

#define Left_Edge	8
#define Right_Edge	2816
#define Top_Edge	SCREEN_HEIGHT / 6
#define Left_Push	1