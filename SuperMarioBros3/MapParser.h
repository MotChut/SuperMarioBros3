#pragma once
#include <map>
#include <string>
#include "Map.h"
#include "TileLayer.h"
#include "tinyxml.h"


class MapParser
{
public: 
	bool Load();
	void Clean();

	inline Map* GetMaps();
	inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }

private: 
	bool Parse(std::string id, std::string source);
	Tileset ParseTileset(TiXmlElement* xmlTileset);
	TileLayer* ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount);

	MapParser() {}
	static MapParser* s_Instance;
	std::map<std::string, Map*> m_MapDict;
};

