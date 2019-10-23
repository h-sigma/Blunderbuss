//
// Created by harshdeep on 19/10/19.
//

#include <SFML/System.hpp>
#include <Purlox.hpp>

void PurloxInput::handleMovement(class GameObject & , class World &)  {
}

void PurloxInput::update(class GameObject & gameObject, sf::Time, class World & world) {
    handleMovement(gameObject, world);
}
