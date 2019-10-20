#pragma once

#include <unordered_map>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <LayeredDraw.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sf {
	class Texture;
}

template<typename ParallaxEnum>
class Parallax
{
public:
	using ParallaxHolder = ResourceHolder<sf::Texture, ParallaxEnum>;
public:
	explicit Parallax(ParallaxHolder*, LayeredDraw*);
	void addLayer(ParallaxEnum pe, short draw_height, float x_speed, float y_speed, float x_offset, float y_offset);
	void removeLayer(ParallaxEnum pe);
	//void update(const sf::RenderTarget& target, sf::View);
	void update(sf::Vector2i characterPosInScreen, sf::Vector2i screenSize);

	//sprite management
	void setScale(ParallaxEnum pe, float scaleX, float scaleY);
	void fitToWindowX(sf::Window);
	void fitToWindowY(sf::Window);
private:
	struct Layer {
		LayeredDraw::ID_size id = 0;
		sf::Sprite sprite;
		float x_speed = 1.0f;
		float y_speed = 1.0f;
		float x_offset = 0.f;
		float y_offset = 0.f;
	};
private:
	std::unordered_map<ParallaxEnum, Layer> mLayers;
	ParallaxHolder* mParallaxHolder;
	LayeredDraw* mLayeredDraw;
};