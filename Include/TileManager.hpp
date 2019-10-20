#pragma once

#include <unordered_map>
#include <TileBuilder.hpp>
#include <TileLayer.hpp>
#include <LayeredDraw.hpp>

class TileManager 
{
public:
	//setup functions
	explicit TileManager(LayeredDraw* ld);
	explicit TileManager(LayeredDraw* ld, const std::string& tileGroupPath);
	std::unordered_map<std::string, int> loadTileGroup(const std::string& tileGroupPath);
	std::unordered_map<std::string, int> getCurrentLayers() const;

	//tile manager functions
	bool getHidden(int id) const;
	void hideLayer(int id, bool hide);
	void switchLayeredDraw(LayeredDraw* ld);

	//tile layer forwards
	void saveTileGroup() const;

	//tile layer functions
	TileBuilder::TileType getTileType(int id, int x, int y) const;
	std::vector<TileBuilder::TileType> getTileTypeVec(int x, int y) const;
	void setTileType(int id, int x, int y, TileBuilder::TileType& type);
	void setHeight(int id, short height);
	short  getHeight(int id) const;
public: 
	struct LayerStruct {
		TileLayer layer;
		LayeredDraw::ID_size id = 0;
		std::string name = "";
		bool hidden = false;
		LayerStruct(TileLayer&& l, LayeredDraw::ID_size s, std::string n, bool h) : layer(l), id(s), hidden(h), name(std::move(n)) { }
	};
private:
	LayeredDraw* mLayeredDraw = nullptr;
	std::string mCurrFileGroup;
	TileBuilder mTileBuilder;
	std::vector<LayerStruct> mTileLayers;
};


bool operator<(const TileManager::LayerStruct& lhs, const TileManager::LayerStruct& rhs);