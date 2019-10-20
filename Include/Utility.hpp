#pragma once 

#include <SFML/Window/Event.hpp>

#include <string>
#include <type_traits>
#include <cmath>

namespace sf
{
    class Sprite;
    class Text;
}

std::string toString(sf::Keyboard::Key key);

void centerOrigin(sf::Sprite& sprite);

void centerOrigin(sf::Text& text);

float toRadian(float degree);

float toDegree(float radian);

float magnitude(sf::Vector2f vector);

sf::Vector2f unitVector(sf::Vector2f vector);

int randomInt(int exclusiveMax);

