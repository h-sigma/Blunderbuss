#pragma once

#include <TileManager.hpp>

namespace sf {
	class RenderWindow;
	class Time;
}

class TileMapEditor : public sf::Drawable
{
public:
	explicit TileMapEditor(const std::string& layergroup);
	void frame(sf::RenderWindow& window, sf::Time dt);
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	void loadTileGroup(const std::string& layergroup);
private:
	TileManager mTileManager;
	int currLayer = 0;
};