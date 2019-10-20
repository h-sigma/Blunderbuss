#include <TileManager.hpp>
#include <fstream>
#include <algorithm>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

TileManager::TileManager(LayeredDraw* ld) : mLayeredDraw(ld)
{
}

TileManager::TileManager(LayeredDraw* ld, const std::string& tileGroupPath) : mLayeredDraw(ld)
{
	this->loadTileGroup(tileGroupPath);
}

void TileManager::switchLayeredDraw(LayeredDraw* ld)
{
	for (auto& layer : mTileLayers)
	{
		mLayeredDraw->removeDrawable(layer.id);
		layer.id = ld->addDrawable(layer.layer, layer.layer.getHeight());
	}
	mLayeredDraw = ld;
}

std::unordered_map<std::string, int> TileManager::loadTileGroup(const std::string& tileGroupPath)
{
	mCurrFileGroup = tileGroupPath;
	mTileLayers.clear();

	std::ifstream layerGroup(tileGroupPath);
	std::string layerPath;
	short height = 0;
	while (layerGroup >> layerPath)
	{
		layerGroup >> height;
		auto& emplaced_ls = mTileLayers.emplace_back(std::move(TileLayer(&mTileBuilder, layerPath, height)), 0, layerPath.substr(layerPath.find_last_of('/') + 1, layerPath.size()), false);
	}
	for (auto& layer : mTileLayers)
		layer.id = mLayeredDraw->addDrawable(layer.layer, layer.layer.getHeight());
	return getCurrentLayers();
}

std::unordered_map<std::string, int> TileManager::getCurrentLayers() const
{
	std::unordered_map<std::string, int> result;
	int i = 0;
	for (auto& ls : mTileLayers)
	{
		result[ls.name] = i++;
	}
	return result;
}


bool TileManager::getHidden(int id) const
{
	return mTileLayers[id].hidden;
}

short TileManager::getHeight(int id) const
{
	return mTileLayers[id].layer.getHeight();
}

void TileManager::hideLayer(int id, bool hide)
{
	if (hide == getHidden(id))
		return;
	auto& tileLayer = mTileLayers[id];
	tileLayer.hidden = hide;
	if (hide)
	{
		mLayeredDraw->removeDrawable(tileLayer.id);
	}
	else
	{
		tileLayer.id = mLayeredDraw->addDrawable(tileLayer.layer, tileLayer.layer.getHeight());
	}
}

void TileManager::saveTileGroup() const
{
	std::string path;
	short height = 0; //dispatch
	std::ifstream layerGroup(mCurrFileGroup);
	for (const auto& layer : mTileLayers)
	{
		layerGroup >> path;
		layer.layer.saveLayerToFile(path);
		layerGroup >> height;
	}
}

TileBuilder::TileType TileManager::getTileType(int id, int x, int y) const
{
	return mTileLayers[id].layer.getTileType(x, y);
}

std::vector<TileBuilder::TileType> TileManager::getTileTypeVec(int x, int y) const
{
	std::vector<TileBuilder::TileType> result;
	for (const auto& layer : mTileLayers)
	{
		result.push_back(layer.layer.getTileType(x, y));
	}
	return std::move(result);
}

void TileManager::setTileType(int id, int x, int y, TileBuilder::TileType& type)
{
	mTileLayers[id].layer.setTileType(x, y, type);
}

void TileManager::setHeight(int id, short height)
{
	auto& layer = mTileLayers[id];
	mLayeredDraw->removeDrawable(layer.id);
	layer.layer.setHeight(height);
	mLayeredDraw->addDrawable(layer.layer, height);
}
