#pragma once
//Window
#define WINDOW_CLASS_NAME L"MarioGame"
#define MAIN_WINDOW_TITLE L"Super Mario Bros 3"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255, 0.0f)

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



//FPS and Input
#define DIRECTINPUT_VERSION 0x0800
#define MAX_FRAME_RATE 100
#define KEYBOARD_BUFFER_SIZE 1024
#define KEYBOARD_STATE_SIZE 256



//Tilesets
#define Tile_Height 16
#define Tile_Weight 16

//Maps
#define Map_1_1 L"Assets Resources\Maps\World_1_1_BackLayer.txt"
//#define Tileset_1_1 L"Assets Resources\Maps\Map_1_1.txt"
#define TilesetConfig_1_1 L"Assets Resources\Maps\TilesetConfig_1_1.txt"
#define Tileset_1_1 L"Assets Resources\Maps\World_1_1.png"