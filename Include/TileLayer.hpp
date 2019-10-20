#pragma once

#include <string>
#include <unordered_map>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <TileBuilder.hpp>

namespace sf {
	class RenderStates;
	class RenderTarget;
}

constexpr unsigned int TILE_SIZE = 32;

class TileLayer : public sf::Drawable
{
public:
	explicit TileLayer(TileBuilder* tilebuilder);
	TileLayer(TileBuilder* tilebuilder, const std::string& filepath, short height);
	void loadLayerFromFile(const std::string& filepath, short height);
	void saveLayerToFile(const std::string& filepath) const;

	TileBuilder::TileType getTileType(int x, int y) const;
	void setTileType(int x, int y, TileBuilder::TileType& type);
	void removeTile(int x, int y);
	void setHeight(short height);
	short getHeight() const;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void buildVertexArrays() const;
	void addVertex(sf::VertexArray& varray, float worldX, float worldY, float textX, float textY, sf::Color color) const;
public:
	struct Tile
	{
		unsigned int tile_index;
		int grid_x;
		int grid_y;
		sf::Color color;
		Tile(unsigned int ti, int gx, int gy, sf::Color c = sf::Color(255,255,255))
			: tile_index (ti)
			, grid_x (gx)
			, grid_y (gy)
			, color (c)
		{
		}
	};
private:
	short mLayerHeight;
	int mTileTypeCount;
	TileBuilder* mTileBuilder;
	std::unordered_map<std::string_view, unsigned int> mTypeMap;
	std::vector<std::string> mTileSets;
	std::vector<TileBuilder::TileType> mTileTypes;
	std::vector<std::vector<Tile>> mTileArrays;
	mutable  std::vector<sf::VertexArray> mVertexArrays;
	mutable bool mNeedsUpdate = true;
};


bool operator<(const TileLayer& lhs, const TileLayer& rhs);