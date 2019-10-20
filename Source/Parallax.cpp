#include <Parallax.hpp>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>

template<typename ParallaxEnum>
Parallax<ParallaxEnum>::Parallax(ParallaxHolder* ph, LayeredDraw* ld) : mParallaxHolder(ph), mLayeredDraw(ld)
{
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::addLayer(ParallaxEnum pe, short draw_height, float x_speed, float y_speed, float x_offset, float y_offset)
{
	sf::Texture& texture = mParallaxHolder->get(pe);
	texture.setRepeated(true);
	Parallax::Layer layer = Parallax<ParallaxEnum>::Layer();	//build Layer struct
	layer.sprite.setTexture(texture);
	layer.x_speed = x_speed;
	layer.y_speed = y_speed;	
	layer.x_offset = x_offset;
	layer.y_offset = y_offset;
	//don't forget to add ID to struct
	auto [pair, success] = mLayers.insert_or_assign(pe, std::move(layer));
	auto& [key, value] = *pair;
    (void)key;
	if (!success)
		std::cerr << "Unable to insert layer.";
	else
		value.id = mLayeredDraw->addDrawable(value.sprite, draw_height);
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::removeLayer(ParallaxEnum pe)
{
	auto& value = mLayers.at(pe);
	mLayeredDraw->removeDrawable(value.id);
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::update(sf::Vector2i characterPos, sf::Vector2i screenSize)
{
	for (auto& layerStruct : mLayers)
	{
		auto& layer = layerStruct.second;
		layer.sprite.setTextureRect(sf::IntRect(characterPos.x / layer.x_speed + layer.x_offset, characterPos.y / layer.y_speed + layer.y_offset, screenSize.x, screenSize.y));
	}
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::setScale(ParallaxEnum pe, float scaleX, float scaleY)
{
	mLayers.at(pe).sprite.setScale(scaleX, scaleY);
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::fitToWindowX(sf::Window) {
    //auto windowSize = window.getSize();
}

template<typename ParallaxEnum>
void Parallax<ParallaxEnum>::fitToWindowY(sf::Window ) {

}
