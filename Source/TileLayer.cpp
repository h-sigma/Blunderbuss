#include <TileLayer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <fstream>
#include <algorithm>

bool operator<(const TileLayer& lhs, const TileLayer& rhs)
{
	return lhs.getHeight() < rhs.getHeight();
}

TileLayer::TileLayer(TileBuilder* tilebuilder) 
	: mTileBuilder(tilebuilder)
	, mLayerHeight(0)
	, mTileTypeCount(0)
{
}

TileLayer::TileLayer(TileBuilder* tilebuilder, const std::string& filepath, short height)
	: mTileBuilder(tilebuilder)
	, mLayerHeight (height)
	, mTileTypeCount(0)
{
	loadLayerFromFile(filepath, height);
}

void TileLayer::loadLayerFromFile(const std::string& filepath, short height)
{
	//clean-up
	mVertexArrays.clear();
	mTileArrays.clear();
	mTileTypeCount = 0;
	mTileTypes.clear();

	//load new layer
	mLayerHeight = height;
	mNeedsUpdate = true;

	std::ifstream Layer(filepath);
	std::string TileSet;
	//load necessary tilesets
	while (Layer >> TileSet)
	{
		if (TileSet == "-")
			break;
		mTileBuilder->loadTileSet(TileSet);
		mTileSets.push_back(TileSet);
	}

	std::string& TileName = TileSet;
	int x = 0, y = 0;
	//load all the tiles
	while (Layer >> TileName)
	{
		Layer >> x >> y;
		auto iter = mTypeMap.find(TileName);
		if (iter == mTypeMap.end())
		{	//first occurence of tile
			mTypeMap.emplace(TileName, mTileTypeCount);
			mTileTypes.emplace_back(mTileBuilder->getTile(TileName));		
			mTileArrays.emplace_back();
			mTileArrays[mTileTypeCount].emplace_back(mTileTypeCount, x, y, sf::Color());
			mVertexArrays.emplace_back(sf::Quads);
			mTileTypeCount++;
		}
		else    
		{	//tile is loaded and saved
			Tile tempTile{iter->second, x, y};
			mTileArrays[tempTile.tile_index].push_back(tempTile);
		}
	}
}

void TileLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (mNeedsUpdate)
	{
		buildVertexArrays();
		mNeedsUpdate = false;
	}
	int i = 0;	//used as indexer for following foreach loop
	for (auto& vertexArray : mVertexArrays)
	{
		states.texture = mTileTypes[i++].texture;
		target.draw(vertexArray, states);
	}
}

TileBuilder::TileType TileLayer::getTileType(int x, int y) const
{
	int on_grid_x = x / static_cast<int>(TILE_SIZE);
	int on_grid_y = y / static_cast<int>(TILE_SIZE);
	for (const auto& TileArray : mTileArrays)
	{
		for (const auto& tile : TileArray)
		{
			if (on_grid_x == tile.grid_x && on_grid_y == tile.grid_y)
				return mTileTypes[tile.tile_index];
		}
	}
	return TileBuilder::TileType{ std::string_view(), std::string_view(), nullptr, 0, 0 };
}

void TileLayer::setHeight(short height)
{
	mLayerHeight = height;
}

short TileLayer::getHeight() const
{
	return mLayerHeight;
}

void TileLayer::setTileType(int x, int y, TileBuilder::TileType& newtype)
{
	mNeedsUpdate = true;
	if (mTypeMap.find(newtype.tilename) == mTypeMap.end())
	{
		mTileArrays.emplace_back();
		mVertexArrays.emplace_back(sf::Quads);
		mTileTypes.emplace_back(newtype);
		mTypeMap.emplace(newtype.tilename, mTileTypeCount++);
	}

	int index = mTypeMap[newtype.tilename];
	for (auto& TileArray : mTileArrays)
	{
		for (auto& tile : TileArray)
		{
			if (x == tile.grid_x && y == tile.grid_y)
			{
				tile.tile_index = index;
				return;
			}
		}
	}
	mTileArrays[index].emplace_back(index, x, y);
}

void TileLayer::removeTile(int x, int y)
{
	for (auto& tileArray : mTileArrays)
	{
		auto iter = std::remove_if(tileArray.begin(), tileArray.end(), [x, y](const TileLayer::Tile& Tile) {
			return (Tile.grid_x == x) && (Tile.grid_y == y);
			});
		if (iter != tileArray.end())
		{
			tileArray.erase(iter, tileArray.end());
			return;
		}
	}
}

void TileLayer::saveLayerToFile(const std::string& filepath) const
{
	std::ofstream Layer(filepath);
	for (const auto& tileset : mTileSets)
	{
		Layer << tileset << " ";
	}
	Layer << "\n-\n";
	for (const auto& tileArray : mTileArrays)
	{
		for (const auto& tile : tileArray)
		{
			Layer << mTileTypes[tile.tile_index].tilename << " " << tile.grid_x << " " <<  tile.grid_y;
		}
	}
}


void TileLayer::buildVertexArrays() const
{
	for (int i = 0; i < mTileTypeCount; ++i)
	{
		const std::vector<TileLayer::Tile>& tileArray = mTileArrays[i];
		sf::VertexArray& vertexArray = mVertexArrays[i];
		const TileBuilder::TileType& tileType = mTileTypes[i];
		vertexArray.clear();

		sf::Vector2f size(TILE_SIZE, TILE_SIZE);
		sf::Vector2f texCoords (tileType.left, tileType.top);

		for (const auto& tile : tileArray)
		{
			sf::Vector2f pos (tile.grid_x * TILE_SIZE, tile.grid_y * TILE_SIZE);
			addVertex(vertexArray, pos.x, pos.y, texCoords.x + 0.f, texCoords.y + 0.f, tile.color);
			addVertex(vertexArray, pos.x + size.x, pos.y, texCoords.x + size.x, texCoords.y + 0.f, tile.color);
			addVertex(vertexArray, pos.x + size.x, pos.y + size.y, texCoords.x + size.x, texCoords.y + size.y, tile.color);
			addVertex(vertexArray, pos.x, pos.y + size.y, texCoords.x + 0.f, texCoords.y + size.y, tile.color);
		}
	}
}

void TileLayer::addVertex(sf::VertexArray& varray, float worldX, float worldY, float textX, float textY, sf::Color color) const
{
	sf::Vertex tempVertex;
	tempVertex.color = color;
	tempVertex.position = { worldX, worldY };
	tempVertex.texCoords = { textX, textY };
	varray.append(tempVertex);
}
