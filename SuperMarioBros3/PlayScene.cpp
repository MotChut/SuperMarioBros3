#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "QuestionBlock.h"
#include "Koopa.h"
#include "Pipe.h"
#include "Plain.h"
#include "TransparentBlock.h"
#include "HudItem.h"
#include "Hud.h"
#include "BonusItem.h"

#include "GameMaps.h"

#include "Resources.h"

#include "SampleKeyEventHandler.h"

using namespace std;

//int countflag = 0;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):CScene(id, filePath)
{
	info = NULL;
	player = NULL;
	hud = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_MAP_OBJECTS 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < signed(tokens.size()); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_BONUS_ITEM:
	{
		int type = atoi(tokens[3].c_str());

		obj = new CBonusItem(x, y, type);
		break;
	}
	case OBJECT_TYPE_HUD_ITEM:
	{
		int type = atoi(tokens[3].c_str());

		obj = new CHudItem(x, y, type);
		hud->AddProperty(dynamic_cast<CHudItem*>(obj));
		break;
	}
	case OBJECT_TYPE_HUD:
	{
		float ccx, ccy;
		CGame::GetInstance()->GetCamPos(ccx, ccy);

		int time = atoi(tokens[3].c_str());

		int c, l, s, b1, b2, b3;
		c = info->GetCoin();
		l = info->GetLife();
		s = info->GetScore();
		b1 = info->GetB1();
		b2 = info->GetB2();
		b3 = info->GetB3();

		obj = new CHud(x, y, 0, 0, c, l, s, 300, b1, b2, b3, info);
		this->hud = (CHud*)(obj);

		break;
	}
	case OBJECT_TYPE_PLAIN:
	{
		int plaintype = (int)atoi(tokens[3].c_str());
		
		obj = new CPlain(x, y, plaintype);
		break;
	}
		break;
	case OBJECT_TYPE_PIPE:
	{
		int pipeType = (int)atoi(tokens[3].c_str());

		obj = new CPipe(x, y, pipeType);
		break;
	}
	case OBJECT_TYPE_TRANSBLOCK: obj = new CTransparentBlock(x, y); break;
	case OBJECT_TYPE_KOOPAS:
	{
		int koopaType = (int)atoi(tokens[3].c_str());

		obj = new CKoopa(x, y, koopaType);
		break;
	}
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	
	case OBJECT_TYPE_GOOMBA: 
	{
		int gootype = (int)atoi(tokens[3].c_str());
		obj = new CGoomba(x, y, gootype); 
		break;
	}
	
	case OBJECT_TYPE_BRICK: 
	{
		int bricktype = (int)atoi(tokens[3].c_str());
		obj = new CBrick(x, y, bricktype);
		break;
	}
	case OBJECT_TYPE_COIN: 
	{
		int cointype = (int)atoi(tokens[3].c_str());
		obj = new CCoin(x, y, cointype);
		break;
	}
	case OBJECT_TYPE_QUESTIONBLOCK: 
	{
		int block_type = (int)atoi(tokens[3].c_str());
		obj = new CQuestionBlock(x, y, block_type); 
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int type = atoi(tokens[9].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			type
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		float desx = (float)atof(tokens[5].c_str());
		float desy = (float)atof(tokens[6].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, desx, desy, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::_ParseSection_MAPS(string line) {
	// Read file
	vector<string> tokens = split(line);

	if (tokens.size() < 4) return; // Skip line without enough infomation.

	this->id = atoi(tokens[0].c_str());
	wstring mapPath = ToWSTR(tokens[1]);
	wstring frontmapPath = ToWSTR(tokens[2]);
	wstring configPath = ToWSTR(tokens[3]);
	wstring tilesetPath = ToWSTR(tokens[4]);

	GameMaps* maps = GameMaps::GetInstance();
	maps->AddMap(this->id, mapPath.c_str(), frontmapPath.c_str());

	Tiles* tileset = new Tiles();
	tileset->LoadTileset(configPath.c_str(), tilesetPath.c_str());
	
	maps->GetMap(this->id)->AddTiles(tileset);
	
	maps->LoadMap(this->id);

}


void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

//Note from Kiet: This function will read the txt file that contains all of the information for each section
void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);
	

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[MAPS]") { section = SCENE_MAP_OBJECTS; continue; }
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_MAP_OBJECTS: _ParseSection_MAPS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}


	for (size_t i = 0; i < objects.size(); i++)
	{
		/*if (dynamic_cast<CQuestionBlock*>(objects[i]))
			DebugOut(L"This is block!!!!!!!!!!!!!!!!!!!! \n");*/
		if (bonusMys) {
			if (dynamic_cast<CBrick*>(objects[i]))
			{
				float tempx, tempy;
				objects[i]->GetPosition(tempx, tempy);
				objects[i]->Delete();
				CCoin* brickcoin = new CCoin(tempx, tempy, 0);
				objects.push_back(brickcoin);
			}
		}
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);
	
	
	CGame *game = CGame::GetInstance();

	cx -= game->GetBackBufferWidth() / 2;
	
	if (cx < 0) cx = 0;
	else if (cx > Right_Edge - SCREEN_WIDTH) cx = Right_Edge - SCREEN_WIDTH;
	
	if (cy < Cam_Y_Middle) cy = Cam_Y_Top;
	else if (cy > Cam_Y_Top && cy < Cam_Y_Middle) cy -= game->GetBackBufferHeight() / 2;
	else if (cy > Cam_Y_Bottom) cy = Cam_Y_Bottom;
	else cy = Cam_Y_Middle;
	
	CGame::GetInstance()->SetCamPos(cx, cy /*cy*/);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{	
	GameMaps* maps = GameMaps::GetInstance();
	maps->RenderMap(this->id);

	for (int i = 0; i < signed(objects.size()); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < signed(objects.size()); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}
