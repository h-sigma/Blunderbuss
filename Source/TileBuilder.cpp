#include <TileBuilder.hpp>
#include <cassert>
#include <fstream>

TileBuilder::TileBuilder(const std::string& tilesetname)
{
	loadTileSet(tilesetname);
}

void TileBuilder::loadTileSet(const std::string& tilesetname)
{
	if (mLoadedTileSets.count(tilesetname))
	{
		return;
	}
	else
	{
		mTileSetHolder.load(tilesetname, "Media/TileSet/" + tilesetname + ".png");
		auto [tilesetref, success] = mLoadedTileSets.emplace(tilesetname);
		if(!success)
		    return;
		auto& tileSetPtr = mTileSetHolder.get(tilesetname);
		
		std::ifstream tileLoader("Media/TileSet/" + tilesetname + "Map.txt");
		std::string TileName;
		int top = 0, left = 0;
		while (tileLoader >> TileName)
		{
			tileLoader >> left >> top;
			auto pair = mTypes.emplace(TileName, TileType{ *tilesetref, "", &tileSetPtr, top, left });
            pair.first->second.tilename = pair.first->first;
            (void)pair;
		}
	}
}

TileBuilder::TileType TileBuilder::getTile(const std::string& tilename) const
{
	auto iter = mTypes.find(tilename);
	assert(iter != mTypes.end());
	return iter->second;
}


