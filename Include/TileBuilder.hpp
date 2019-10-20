#pragma once

#include <unordered_map>
#include <string>
#include <string_view>
#include <set>

#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>

#include <SFML/Graphics/Texture.hpp>

class TileBuilder
{
public:
	using sv = std::string_view;
	using TileSetHolder = ResourceHolder<sf::Texture, std::string>;
public:
	struct TileType
	{
		//SSO: Don't make tilenames very long
		sv tilesetname;
		sv tilename;
		sf::Texture* texture;
		int top, left;
		TileType(sv tsn, sv tn, sf::Texture* t, int to, int l) : tilesetname(tsn), tilename(tn), texture(t), top(to), left(l) 
		{}
		TileType(const TileType & other) = default;
	};
	explicit TileBuilder() = default;
	explicit TileBuilder(const std::string& tilesetname);
	void loadTileSet(const std::string& tilesetname);
	TileType getTile(const std::string& tilename) const;
private:
	TileSetHolder mTileSetHolder;
	std::unordered_map<std::string, TileType> mTypes;
	std::set<std::string> mLoadedTileSets;
};