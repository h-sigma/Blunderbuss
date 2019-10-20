#include <Parallax.hpp>
#include <iostream>

#include <SFML/Graphics/Texture.hpp>

Parallax::Parallax(ParallaxHolder* ph, LayeredDraw* ld) : mParallaxHolder(ph), mLayeredDraw(ld)
{
}

void Parallax::addLayer(ParallaxEnum pe, short draw_height, float x_speed, float y_speed, float x_offset, float y_offset)
{
	sf::Texture& texture = mParallaxHolder->get(pe);
	texture.setRepeated(true);
	Parallax::Layer layer = Parallax::Layer();	//build Layer struct
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

void Parallax::removeLayer(ParallaxEnum pe)
{
	auto& value = mLayers.at(pe);
	mLayeredDraw->removeDrawable(value.id);
}
//
//void Parallax::update(const sf::RenderTarget& target, sf::View view)
//{
//	const sf::Vector2i pos(view.getCenter() - view.getSize() / 2.f);
//	sf::IntRect rect (pos, static_cast<sf::Vector2i>(view.getSize()));
//	for (auto& layerStruct : mLayers)
//	{
//		auto& layer = layerStruct.second;
//		layer.sprite.setTextureRect(sf::IntRect(rect.left / layer.x_speed + layer.x_offset, rect.top / layer.y_speed + layer.y_offset, rect.width, rect.height));
//	}
//}


void Parallax::update(sf::Vector2i characterPos, sf::Vector2i screenSize)
{
	for (auto& layerStruct : mLayers)
	{
		auto& layer = layerStruct.second;
		layer.sprite.setTextureRect(sf::IntRect(characterPos.x / layer.x_speed + layer.x_offset, characterPos.y / layer.y_speed + layer.y_offset, screenSize.x, screenSize.y));
	}
}

void Parallax::setScale(ParallaxEnum pe, float scaleX, float scaleY)
{
	mLayers.at(pe).sprite.setScale(scaleX, scaleY);
}
