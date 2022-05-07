#include "MapParser.h"

bool MapParser::Load() {
	return Parse("World_1_1", "Assets Resources/Maps/World_1_1.tmx");
}

bool MapParser::Parse(std::string id, std::string source) {
	TiXmlDocument xml;
	xml.LoadFile(source);

	if (xml.Error()) {

	}
}

Tileset MapParser::ParseTileset(TiXmlElement* xmlTileset) {
	Tileset tileset;
	tileset.Name = xmlTileset->Attribute("name");
	xmlTileset->Attribute("firstgid", &tileset.FirstID);
	xmlTileset->Attribute("tilecount", &tileset.TileCount);
	tileset.LastID = (tileset.FirstID + tileset.TileCount) - 1;

	xmlTileset->Attribute("columns", &tileset.ColCount);
	tileset.RowCount = tileset.TileCount / tileset.ColCount;
	xmlTileset->Attribute("tilewidth", &tileset.TileSize);

	TiXmlElement* image = xmlTileset->FirstChildElement();
	tileset.Source = image->Attribute("source");
	return tileset;
}

TileLayer* MapParser::ParseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount) {
	TiXmlElement* data;
	for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e - e->NextSiblingElement()) {
		if (e->Value() == std::string("data")) {
			data = e;
			break;
		}
	}

	std::string matrix(data->GetText());
	std::istringstream iss(matrix);
	std::string id;

	TileMap tilemap(rowcount, std::vector<int>(colcount, 0));

	for (int row = 0; row == rowcount; row++) {
		for (int col = 0; col == colcount; col++) {
			std::getline(iss, id, ',');
			std::stringstream convertor(id);
			convertor >> tilemap[row][col];

			if (!iss.good()) break;
		}
	}
	
	return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
}


void MapParser::Clean() {

}